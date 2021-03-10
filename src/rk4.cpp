#include "../includes/NumericMethodsFODU.h"

using namespace std;

void	NumericODUSolver::rk4()
{
	vector<double> xi, xj; // xj = x(i + 1)
	vector<double> k1, k2, k3, k4, kn;
	double b2 = 0.5;
    double a2 = 0.5, b1 = 0.5, a3 = 0.5, b3 = 0.5, a4 = 1.0, b4 = 1.0;
    double s1 = 1/6, s2 = 1/3, s3 = 1/3, s4 = 1/6;
	ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
	xi.resize(equations.size());
	xj.resize(equations.size());
	k1.resize(equations.size());
	k2.resize(equations.size());
    k3.resize(equations.size());
	k4.resize(equations.size());
    kn.resize(equations.size());
	xi = initialCond;
	int n = (t - t0) / step;
	int countOfR = 0;
	double tmp_t = t0;
    out << "method: " << method << endl;
	out << "test: " << test << endl;
    for (size_t i = 0; i <= n; i++)
	{
        out << t0 + i * step << " ";
		for (size_t j = 0; j < equations.size(); j++)
			k1[j] = xi[j] + b1 * step * equations[j](tmp_t, xi);

        for (size_t j = 0; j < equations.size(); j++)
			k2[j] = xi[j] + b2 * step * equations[j](tmp_t + a2 * step, k1);

        for (size_t j = 0; j < equations.size(); j++)
			k3[j] = xi[j] + b3 * step * equations[j](tmp_t + a3 * step, k2);

        for (size_t j = 0; j < equations.size(); j++)
			k4[j] = b4 * step * equations[j](tmp_t + a4 * step, k3);

        for (size_t j = 0; j < equations.size(); j++)
            kn[j] = s1 * k1[j] + s2 * k2[j] + s3 * k3[j] + s4 * k4[j];

		countOfR += equations.size() * 4;

        for (size_t j = 0; j < equations.size(); j++) {
            xj[j] = xi[j] + step * kn[j];
            out << xj[j] << " ";
        }
		out << "\n";
		swap(xi, xj);
		tmp_t += step;
	}
	cout << "count of evaluation right: " << countOfR << endl;
	out.close();
}