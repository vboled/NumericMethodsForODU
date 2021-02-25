#include "../includes/NumericMethodsFODU.h"
//test1
double		test1Equation1(double t, std::vector<double> &x) {
	return 2 * x[0] + x[1] * x[1] - 1;
}	

double		test1Equation2(double t, std::vector<double> &x) {
	return 6 * x[0]- x[1] * x[1] + 1;
}