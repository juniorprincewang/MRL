#ifndef MODEL_H
#define MODEL_H
#include <QVector>
#include "ufunction.h"
#include <functional>   // std::greater
#include <map>
#include <QDebug>

const static std::map<double, std::pair<double, double>>::value_type init_rounding[10] =
{
    std::map<int, std::pair<double, double>>::value_type(0.000001 , std::make_pair(0.01  ,0.00)),
    std::map<int, std::pair<double, double>>::value_type(0.1      , std::make_pair(0.05  ,0.00)),
    std::map<int, std::pair<double, double>>::value_type(0.5      , std::make_pair(0.1   ,0.00)),
    std::map<int, std::pair<double, double>>::value_type(0.9      , std::make_pair(0.1   , 0.0)),
    std::map<int, std::pair<double, double>>::value_type(2        , std::make_pair(0.5   , 0.0)),
    std::map<int, std::pair<double, double>>::value_type(5        , std::make_pair(1     , 0.0)),
    std::map<int, std::pair<double, double>>::value_type(9        , std::make_pair(1     ,   0)),
    std::map<int, std::pair<double, double>>::value_type(20       , std::make_pair(5     ,   0)),
    std::map<int, std::pair<double, double>>::value_type(100      , std::make_pair(10    ,   0)),
    std::map<int, std::pair<double, double>>::value_type(1000     , std::make_pair(100   ,   0)),
};
const static std::map<double, std::pair<double, double>, std::greater<int> > rounding(init_rounding, init_rounding + 99);
const static std::map<int, std::pair<double, double>>::value_type init_value[99] =
{
    std::map<int, std::pair<double, double>>::value_type(2 , std::make_pair(26.260 ,37.094)),
    std::map<int, std::pair<double, double>>::value_type(3 , std::make_pair(7.656  ,10.533)),
    std::map<int, std::pair<double, double>>::value_type(4 , std::make_pair( 5.144  ,7.042)),
    std::map<int, std::pair<double, double>>::value_type(5 , std::make_pair( 4.203  ,5.741)),
    std::map<int, std::pair<double, double>>::value_type(6 , std::make_pair( 3.708  ,5.062)),
    std::map<int, std::pair<double, double>>::value_type(7 , std::make_pair( 3.399  ,4.642)),
    std::map<int, std::pair<double, double>>::value_type(8 , std::make_pair( 3.187  ,4.354)),
    std::map<int, std::pair<double, double>>::value_type(9 , std::make_pair( 3.031  ,4.143)),
    std::map<int, std::pair<double, double>>::value_type(10, std::make_pair( 2.911  ,3.981)),
    std::map<int, std::pair<double, double>>::value_type(11, std::make_pair( 2.815  ,3.852)),
    std::map<int, std::pair<double, double>>::value_type(12, std::make_pair( 2.736  ,3.747)),
    std::map<int, std::pair<double, double>>::value_type(13, std::make_pair( 2.671  ,3.659)),
    std::map<int, std::pair<double, double>>::value_type(14, std::make_pair( 2.614  ,3.585)),
    std::map<int, std::pair<double, double>>::value_type(15, std::make_pair( 2.566  ,3.520)),
    std::map<int, std::pair<double, double>>::value_type(16, std::make_pair( 2.524  ,3.464)),
    std::map<int, std::pair<double, double>>::value_type(17, std::make_pair( 2.486  ,3.414)),
    std::map<int, std::pair<double, double>>::value_type(18, std::make_pair( 2.453  ,3.370)),
    std::map<int, std::pair<double, double>>::value_type(19, std::make_pair( 2.423  ,3.331)),
    std::map<int, std::pair<double, double>>::value_type(20, std::make_pair( 2.396  ,3.295)),
    std::map<int, std::pair<double, double>>::value_type(21, std::make_pair( 2.371  ,3.263)),
    std::map<int, std::pair<double, double>>::value_type(22, std::make_pair( 2.349  ,3.233)),
    std::map<int, std::pair<double, double>>::value_type(23, std::make_pair( 2.328  ,3.206)),
    std::map<int, std::pair<double, double>>::value_type(24, std::make_pair( 2.309  ,3.181)),
    std::map<int, std::pair<double, double>>::value_type(25, std::make_pair( 2.292  ,3.158)),
    std::map<int, std::pair<double, double>>::value_type(26, std::make_pair( 2.275  ,3.136)),
    std::map<int, std::pair<double, double>>::value_type(27, std::make_pair( 2.260  ,3.116)),
    std::map<int, std::pair<double, double>>::value_type(28, std::make_pair( 2.246  ,3.098)),
    std::map<int, std::pair<double, double>>::value_type(29, std::make_pair( 2.232  ,3.080)),
    std::map<int, std::pair<double, double>>::value_type(30, std::make_pair( 2.220  ,3.064)),
    std::map<int, std::pair<double, double>>::value_type(31, std::make_pair( 2.208  ,3.050)),
    std::map<int, std::pair<double, double>>::value_type(32, std::make_pair( 2.197  ,3.034)),
    std::map<int, std::pair<double, double>>::value_type(33, std::make_pair( 2.186  ,3.020)),
    std::map<int, std::pair<double, double>>::value_type(34, std::make_pair( 2.176  ,3.007)),
    std::map<int, std::pair<double, double>>::value_type(35, std::make_pair( 2.167  ,2.995)),
    std::map<int, std::pair<double, double>>::value_type(36, std::make_pair( 2.158  ,2.983)),
    std::map<int, std::pair<double, double>>::value_type(37, std::make_pair( 2.149  ,2.972)),
    std::map<int, std::pair<double, double>>::value_type(38, std::make_pair( 2.141  ,2.961)),
    std::map<int, std::pair<double, double>>::value_type(39, std::make_pair( 2.133  ,2.951)),
    std::map<int, std::pair<double, double>>::value_type(40, std::make_pair( 2.125  ,2.941)),
    std::map<int, std::pair<double, double>>::value_type(41, std::make_pair( 2.119  ,2.932)),
    std::map<int, std::pair<double, double>>::value_type(42, std::make_pair( 2.112  ,2.923)),
    std::map<int, std::pair<double, double>>::value_type(43, std::make_pair( 2.105  ,2.915)),
    std::map<int, std::pair<double, double>>::value_type(44, std::make_pair( 2.099  ,2.906)),
    std::map<int, std::pair<double, double>>::value_type(45, std::make_pair( 2.093  ,2.898)),
    std::map<int, std::pair<double, double>>::value_type(46, std::make_pair( 2.125  ,2.891)),
    std::map<int, std::pair<double, double>>::value_type(47, std::make_pair( 2.087  ,2.884)),
    std::map<int, std::pair<double, double>>::value_type(48, std::make_pair( 2.081  ,2.876)),
    std::map<int, std::pair<double, double>>::value_type(49, std::make_pair( 2.076  ,2.870)),
    std::map<int, std::pair<double, double>>::value_type(50, std::make_pair( 2.071  ,2.862)),
    std::map<int, std::pair<double, double>>::value_type(51, std::make_pair( 2.065  ,2.857)),
    std::map<int, std::pair<double, double>>::value_type(52, std::make_pair( 2.061  ,2.851)),
    std::map<int, std::pair<double, double>>::value_type(53, std::make_pair( 2.056  ,2.845)),
    std::map<int, std::pair<double, double>>::value_type(54, std::make_pair( 2.051  ,2.839)),
    std::map<int, std::pair<double, double>>::value_type(55, std::make_pair( 2.047  ,2.833)),
    std::map<int, std::pair<double, double>>::value_type(56, std::make_pair( 2.042  ,2.828)),
    std::map<int, std::pair<double, double>>::value_type(57, std::make_pair( 2.038  ,2.823)),
    std::map<int, std::pair<double, double>>::value_type(58, std::make_pair( 2.034  ,2.818)),
    std::map<int, std::pair<double, double>>::value_type(59, std::make_pair( 2.030  ,2.813)),
    std::map<int, std::pair<double, double>>::value_type(60, std::make_pair( 2.026  ,2.807)),
    std::map<int, std::pair<double, double>>::value_type(61, std::make_pair( 2.022  ,2.803)),
    std::map<int, std::pair<double, double>>::value_type(62, std::make_pair( 2.019  ,2.799)),
    std::map<int, std::pair<double, double>>::value_type(63, std::make_pair( 2.012  ,2.794)),
    std::map<int, std::pair<double, double>>::value_type(64, std::make_pair( 2.009  ,2.790)),
    std::map<int, std::pair<double, double>>::value_type(65, std::make_pair( 2.006  ,2.786)),
    std::map<int, std::pair<double, double>>::value_type(66, std::make_pair( 2.002  ,2.782)),
    std::map<int, std::pair<double, double>>::value_type(67, std::make_pair( 1.999  ,2.778)),
    std::map<int, std::pair<double, double>>::value_type(68, std::make_pair( 1.996  ,2.774)),
    std::map<int, std::pair<double, double>>::value_type(69, std::make_pair( 1.993  ,2.770)),
    std::map<int, std::pair<double, double>>::value_type(70, std::make_pair( 1.990  ,2.766)),
    std::map<int, std::pair<double, double>>::value_type(71, std::make_pair( 1.988  ,2.763)),
    std::map<int, std::pair<double, double>>::value_type(72, std::make_pair( 1.985  ,2.759)),
    std::map<int, std::pair<double, double>>::value_type(73, std::make_pair( 1.982  ,2.756)),
    std::map<int, std::pair<double, double>>::value_type(74, std::make_pair( 1.980  ,2.753)),
    std::map<int, std::pair<double, double>>::value_type(75, std::make_pair( 1.977  ,2.748)),
    std::map<int, std::pair<double, double>>::value_type(76, std::make_pair( 1.975  ,2.745)),
    std::map<int, std::pair<double, double>>::value_type(77, std::make_pair( 1.972  ,2.742)),
    std::map<int, std::pair<double, double>>::value_type(78, std::make_pair( 1.970  ,2.739)),
    std::map<int, std::pair<double, double>>::value_type(79, std::make_pair( 1.967  ,2.736)),
    std::map<int, std::pair<double, double>>::value_type(80, std::make_pair( 1.965  ,2.733)),
    std::map<int, std::pair<double, double>>::value_type(81, std::make_pair( 1.963  ,2.730)),
    std::map<int, std::pair<double, double>>::value_type(82, std::make_pair( 1.961  ,2.727)),
    std::map<int, std::pair<double, double>>::value_type(83, std::make_pair( 1.959  ,2.724)),
    std::map<int, std::pair<double, double>>::value_type(84, std::make_pair( 1.956  ,2.722)),
    std::map<int, std::pair<double, double>>::value_type(85, std::make_pair( 1.954  ,2.719)),
    std::map<int, std::pair<double, double>>::value_type(86, std::make_pair( 1.952  ,2.717)),
    std::map<int, std::pair<double, double>>::value_type(87, std::make_pair( 1.950  ,2.714)),
    std::map<int, std::pair<double, double>>::value_type(88, std::make_pair( 1.948  ,2.711)),
    std::map<int, std::pair<double, double>>::value_type(89, std::make_pair( 1.946  ,2.709)),
    std::map<int, std::pair<double, double>>::value_type(90, std::make_pair( 1.945  ,2.707)),
    std::map<int, std::pair<double, double>>::value_type(91, std::make_pair( 1.943  ,2.704)),
    std::map<int, std::pair<double, double>>::value_type(92, std::make_pair( 1.941  ,2.702)),
    std::map<int, std::pair<double, double>>::value_type(93, std::make_pair( 1.939  ,2.699)),
    std::map<int, std::pair<double, double>>::value_type(94, std::make_pair( 1.937  ,2.697)),
    std::map<int, std::pair<double, double>>::value_type(95, std::make_pair( 1.936  ,2.695)),
    std::map<int, std::pair<double, double>>::value_type(96, std::make_pair( 1.933  ,2.693)),
    std::map<int, std::pair<double, double>>::value_type(97, std::make_pair( 1.931  ,2.691)),
    std::map<int, std::pair<double, double>>::value_type(98, std::make_pair( 1.930  ,2.689)),
    std::map<int, std::pair<double, double>>::value_type(99, std::make_pair( 1.928  ,2.686)),
    std::map<int, std::pair<double, double>>::value_type(10, std::make_pair( 1.927  ,2.684)),

};
const static std::map<int, std::pair<double, double>, std::greater<int> > gFactor(init_value, init_value + 99);

class Model
{
public:
    Model();
    Model(std::vector<double> residues);
    ~Model();
    static std::vector<double> getZScoreVector(std::vector<double>);
    static std::vector<double> getLnVector(std::vector<double>);
// 模型接口
public:
    std::vector<std::pair<double, double> > EUMethodI();
    double EUMethodII();
    double UCLMedian95th();
    double Mean3SD();     // 加利福尼亚方法，Xbar+3*SD = 均值+3*方差
    double NAFTA();       // 95/99 Rule
public:
    std::vector<double> residues;
    std::vector<double> getLnResidues();
private:
    //
    double getStdDev(const std::vector<double>);
    double getMedian(const std::vector<double>);
    std::vector<double> lnResidues;
    // 运算中间结果
    double average;
    double median;
    double max_value;
    double min_value;
};


#endif // MODEL_H