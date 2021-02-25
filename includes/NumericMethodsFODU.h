# pragma once

#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include "equations.h"
#include <fstream>

#define M 0.3
#define K 20

typedef double(*eq) (double t, std::vector<double> &x);
typedef std::vector<double>(*method_func) (double tau, std::vector<double> &yn, 
		std::vector<double> &ym, std::vector<eq> &functions);
typedef double(*fun) (double t);

class NumericODUSolver {
private:
    std::vector<std::vector<double> > sol;
	std::vector<eq> equations;
	std::vector<double> initialCond;
	std::vector<fun> functions;
	double r;
	double a;
	double t0;
	double t;
	double n;
	double step;
	std::string test;
	std::string method;
	std::string outputFile;

public:
    NumericODUSolver(std::string inputfile);
    void explicitEuler();
	void rk2();
	void rk4();
    void printSolver();
	double residual();
    std::string getMethod() {return method;}
	std::vector<double> getInitialCond() {return initialCond;}
	std::string getTest() {return test;}
};