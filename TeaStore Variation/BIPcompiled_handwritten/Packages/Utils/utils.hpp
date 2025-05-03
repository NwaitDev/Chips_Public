#ifndef __UTILS_H__
#define __UTILS_H__

double curve(int time, int maxtime);

bool ltlt(double lowerbound, double middlebound, double upperbound);
bool leqleq(double lowerbound, double middlebound, double upperbound);

inline int asint(float f){return (int)f;}
inline float asfloat(int i){return (float)i;}

#endif //__UTILS_H__