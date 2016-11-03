#include "model.h"
#include <cmath>
// for bind2nd
#include <functional>


Model::Model(std::vector<double> residues)
{
    this->residues = residues;
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

double Model::getMedian(const std::vector<double> v)
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

    double mean = this->getMedian(v);
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(),
                   std::bind2nd(std::minus<double>(), mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size());
    return stdev;
}

std::vector<double> Model::getLnResidues()
{
    if(this->lnResidues.empty())
        this->lnResidues = Model::getLnVector(this->residues);
    return this->lnResidues;
}

std::vector<std::pair<double, double> > Model::EUMethodI()
{
    if(this->residues.empty())
    {
        qDebug() << "Calling EUMethodI with empty residues!";
        return 0.0;
    }
    double Estimated100pthPercentile = 0.0;
    double ToleranceBoundFactor = 0.0;
    double NinetyFiveToleranceBound = 0.0;
    std::vector<double> v;
    if(log)
    {
        v = this->getLnResidues();
    }
    else
        v = this->residues;
    double mean = this->getMedian(v);
    double stdDev = this->getStdDev(v);
    std::vector<std::pair<double, double> > result;
    //if(percentile == 0.95)
    {
        Estimated100pthPercentile = mean+1.645*stdDev;
        std::pair<double, double> gFactorResult = gFactor.upper_bound(v.size())->second;
        ToleranceBoundFactor = gFactorResult.first;
        NinetyFiveToleranceBound = mean+ToleranceBoundFactor*stdDev;
        result.push_back(std::make_pair(Estimated100pthPercentile, NinetyFiveToleranceBound));
    }
    //else if(percentile == 0.99)
    {
        Estimated100pthPercentile = mean+2.326*stdDev;
        std::pair<double, double> gFactorResult = gFactor.upper_bound(v.size())->second;
        ToleranceBoundFactor = gFactorResult.second;
        NinetyFiveToleranceBound = mean+ToleranceBoundFactor*stdDev;
        result.push_back(std::make_pair(Estimated100pthPercentile, NinetyFiveToleranceBound));
    }
//    else if(percentile == 0.999)
    {
        Estimated100pthPercentile = mean+3.09*stdDev;
        result.push_back(std::make_pair(Estimated100pthPercentile, 0.0));
    }
    return result;
}
