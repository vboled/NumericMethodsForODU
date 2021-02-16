#include "../includes/NumericMethodsFODU.h"

using namespace std;

class NumericODUSolver {
private:
    vector<vector<double>> sol;
	// std::vector<eq> equations;
	std::vector<double> initial_cond;
	// std::vector<fun> functions;
	double t0;
	double t;
	double n;
	double step;
	string method;
	string out_file;
public:
    NumericODUSolver(string inputfile) {

    }
};