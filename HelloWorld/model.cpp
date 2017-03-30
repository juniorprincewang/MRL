#include "model.h"
#include <cmath>
// for bind2nd
#include <functional>
#include <boost/math/distributions/students_t.hpp>

Model::Model()
{

}

Model::Model(std::vector<double> residues)
{
    this->residues = residues;
}

Model::~Model()
{

}

std::vector<double> Model::getLnVector(const std::vector<double> v)
{
    std::vector<double> result;
    for(int i=0; i<v.size(); i++)
    {
        result.push_back(ln(v[i]));
    }
    return result;
}

std::vector<double> Model::getZScoreVector(const std::vector<double> v)
{
    int len = v.size();
    std::vector<double> ln_vec;
    for(auto num : v)
    {
        ln_vec.push_back(ln(num));
    }
    std::vector<int> ln_position = rank(ln_vec, 0);//?
    std::vector<int> ln_repeat;
    std::vector<double>::iterator it = ln_vec.begin();
    for(; it != ln_vec.end(); it++)
    {

        int r = countIf(std::vector<double>(ln_vec.begin(), it), *it);
        ln_repeat.push_back(r+1);
    }
//    print(ln_repeat);
    std::vector<double> result;
    for(int i=0; i<len; i++)
    {
        double tmp = (ln_position[i]+ln_repeat[i]-1-0.375)/(len+0.25);
        double z_score= ppf(tmp);
        result.push_back(z_score);
    }
    return result;
}

double Model::getMean(const std::vector<double> v)
{
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();
    return mean;
}

