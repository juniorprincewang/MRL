#include "ufunction.h"
#include "ndtri.h"
#include <cfloat>
#include <algorithm>
#include <vector>
#include <QDebug>


double ln(double source)
{
    return log(source);
}
// position位置的累计分布概率
double cdf(double position)
{
    return 0.5 * erfc(-position * sqrt(0.5));
}
// 概率对应的正态分布的分位点
double ppf(double percent)
{
    return ndtri(percent);
}
/*
std::vector<int> rank(std::vector<double> arr)
{
    // Original array
//    int arr[] = {3, 2, 3, 4};
    // Size of original array
    const int sz = static_cast<int>(sizeof arr / sizeof arr[0]);
    // Array of pair {.first = item, .second = 1-based index
    std::vector<std::pair<int, int> > vp(sz); // std::array if size is fixed
    for(int i = 0; i < sz; ++i) vp[i] = std::make_pair(arr[i], i + 1);
    // Sort the array, original array remains unchanged
    std::sort(vp.begin(), vp.end());
    std::vector<int> rank_position;
    // Print the result
    for(int i = 0; i < sz; ++i)
    {
        if(i!=0 && vp[i].first == vp[i-1].first)
        {
            rank_position.push_back(rank_position.back());

        }
        else
            rank_position.push_back(i+1);
        qDebug() << rank_position.back() <<' ' <<vp[i].first << ' ' << vp[i].second;
    }
    return rank_position;
}
*/

bool myfunction (std::pair<double, int> i,std::pair<double, int> j) { return (i.first> j.first); }
std::vector<int> rank(std::vector<double> arr, int flag)
{
    // Size of original array
    const int sz = arr.size();
    // Array of pair {.first = item, .second = 1-based index
    std::vector<std::pair<double, int> > vp(sz); // std::array if size is fixed
    for(int i = 0; i < sz; ++i)
        vp[i] = std::make_pair(arr[i], i + 1);  /* Can be done in a more fancy way using std::transform + lambda */
    // Sort the array, original array remains unchanged
    if(flag)    // 降序
        std::sort(vp.begin(), vp.end(), myfunction);
    else
        std::sort(vp.begin(), vp.end());
    std::vector<int> rank_position;
    std::vector<int> result(sz);
    // Print the result
    for(int i = 0; i < sz; ++i)
    {
        if(i!=0 && vp[i].first == vp[i-1].first)
        {
            rank_position.push_back(rank_position.back());

        }
        else
            rank_position.push_back(i+1);
        result[vp[i].second-1] = rank_position.back();
//        qDebug() << rank_position.back() <<' ' <<vp[i].first << ' ' << vp[i].second;
    }
    return result;
}

int countIf(std::vector<double> arr, double target)
{
    int count = 0;
    for(auto a:arr)
    {
        if(a==target)   count++;
    }
    return count;
}

