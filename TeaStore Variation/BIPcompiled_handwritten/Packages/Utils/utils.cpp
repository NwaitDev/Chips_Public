#include "utils.hpp"



double curve(int time, int maxtime){
	return ((double)(maxtime-time))/((double)maxtime);
	//return 0.48;
	//return sin(6*(double)(time)/((double)maxtime))*0.5 + 0.5;
}

bool ltlt(double lowerbound, double middlebound, double upperbound){
	return lowerbound < middlebound && middlebound < upperbound;
}

bool leqleq(double lowerbound, double middlebound, double upperbound){
	return lowerbound <= middlebound && middlebound <= upperbound;
}

