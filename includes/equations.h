#pragma once
// test1
double		test1Equation1(double t, std::vector<double> &x);
double		test1Equation2(double t, std::vector<double> &x);

//testPendulum x1(0) = 1, x2(0) = 0
double		pendulumEquation1(double t, std::vector<double> &x); // equations discribing movement of the ball
double		pendulumEquation2(double t, std::vector<double> &x);
double		pendulumExactSol1(double t);
double		pendulumExactSol2(double t);

//mytest1 x1(t0) = 1, x2(t0) = 0
double      myTest1Equation1(double t, std::vector<double> &x);
double      myTest1Equation2(double t, std::vector<double> &x);
double      myTest1ExactSol1(double t);
double      myTest1ExactSol2(double t);