double Model::getStdDev(const std::vector<double> v)
{

//    this->average = sum/this->size;
//    this->max_value = *std::max_element(v.begin(), v.end());
//    this->min_value = *std::min_element(v.begin(), v.end());
//    std::nth_element(v.begin(), v.begin()+this->size/2, v.end());
//    if(this->size%2)
//        this->median = v.at(this->size/2);
//    else
//        this->median = (v.at((this->size-1)/2) + v.at(this->size/2))/2;
    //

    double mean = this->getMean(v);
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(),
                   std::bind2nd(std::minus<double>(), mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    return std::sqrt(sq_sum / (v.size()-1));
}

double Model::getMedian(const std::vector<double> vector)
{
    std::vector<double> v(vector.begin(), vector.end());
    std::sort(v.begin(), v.end());
    int size = v.size();
    double median = size%2? v[size/2] : (v[size/2-1] + v[size/2])/2;
    return median;
}

double Model::getMode(const std::vector<double> unSortedVector)
{
    std::vector<double> array(unSortedVector.begin(), unSortedVector.end());
    std::sort(array.begin(), array.end());
    int counter = 1;
    int max = 0;
    double mode = array[0];
    int size = array.size();
    for (int pass = 0; pass < size - 1; pass++)
    {
        if ( array[pass] == array[pass+1] )
        {
            counter++;
            if ( counter > max )
            {
                max = counter;
                mode = array[pass];
            }
        }
        else
            counter = 1; // reset counter.
    }
    return mode;
}

std::vector<double> Model::getLnResidues()
{
    if(this->lnResidues.empty())
        this->lnResidues = Model::getLnVector(this->residues);
    return this->lnResidues;
}

double Model::ceil(double target, double precision)
{
    return precision * std::ceil(target/precision);
}

int Model::ShapiroFranciaNormalityTest(double rSquaredValue)
{
    if(this->residues.empty())
    {
        qDebug() << "Calling EUMethodI with empty residues!";
        return 0;
    }
    int count = this->residues.size();
    std::pair<double, double> r = rCritical.lower_bound(count)->second;
    double r99 =  r.first;
    double r95 = r.second;
    if(rSquaredValue <= pow(r99, 2))
        return 1;
    else if(rSquaredValue <= pow(r95, 2))
        return 2;
    else
        return 3;
}

std::vector<std::pair<double, int> > Model::EUMethodI()
{
    if(this->residues.empty())
    {
        qDebug() << "Calling EUMethodI with empty residues!";
        return std::vector<std::pair<double, int> >();
    }
    double estimated100pthPercentile = 0.0;
    double toleranceBoundFactor = 0.0;
    double ninetyFiveToleranceBound = 0.0;
    double precision= 0.0;
    int significantFigure = 0;
    double afterPrecision = 0.0;
    std::vector<double> v(this->residues);

    double mean = this->getMean(v);
    double stdDev = this->getStdDev(v);
    std::vector<std::pair<double, int> > result;
    //if(percentile == 0.95)
    {
//        qDebug() << "std dev" << stdDev;
//        qDebug() << "mean" << mean;
        estimated100pthPercentile = mean+1.645*stdDev;
//        qDebug() << estimated100pthPercentile;
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//         estString(QString::number(afterPrecision, 'f', significantFigure));
        result.push_back(std::make_pair(afterPrecision, significantFigure));
        //
        std::pair<double, double> gFactorResult = gFactor.lower_bound(v.size())->second;
        toleranceBoundFactor = gFactorResult.first;
//        qDebug() << "toleranceBoundFactor " << toleranceBoundFactor;
        ninetyFiveToleranceBound = mean+toleranceBoundFactor*stdDev;
        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
        qDebug() << "precision" << precision;
        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//        QString ninetyFiveString(QString::number(afterPrecision, 'f', significantFigure));

        result.push_back(std::make_pair(afterPrecision, significantFigure));
    }
    //else if(percentile == 0.99)
    {
        estimated100pthPercentile = mean+2.326*stdDev;
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        double estDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(std::make_pair(afterPrecision, significantFigure));

        std::pair<double, double> gFactorResult = gFactor.lower_bound(v.size())->second;
        toleranceBoundFactor = gFactorResult.second;
        ninetyFiveToleranceBound = mean+toleranceBoundFactor*stdDev;
        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
//        double ninetyFiveDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(std::make_pair(afterPrecision, significantFigure));
//        result.push_back(std::make_pair(estDbl, ninetyFiveDbl));
    }
//    else if(percentile == 0.999)
    {
        estimated100pthPercentile = mean+3.09*stdDev;
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        double estDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(std::make_pair(afterPrecision, significantFigure));
//        result.push_back(std::make_pair(estDbl, 0.0));
    }
    return result;
}

std::vector<QString > Model::EUMethodI(bool rounded)
{
    if(this->residues.empty())
    {
        qDebug() << "Calling EUMethodI with empty residues!";
        return std::vector<QString>();
    }
    double estimated100pthPercentile = 0.0;
    double toleranceBoundFactor = 0.0;
    double ninetyFiveToleranceBound = 0.0;
    double precision= 0.0;
    int significantFigure = 0;
    double afterPrecision = 0.0;
    std::vector<double> v(this->residues);

    double mean = this->getMean(v);
    double stdDev = this->getStdDev(v);
    std::vector<QString > result;
    //if(percentile == 0.95)

//        qDebug() << "std dev" << stdDev;
//        qDebug() << "mean" << mean;
    estimated100pthPercentile = mean+1.645*stdDev;
    std::pair<double, double> gFactorResult = gFactor.lower_bound(v.size())->second;
    toleranceBoundFactor = gFactorResult.first;
//        qDebug() << "toleranceBoundFactor " << toleranceBoundFactor;
    ninetyFiveToleranceBound = mean+toleranceBoundFactor*stdDev;
    if(rounded)
    {
//        qDebug() << estimated100pthPercentile;
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//         estString(QString::number(afterPrecision, 'f', significantFigure));
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
        /*    */
        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//        QString ninetyFiveString(QString::number(afterPrecision, 'f', significantFigure));
//        result.push_back(std::make_pair(afterPrecision, significantFigure));
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
    {
        result.push_back(QString::number(estimated100pthPercentile));
        result.push_back(QString::number(ninetyFiveToleranceBound));

    }

    //else if(percentile == 0.99)

    estimated100pthPercentile = mean+2.326*stdDev;
    gFactorResult = gFactor.lower_bound(v.size())->second;
    toleranceBoundFactor = gFactorResult.second;
    ninetyFiveToleranceBound = mean+toleranceBoundFactor*stdDev;
    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
    //        double estDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));

        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
    //        double ninetyFiveDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
    {
        result.push_back(QString::number(estimated100pthPercentile));
        result.push_back(QString::number(ninetyFiveToleranceBound));

    }


//    else if(percentile == 0.999)

    estimated100pthPercentile = mean+3.09*stdDev;
    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));

    }
    else
    {
        result.push_back(QString::number(estimated100pthPercentile));
    }

    return result;
}


