#ifndef SKILETIZATIONFILTER_H
#define SKILETIZATIONFILTER_H
#include "abstractfilter.h"
#include "vector"

using namespace std;

class SkiletizationFilter : public AbstractFilter
{
public:
    void doFilter(QImage &image);    
    virtual QString* getDescription();
    SkiletizationFilter();    
private:
    vector<vector<int>> bitmap;
    vector<vector<int>> skeletonZhangSuen();
    int tla(vector<vector<int>> &image, int i, int j, vector<int> &p, int &b);
    void deleteMarked(vector<vector<int>> &markBmp, vector<vector<int>> &bitMap);
};

#endif // SKILETIZATIONFILTER_H
