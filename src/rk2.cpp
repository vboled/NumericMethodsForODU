#include "../includes/NumericMethodsFODU.h"

using namespace std;

void	NumericODUSolver::rk2()
{
vector<double> xi, xj; // xj = x(i + 1)
	vector<double> k1, k2;
	double b21 = 0.5, a2 = 0.5;
	ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
	int countOfR = 0;
	xi.resize(equations.size());
	xj.resize(equations.size());
	k1.resize(equations.size());
	k2.resize(equations.size());
	xi = initialCond;
	int n = (t - t0) / step;
	double tmp_t = t0;
    out << "method: " << method << endl;
	out << "test: " << test << endl;
	for (size_t i = 0; i <= n; i++)
	{
		for (size_t j = 0; j < equations.size(); j++)
			k1[j] = xi[j] + b21 * step * equations[j](tmp_t, xi);
		out << t0 + i * step << " ";
		for (size_t j = 0; j < equations.size(); j++)
			k2[j] = equations[j](tmp_t + a2 * step, k1);
		countOfR += equations.size() * 2;
		for (size_t j = 0; j < equations.size(); j++)
		{
			xj[j] = xi[j] + step * k2[j];
			out << xj[j] << " ";
		}
		out << "\n";
		swap(xi, xj);
		tmp_t += step;
	}
	cout << "count of evaluate right: " << countOfR << endl;
	out.close();
}