std::vector<std::pair<double, int> > Model::NAFTA()
{
    if(this->residues.empty())
    {
        qDebug() << "Calling NAFTA with empty residues!";
        return std::vector<std::pair<double, int> >();
    }
    std::vector<double> v(this->getLnResidues());
//    for(auto a:v)
//        qDebug() << a;
    double estimated100pthPercentile = 0.0;
    double toleranceBoundFactor = 0.0;
    double ninetyFiveToleranceBound = 0.0;
    double precision= 0.0;
    int significantFigure = 0;
    double afterPrecision = 0.0;

    double mean = this->getMean(v);
    double stdDev = this->getStdDev(v);
    std::vector<std::pair<double, int> > result;
    //if(percentile == 0.95)
    {
//        qDebug() << "std dev" << stdDev;
//        qDebug() << "mean" << mean;
        estimated100pthPercentile = exp(mean+1.645*stdDev);
//        qDebug() << estimated100pthPercentile;
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//         estString(QString::number(afterPrecision, 'f', significantFigure));
        result.push_back(std::make_pair(afterPrecision, significantFigure));
        //
        std::pair<double, double> gFactorResult = gFactor.lower_bound(v.size())->second;
        toleranceBoundFactor = gFactorResult.first;
//        qDebug() << "toleranceBoundFactor " << toleranceBoundFactor;
        ninetyFiveToleranceBound = exp(mean+toleranceBoundFactor*stdDev);
        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//        QString ninetyFiveString(QString::number(afterPrecision, 'f', significantFigure));

        result.push_back(std::make_pair(afterPrecision, significantFigure));
    }
    //else if(percentile == 0.99)
    {
        estimated100pthPercentile = exp(mean+2.326*stdDev);
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        double estDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(std::make_pair(afterPrecision, significantFigure));

        std::pair<double, double> gFactorResult = gFactor.lower_bound(v.size())->second;
        toleranceBoundFactor = gFactorResult.second;
        ninetyFiveToleranceBound = exp(mean+toleranceBoundFactor*stdDev);
        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
//        double ninetyFiveDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(std::make_pair(afterPrecision, significantFigure));
//        result.push_back(std::make_pair(estDbl, ninetyFiveDbl));
    }
//    else if(percentile == 0.999)
    {
        estimated100pthPercentile = exp(mean+3.09*stdDev);
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        double estDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(std::make_pair(afterPrecision, significantFigure));
//        result.push_back(std::make_pair(estDbl, 0.0));
    }
    return result;
}

std::vector<QString > Model::NAFTA(bool rounded)
{
    if(this->residues.empty())
    {
        qDebug() << "Calling NAFTA with empty residues!";
        return std::vector<QString>();
    }
    double estimated100pthPercentile = 0.0;
    double toleranceBoundFactor = 0.0;
    double ninetyFiveToleranceBound = 0.0;
    double precision= 0.0;
    int significantFigure = 0;
    double afterPrecision = 0.0;
    std::vector<double> v(this->getLnResidues());

    double mean = this->getMean(v);
    double stdDev = this->getStdDev(v);
    std::vector<QString > result;
    //if(percentile == 0.95)

//        qDebug() << "std dev" << stdDev;
//        qDebug() << "mean" << mean;
    estimated100pthPercentile = exp(mean+1.645*stdDev);
    std::pair<double, double> gFactorResult = gFactor.lower_bound(v.size())->second;
    toleranceBoundFactor = gFactorResult.first;
//        qDebug() << "toleranceBoundFactor " << toleranceBoundFactor;
    ninetyFiveToleranceBound = exp(mean+toleranceBoundFactor*stdDev);
    if(rounded)
    {
//        qDebug() << estimated100pthPercentile;
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(estimated100pthPercentile, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//         estString(QString::number(afterPrecision, 'f', significantFigure));
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
        /*    */
        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
//        QString ninetyFiveString(QString::number(afterPrecision, 'f', significantFigure));
//        result.push_back(std::make_pair(afterPrecision, significantFigure));
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
    {
        result.push_back(QString::number(estimated100pthPercentile));
        result.push_back(QString::number(ninetyFiveToleranceBound));

    }

    //else if(percentile == 0.99)

    estimated100pthPercentile = exp(mean+2.326*stdDev);
    gFactorResult = gFactor.lower_bound(v.size())->second;
    toleranceBoundFactor = gFactorResult.second;
    ninetyFiveToleranceBound = exp(mean+toleranceBoundFactor*stdDev);
    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
    //        double estDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));

        std::pair<double, int> ninetyFiveResult= rounding.lower_bound(ninetyFiveToleranceBound)->second;
        precision = ninetyFiveResult.first;
        significantFigure = ninetyFiveResult.second;
        afterPrecision = ceil(ninetyFiveToleranceBound, precision);
    //        double ninetyFiveDbl = QString::number(afterPrecision, 'f', significantFigure).toDouble();
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
    {
        result.push_back(QString::number(estimated100pthPercentile));
        result.push_back(QString::number(ninetyFiveToleranceBound));

    }


//    else if(percentile == 0.999)

    estimated100pthPercentile = exp(mean+3.09*stdDev);
    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(estimated100pthPercentile)->second;
        precision = roundingResult.first;
        significantFigure = roundingResult.second;
        afterPrecision = ceil(estimated100pthPercentile, precision);
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));

    }
    else
    {
        result.push_back(QString::number(estimated100pthPercentile));
    }

    return result;
}


