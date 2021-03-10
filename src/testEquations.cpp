#include "../includes/NumericMethodsFODU.h"

//test1
double		test1Equation1(double t, std::vector<double> &x) {
	return 2 * x[0] + x[1] * x[1] - 1;
}	

double		test1Equation2(double t, std::vector<double> &x) {
	return 6 * x[0]- x[1] * x[1] + 1;
}

//test Pendulum

double		pendulumEquation1(double t, std::vector<double> &x) {
	return x[1];
}

double		pendulumEquation2(double t, std::vector<double> &x) {
	return -K / M * x[0];
}

double		pendulumExactSol1(double t) {
	return cos(sqrt(K / M) * t);
}

double		pendulumExactSol2(double t) {
	return -sqrt(K / M) * sin(sqrt(K / M) * t);
}

//mytest1 x1(t0) = 1, x2(t0) = 0
double      myTest1Equation1(double t, std::vector<double> &x) {
    return x[1];
}
double      myTest1Equation2(double t, std::vector<double> &x) {
    return -2 * x[1] - x[0] + t;
}

double myTest1ExactSol1(double t) {
    return 3 * exp(-t) + 2 * t * exp(-t) + t - 2;
}

double myTest1ExactSol2(double t) {
    return -2 * t * exp(-t) - exp(-t) +1;
}