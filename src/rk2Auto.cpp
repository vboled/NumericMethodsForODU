#include "../includes/NumericMethodsFODU.h"

using namespace std;

vector<double> NumericODUSolver::oneStepRK2(vector<double> initCond, double step, double t) {
    vector<double> xi, xj; // xj = x(i + 1)
	vector<double> k1, k2;
	double b21 = 0.5, a2 = 0.5;
	xi.resize(equations.size());
	xj.resize(equations.size());
	k1.resize(equations.size());
	k2.resize(equations.size());
	xi = initCond;
	int n = (t - t0) / step;
	double tmp_t = t;
    for (size_t j = 0; j < equations.size(); j++)
        k1[j] = xi[j] + b21 * step * equations[j](tmp_t, xi);
    for (size_t j = 0; j < equations.size(); j++)
        k2[j] = equations[j](tmp_t + a2 * step, k1);
    for (size_t j = 0; j < equations.size(); j++)
        xj[j] = xi[j] + step * k2[j];
    return xj;
}

double  NumericODUSolver::infNorm(const vector<double> &vec) {
    double max = 0;
    for (const auto &t: vec) {
        if (fabs(t) > max)
            max = fabs(t);
    }
    return max;
}

void	NumericODUSolver::rk2Auto()
{
	vector<double> xi_1, xi1_2, xi1_1, xi, tmp;
	double b21 = 0.5, a2 = 0.5;
	ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
	int countOfR = 0;
	xi.resize(equations.size());
	xi_1.resize(equations.size());
    xi1_2.resize(equations.size());
    xi1_1.resize(equations.size());
    tmp.resize(equations.size());
	xi = initialCond;
	int n = (t - t0) / step;
	double tmp_t = t0, newStep = 0, error = 0;
    bool makeStep = false;
	for (size_t i = 0; i <= n; i++)
	{
        if (t0 + i * step > 2 * t)
            break;
        while (!makeStep) {
            xi_1 = oneStepRK2(xi, step, tmp_t);
            xi1_1 = oneStepRK2(xi, step / 2, tmp_t);
            xi1_2 = oneStepRK2(xi1_1, step / 2, tmp_t);
            for (int j = 0; j < equations.size(); j++)
                tmp[j] = xi1_2[j] - xi_1[j];
            error = infNorm(tmp) / (pow(2, equations.size()) - 1);
            if (error <= LOW) {
                out << t0 + i * step << " ";
                for (size_t j = 0; j < equations.size(); j++)
                    out << xi1_2[j] << " ";
                out << step << " ";
                out << endl;
                if (error <= LOW / 2)
                    step *= 2;
                tmp_t += step;
                xi = xi1_2;
                makeStep = true;
            } else {
                step /= 2;
                makeStep = false;
            }
        }
        makeStep = false;
	}
	cout << "count of evaluate right: " << countOfR;
	out.close();
}