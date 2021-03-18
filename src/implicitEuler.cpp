#include "../includes/NumericMethodsFODU.h"

using namespace std;

void NumericODUSolver::implicitEuler() {
std::vector<double> x_old; // x_new = x(i + 1)
	std::vector<double> x_new;
	method_func F = imp_eur_eq;
	std::ofstream out(outputFile);
	double step = (t - t0) / n;
	x_old.resize(equations.size());
	x_new.resize(equations.size());
	x_old = initialCond;
	out << t0 << " ";
	for (std::size_t j = 0; j < x_new.size(); j++)
	{
		out << x_old[j] << " ";
	}
	out << "\n";
	double tmp_t = t0;
	double t = 0;
	double countOfEq = 0;
	double countOfR = 0;
	for (std::size_t  i = 1; i <= n; i++)
	{
		tmp_t += step;
		out << tmp_t << " ";
		std::vector<double> tmp_v(x_new.size());
		for (std::size_t j = 0; j < x_old.size(); j++)
			tmp_v[j] = x_old[j] + step * equations[j](tmp_t, x_old);
		countOfR++;
		x_new = newtonMethod(step, x_old, tmp_v, equations, F, t);
		countOfEq++;
		for (std::size_t j = 0; j < x_new.size(); j++)
			out << x_new[j] << " ";
		out << "\n";
		swap(x_old, x_new);
	}
	out.close();
	cout << "num of countOfEq" << countOfEq << endl;
	cout << "num of countOfR" << countOfR << endl;
}