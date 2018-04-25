#ifndef KERNELS_H
#define KERNELS_H
#include <array>

template<class T,size_t Rows,size_t Cols> using matrix=std::array<std::array<T,Cols>,Rows>;

const matrix<int,2,2> robertsx{{{{1,0}},{{0,-1}}}};
const matrix<int,2,2> robertsy{{{{0,1}},{{-1,0}}}};
const matrix<int,2,5> prewittx{{{{1,1,1,1,1,}},{{-1,-1,-1,-1,-1}}}};
const matrix<int,2,5> prewitty{{{{1,1,1,1,1}},{{-1,-1,-1,-1,-1}}}};
#endif // KERNELS_H
