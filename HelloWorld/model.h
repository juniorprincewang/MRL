#ifndef MODEL_H
#define MODEL_H
#include <QVector>
#include "ufunction.h"
#include <functional>   // std::greater
#include <map>
#include <QDebug>

const static std::map<double, std::pair<double, int>>::value_type init_rounding[10] =
{
    std::map<double, std::pair<double, int>>::value_type(0.000001 , std::make_pair(0.01  ,2)),
    std::map<double, std::pair<double, int>>::value_type(0.1      , std::make_pair(0.05  ,2)),
    std::map<double, std::pair<double, int>>::value_type(0.5      , std::make_pair(0.1   ,2)),
    std::map<double, std::pair<double, int>>::value_type(0.9      , std::make_pair(0.1   ,1)),
    std::map<double, std::pair<double, int>>::value_type(2        , std::make_pair(0.5   ,1)),
    std::map<double, std::pair<double, int>>::value_type(5        , std::make_pair(1     ,1)),
    std::map<double, std::pair<double, int>>::value_type(9        , std::make_pair(1     ,0)),
    std::map<double, std::pair<double, int>>::value_type(20       , std::make_pair(5     ,0)),
    std::map<double, std::pair<double, int>>::value_type(100      , std::make_pair(10    ,0)),
    std::map<double, std::pair<double, int>>::value_type(1000     , std::make_pair(100   ,0)),
};
const static std::map<double, std::pair<double, int>, std::greater<double> > rounding(init_rounding, init_rounding + 10);
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
const static std::map<int, std::pair<double, double>>::value_type r_critical_value[118] =
{
    std::map<int, std::pair<double, double>>::value_type(3   , std::make_pair(0.8687,  0.879)),
    std::map<int, std::pair<double, double>>::value_type(4   , std::make_pair(0.8234,  0.8666)),
    std::map<int, std::pair<double, double>>::value_type(5   , std::make_pair(0.824 ,  0.8786)),
    std::map<int, std::pair<double, double>>::value_type(6   , std::make_pair(0.8351,  0.888)),
    std::map<int, std::pair<double, double>>::value_type(7   , std::make_pair(0.8474,  0.897)),
    std::map<int, std::pair<double, double>>::value_type(8   , std::make_pair(0.859 ,  0.9043)),
    std::map<int, std::pair<double, double>>::value_type(9   , std::make_pair(0.8689,  0.9115)),
    std::map<int, std::pair<double, double>>::value_type(10  , std::make_pair(0.8765,  0.9173)),
    std::map<int, std::pair<double, double>>::value_type(11  , std::make_pair(0.8838,  0.9223)),
    std::map<int, std::pair<double, double>>::value_type(12  , std::make_pair(0.8918,  0.9267)),
    std::map<int, std::pair<double, double>>::value_type(13  , std::make_pair(0.8974,  0.931)),
    std::map<int, std::pair<double, double>>::value_type(14  , std::make_pair(0.9029,  0.9343)),
    std::map<int, std::pair<double, double>>::value_type(15  , std::make_pair(0.908 ,  0.9376)),
    std::map<int, std::pair<double, double>>::value_type(16  , std::make_pair(0.9121,  0.9405)),
    std::map<int, std::pair<double, double>>::value_type(17  , std::make_pair(0.916 ,  0.9433)),
    std::map<int, std::pair<double, double>>::value_type(18  , std::make_pair(0.9196,  0.9452)),
    std::map<int, std::pair<double, double>>::value_type(19  , std::make_pair(0.923 ,  0.9479)),
    std::map<int, std::pair<double, double>>::value_type(20  , std::make_pair(0.9256,  0.9498)),
    std::map<int, std::pair<double, double>>::value_type(21  , std::make_pair(0.9285,  0.9515)),
    std::map<int, std::pair<double, double>>::value_type(22  , std::make_pair(0.9308,  0.9535)),
    std::map<int, std::pair<double, double>>::value_type(23  , std::make_pair(0.9334,  0.9548)),
    std::map<int, std::pair<double, double>>::value_type(24  , std::make_pair(0.9356,  0.9564)),
    std::map<int, std::pair<double, double>>::value_type(25  , std::make_pair(0.937 ,  0.9575)),
    std::map<int, std::pair<double, double>>::value_type(26  , std::make_pair(0.9393,  0.959)),
    std::map<int, std::pair<double, double>>::value_type(27  , std::make_pair(0.9413,  0.96)),
    std::map<int, std::pair<double, double>>::value_type(28  , std::make_pair(0.9428,  0.9615)),
    std::map<int, std::pair<double, double>>::value_type(29  , std::make_pair(0.9441,  0.9622)),
    std::map<int, std::pair<double, double>>::value_type(30  , std::make_pair(0.9462,  0.9634)),
    std::map<int, std::pair<double, double>>::value_type(31  , std::make_pair(0.9476,  0.9644)),
    std::map<int, std::pair<double, double>>::value_type(32  , std::make_pair(0.949 ,  0.9652)),
    std::map<int, std::pair<double, double>>::value_type(33  , std::make_pair(0.9505,  0.9661)),
    std::map<int, std::pair<double, double>>::value_type(34  , std::make_pair(0.9521,  0.9671)),
    std::map<int, std::pair<double, double>>::value_type(35  , std::make_pair(0.953 ,  0.9678)),
    std::map<int, std::pair<double, double>>::value_type(36  , std::make_pair(0.954 ,  0.9686)),
    std::map<int, std::pair<double, double>>::value_type(37  , std::make_pair(0.9551,  0.9693)),
    std::map<int, std::pair<double, double>>::value_type(38  , std::make_pair(0.9555,  0.97)),
    std::map<int, std::pair<double, double>>::value_type(39  , std::make_pair(0.9568,  0.9704)),
    std::map<int, std::pair<double, double>>::value_type(40  , std::make_pair(0.9576,  0.9712)),
    std::map<int, std::pair<double, double>>::value_type(41  , std::make_pair(0.9589,  0.9719)),
    std::map<int, std::pair<double, double>>::value_type(42  , std::make_pair(0.9593,  0.9723)),
    std::map<int, std::pair<double, double>>::value_type(43  , std::make_pair(0.9609,  0.973)),
    std::map<int, std::pair<double, double>>::value_type(44  , std::make_pair(0.9611,  0.9734)),
    std::map<int, std::pair<double, double>>::value_type(45  , std::make_pair(0.962 ,  0.9739)),
    std::map<int, std::pair<double, double>>::value_type(46  , std::make_pair(0.9629,  0.9744)),
    std::map<int, std::pair<double, double>>::value_type(47  , std::make_pair(0.9637,  0.9748)),
    std::map<int, std::pair<double, double>>::value_type(48  , std::make_pair(0.964 ,  0.9753)),
    std::map<int, std::pair<double, double>>::value_type(49  , std::make_pair(0.9643,  0.9758)),
    std::map<int, std::pair<double, double>>::value_type(50  , std::make_pair(0.9654,  0.9761)),
    std::map<int, std::pair<double, double>>::value_type(55  , std::make_pair(0.9683,  0.9781)),
    std::map<int, std::pair<double, double>>::value_type(60  , std::make_pair(0.9706,  0.9797)),
    std::map<int, std::pair<double, double>>::value_type(65  , std::make_pair(0.9723,  0.9809)),
    std::map<int, std::pair<double, double>>::value_type(70  , std::make_pair(0.9742,  0.9822)),
    std::map<int, std::pair<double, double>>::value_type(75  , std::make_pair(0.9758,  0.9831)),
    std::map<int, std::pair<double, double>>::value_type(80  , std::make_pair(0.9771,  0.9841)),
    std::map<int, std::pair<double, double>>::value_type(85  , std::make_pair(0.9784,  0.985)),
    std::map<int, std::pair<double, double>>::value_type(90  , std::make_pair(0.9797,  0.9857)),
    std::map<int, std::pair<double, double>>::value_type(95  , std::make_pair(0.9804,  0.9864)),
    std::map<int, std::pair<double, double>>::value_type(100 , std::make_pair(0.9814,  0.9869)),
    std::map<int, std::pair<double, double>>::value_type(110 , std::make_pair(0.983 ,  0.9881)),
    std::map<int, std::pair<double, double>>::value_type(120 , std::make_pair(0.9841,  0.9889)),
    std::map<int, std::pair<double, double>>::value_type(130 , std::make_pair(0.9854,  0.9897)),
    std::map<int, std::pair<double, double>>::value_type(140 , std::make_pair(0.9865,  0.9904)),
    std::map<int, std::pair<double, double>>::value_type(150 , std::make_pair(0.9871,  0.9909)),
    std::map<int, std::pair<double, double>>::value_type(160 , std::make_pair(0.9879,  0.9915)),
    std::map<int, std::pair<double, double>>::value_type(170 , std::make_pair(0.9887,  0.9919)),
    std::map<int, std::pair<double, double>>::value_type(180 , std::make_pair(0.9891,  0.9923)),
    std::map<int, std::pair<double, double>>::value_type(190 , std::make_pair(0.9897,  0.9927)),
    std::map<int, std::pair<double, double>>::value_type(200 , std::make_pair(0.9903,  0.993)),
    std::map<int, std::pair<double, double>>::value_type(210 , std::make_pair(0.9907,  0.9933)),
    std::map<int, std::pair<double, double>>::value_type(220 , std::make_pair(0.991 ,  0.9936)),
    std::map<int, std::pair<double, double>>::value_type(230 , std::make_pair(0.9914,  0.9939)),
    std::map<int, std::pair<double, double>>::value_type(240 , std::make_pair(0.9917,  0.9941)),
    std::map<int, std::pair<double, double>>::value_type(250 , std::make_pair(0.9921,  0.9943)),
    std::map<int, std::pair<double, double>>::value_type(260 , std::make_pair(0.9924,  0.9945)),
    std::map<int, std::pair<double, double>>::value_type(270 , std::make_pair(0.9926,  0.9947)),
    std::map<int, std::pair<double, double>>::value_type(280 , std::make_pair(0.9929,  0.9949)),
    std::map<int, std::pair<double, double>>::value_type(290 , std::make_pair(0.9931,  0.9951)),
    std::map<int, std::pair<double, double>>::value_type(300 , std::make_pair(0.9933,  0.9952)),
    std::map<int, std::pair<double, double>>::value_type(310 , std::make_pair(0.9936,  0.9954)),
    std::map<int, std::pair<double, double>>::value_type(320 , std::make_pair(0.9937,  0.9955)),
    std::map<int, std::pair<double, double>>::value_type(330 , std::make_pair(0.9939,  0.9956)),
    std::map<int, std::pair<double, double>>::value_type(340 , std::make_pair(0.9941,  0.9957)),
    std::map<int, std::pair<double, double>>::value_type(350 , std::make_pair(0.9942,  0.9958)),
    std::map<int, std::pair<double, double>>::value_type(360 , std::make_pair(0.9944,  0.9959)),
    std::map<int, std::pair<double, double>>::value_type(370 , std::make_pair(0.9945,  0.996)),
    std::map<int, std::pair<double, double>>::value_type(380 , std::make_pair(0.9947,  0.9961)),
    std::map<int, std::pair<double, double>>::value_type(390 , std::make_pair(0.9948,  0.9962)),
    std::map<int, std::pair<double, double>>::value_type(400 , std::make_pair(0.9949,  0.9963)),
    std::map<int, std::pair<double, double>>::value_type(410 , std::make_pair(0.995 ,  0.9964)),
    std::map<int, std::pair<double, double>>::value_type(420 , std::make_pair(0.9951,  0.9965)),
    std::map<int, std::pair<double, double>>::value_type(430 , std::make_pair(0.9953,  0.9966)),
    std::map<int, std::pair<double, double>>::value_type(440 , std::make_pair(0.9954,  0.9966)),
    std::map<int, std::pair<double, double>>::value_type(450 , std::make_pair(0.9954,  0.9967)),
    std::map<int, std::pair<double, double>>::value_type(460 , std::make_pair(0.9955,  0.9968)),
    std::map<int, std::pair<double, double>>::value_type(470 , std::make_pair(0.9956,  0.9968)),
    std::map<int, std::pair<double, double>>::value_type(480 , std::make_pair(0.9957,  0.9969)),
    std::map<int, std::pair<double, double>>::value_type(490 , std::make_pair(0.9958,  0.9969)),
    std::map<int, std::pair<double, double>>::value_type(500 , std::make_pair(0.9959,  0.997)),
    std::map<int, std::pair<double, double>>::value_type(525 , std::make_pair(0.9961,  0.9972)),
    std::map<int, std::pair<double, double>>::value_type(550 , std::make_pair(0.9963,  0.9973)),
    std::map<int, std::pair<double, double>>::value_type(575 , std::make_pair(0.9964,  0.9974)),
    std::map<int, std::pair<double, double>>::value_type(600 , std::make_pair(0.9965,  0.9975)),
    std::map<int, std::pair<double, double>>::value_type(625 , std::make_pair(0.9967,  0.9976)),
    std::map<int, std::pair<double, double>>::value_type(650 , std::make_pair(0.9968,  0.9977)),
    std::map<int, std::pair<double, double>>::value_type(675 , std::make_pair(0.9969,  0.9977)),
    std::map<int, std::pair<double, double>>::value_type(700 , std::make_pair(0.997 ,  0.9978)),
    std::map<int, std::pair<double, double>>::value_type(725 , std::make_pair(0.9971,  0.9979)),
    std::map<int, std::pair<double, double>>::value_type(750 , std::make_pair(0.9972,  0.998)),
    std::map<int, std::pair<double, double>>::value_type(775 , std::make_pair(0.9973,  0.998)),
    std::map<int, std::pair<double, double>>::value_type(800 , std::make_pair(0.9974,  0.9981)),
    std::map<int, std::pair<double, double>>::value_type(825 , std::make_pair(0.9975,  0.9981)),
    std::map<int, std::pair<double, double>>::value_type(850 , std::make_pair(0.9975,  0.9982)),
    std::map<int, std::pair<double, double>>::value_type(875 , std::make_pair(0.9976,  0.9982)),
    std::map<int, std::pair<double, double>>::value_type(900 , std::make_pair(0.9977,  0.9983)),
    std::map<int, std::pair<double, double>>::value_type(925 , std::make_pair(0.9977,  0.9983)),
    std::map<int, std::pair<double, double>>::value_type(950 , std::make_pair(0.9978,  0.9984)),
    std::map<int, std::pair<double, double>>::value_type(975 , std::make_pair(0.9978,  0.9984)),
    std::map<int, std::pair<double, double>>::value_type(1000, std::make_pair(0.9979,  0.9984))
};
const static std::map<int, std::pair<double, double>, std::greater<int> > rCritical(r_critical_value, r_critical_value + 118);

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
    std::vector<std::pair<double, int> > EUMethodI();
    std::vector<QString> EUMethodI(bool rounded);
    std::vector<QString > EUMethodII(bool rounded);
    std::vector<std::pair<double, int> > NAFTA();   // 95/99 Rule
    std::vector<QString > NAFTA(bool rounded);   // 95/99 Rule
    std::vector<QString > CaliMethodI(bool rounded);   // 加利福尼亚方法1，即Mean+3SD
    std::vector<QString > UPLMedian95th(bool rounded); // UPLMedian95th 方法
    //Approximate Shapiro-Francia Normality Test Statistic
    // return
    // - 0  错误;
    // - 1  >99
    // - 2  95-99
    // - 3  <95
    int ShapiroFranciaNormalityTest(double rSquaredValue);

public:
    std::vector<double> residues;
    std::vector<double> getLnResidues();
private:
    std::vector<double> lnResidues;
    //
    double getStdDev(const std::vector<double>);
    double getMean(const std::vector<double>);
    double ceil(double, double);
    double percentile(std::vector<double>, double);
    // 运算中间结果
    double average;
    double median;
    double max_value;
    double min_value;
};


#endif // MODEL_H
