#include "../includes/NumericMethodsFODU.h"

using namespace std;

void	NumericODUSolver::rk4()
{
		// for (size_t j = 0; j < equations.size(); j++)
		// 	k1[j] = xi[j] + 0.5 * step * equations[j](tmp_t, xi);

        // for (size_t j = 0; j < equations.size(); j++)
		// 	k2[j] = xi[j] + 0.5 * step * equations[j](tmp_t + 0.5 * step, k1);

        // for (size_t j = 0; j < equations.size(); j++)
		// 	k3[j] = xi[j] + 0.5 * step * equations[j](tmp_t + 0.5 * step, k2);

        // for (size_t j = 0; j < equations.size(); j++)
		// 	k4[j] = equations[j](tmp_t + step, k3);

        // for (size_t j = 0; j < equations.size(); j++)
        //     kn[j] = 1 / 6 * k1[j] + 1 / 3 * k2[j] + 1 / 3 * k3[j] + 1 / 6 * k4[j];
	vector<double> xi, xj; // xj = x(i + 1)
	vector<double> k1, k2, k3, k4, kn, y_n;
	double b21 = 0.5;
	double b32 = 0.5;
	double b43 = 1;

	double a2 = 0.5, a3 = 0.5, a4 = 1;
	double s1 = 1. / 6, s2 = 2. / 6, s3 = 2. / 6, s4 = 1. / 6;
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
	k3.resize(equations.size());
	k4.resize(equations.size());
	kn.resize(equations.size());
	y_n.resize(equations.size());
	xi = initialCond;
	int n = (t - t0) / step;
	double tmp_t = t0;
	for (size_t i = 0; i <= n; i++)
	{
		out << t0 + i * step << " ";
		for (size_t j = 0; j < equations.size(); j++)
			k1[j] = equations[j](tmp_t, xi);
		for (size_t j = 0; j < equations.size(); j++)
			y_n[j] = xi[j] + step * b21 * k1[j];

		for (size_t j = 0; j < equations.size(); j++)
			k2[j] = equations[j](tmp_t + a2 * step, y_n);	
		for (size_t j = 0; j < equations.size(); j++)
			y_n[j] =  xi[j] + step * (b32 * k2[j]);
		
		for (size_t j = 0; j < equations.size(); j++)
			k3[j] = equations[j](tmp_t + a3 * step, y_n);	
		for (size_t j = 0; j < equations.size(); j++)
			y_n[j] = xi[j] + step * (b43 * k3[j]);
		
		for (size_t j = 0; j < equations.size(); j++)
			k4[j] = equations[j](tmp_t + a4 * step, y_n);

		for (size_t j = 0; j < equations.size(); j++)
			xj[j] = xi[j] + step * (s1 * k1[j] + s2 * k2[j] + s3 * k3[j] + s4 * k4[j]);

		countOfR += 4;
		for (size_t j = 0; j < equations.size(); j++)
		{
			out << xj[j] << " ";
		}
		out << endl;
		swap(xi, xj);
		tmp_t += step;
	}
	cout << "count of evaluate right: " << countOfR << endl;
	out.close();
}