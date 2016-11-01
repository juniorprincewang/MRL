#ifndef UFUNCTION_H
#define UFUNCTION_H

#include <cmath>
#include <QVector>


//#ifdef __cplusplus
//extern "C" {
//#endif

double ln(double );      // 获得以e为底的自然对数
double zScore(double);  // 计算取对数后的值在正态分布的分位数
double cdf(double );     // 正太分布的累计分布函数
double ppf(double );     // cdf的相反值
//std::vector<int> rank(std::vector<double> );  // 返回一列数字的数字排位
std::vector<int> rank(std::vector<double>, int);         //返回一列数字的数字排位, 第二个参数为真时，降序排列
int countIf(std::vector<double> , double );     // 返回满足条件的个数

//#ifdef __cplusplus
//}
//#endif

#endif // UFUNCTION_H