double Model::percentile(std::vector<double> array, double p)
{
    int count = array.size();
    std::vector<double> v(array.begin(), array.end());
    std::sort(v.begin(), v.end());
    double tmp = (count-1)*p;
    int pos = (int)tmp;
    double percent = tmp-pos;
    return (1-percent)*v[pos]+percent*v[pos+1];
}

std::vector<QString > Model::EUMethodII(bool rounded)
{
    if(this->residues.empty())
    {
        qDebug() << "Calling EUMethodII with empty residues!";
        return std::vector<QString>();
    }
    std::vector<double> v(this->residues);
    int lens = v.size();
    double p = (0.75*lens-0.25)/(lens-1);
    double r = 2*Model::percentile(v, p);
    std::vector<QString> result;
    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(r)->second;
        double precision = roundingResult.first;
        int significantFigure = roundingResult.second;
//        qDebug() << "precision" << precision;
//        qDebug() << "significantFigure " << significantFigure;
        double afterPrecision = ceil(r, precision);
//        qDebug() << "est " << est;
//        qDebug() << "significantFigure "<< QString::number(est, 'f', significantFigure);
//        qDebug() << QString::number(afterPrecision, 'f', significantFigure);
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
        result.push_back(QString::number(r));

    return result;
}

std::vector<QString > Model::CaliMethodI(bool rounded)
{
    if(this->residues.empty())
    {
        qDebug() << "Calling Cali Method I with empty residues!";
        return std::vector<QString>();
    }
    std::vector<double> v(this->residues);
    double mean = this->getMean(v);
    double stdDev = this->getStdDev(v);
    std::vector<QString> result;
    double r = mean + 3*stdDev;
    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(r)->second;
        double precision = roundingResult.first;
        int significantFigure = roundingResult.second;
        double afterPrecision = ceil(r, precision);
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
        result.push_back(QString::number(r));

    return result;
}

std::vector<QString > Model::UPLMedian95th(bool rounded)
{
    if(this->residues.empty())
    {
        qDebug() << "Calling UPLMedian95th Method with empty residues!";
        return std::vector<QString>();
    }
    std::vector<double> v(this->residues);
    int size = v.size();
    std::vector<QString> result;

    /*
     * 参考  https://zh.wikipedia.org/wiki/%E5%AD%A6%E7%94%9Ft-%E5%88%86%E5%B8%83
     * 这里分双侧和单侧，双侧的90%对应单侧的10%。
    */
    boost::math::students_t dist(size-1);
    double tinv = boost::math::quantile(dist, 0.95);
    std::sort(v.begin(), v.end());
    double median = size%2? v[size/2] : (v[size/2-1] + v[size/2])/2;
    double r = median * std::exp(std::sqrt(ln(2))*(1.645+tinv/std::sqrt(size)));

    if(rounded)
    {
        std::pair<double, int> roundingResult= rounding.lower_bound(r)->second;
        double precision = roundingResult.first;
        int significantFigure = roundingResult.second;
        double afterPrecision = ceil(r, precision);
        result.push_back(QString::number(afterPrecision, 'f', significantFigure));
    }
    else
        result.push_back(QString::number(r));

    return result;
}
