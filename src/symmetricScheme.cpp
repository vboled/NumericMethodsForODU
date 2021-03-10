#include "../includes/NumericMethodsFODU.h"

using namespace std;

void NumericODUSolver::symmetricScheme() {
    vector<double> x_old;
	vector<double> x_new;

	ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }

    x_old.resize(equations.size());
	x_new.resize(equations.size());
    
	double step = (t - t0) / n;
    x_old = initialCond;
	out << "method: " << method << endl;
	out << "test: " << test << endl;
	out << t0 << " ";
	
	for (size_t j = 0; j < x_old.size(); j++)
		out << x_old[j] << " ";
	
	out << "\n";
	double tmp_t = t0;
	
	for (size_t  i = 1; i <= n; i++) {
		tmp_t += step;
		out << tmp_t << " ";
		x_new = newtonMethod(step, x_old, x_old, equations, F);
		for (std::size_t j = 0; j < x_new.size(); j++)
			out << x_new[j] << " ";
		out << "\n";
		// swap(x_old, x_new);
	}

	out.close();
}