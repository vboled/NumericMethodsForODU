#include "../includes/NumericMethodsFODU.h"

using namespace std;

void NumericODUSolver::explicitEuler() {
    vector<double> x_old;
	vector<double> x_new;
	int countOfR = 0;
	ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }

    x_old.resize(equations.size());
	x_new.resize(equations.size());
    
	double step = (t - t0) / n;
    x_old = initialCond;
	out << t0 << " ";
	
	for (size_t j = 0; j < x_old.size(); j++)
		out << x_old[j] << " ";
	
	out << "\n";
	double tmp_t = t0;
	
	for (size_t  i = 1; i <= n; i++) {
		tmp_t += step;
		out << tmp_t << " ";

		for (size_t j = 0; j < x_old.size(); j++) {
			x_new[j] = x_old[j] + step * equations[j](tmp_t, x_old);
			countOfR++;
			out << x_new[j] << " ";
		}

		out << "\n";
		swap(x_old, x_new);
	}
	cout << "count of evaluate right: " << countOfR << endl;
	out.close();
}