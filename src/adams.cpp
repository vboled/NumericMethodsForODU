#include "../includes/NumericMethodsFODU.h"

using namespace std;

void NumericODUSolver::adams() {
    vector<double> xn_3;
	vector<double> xn_2;
    vector<double> xn_1;
    vector<double> xn;
    vector<vector<double> > firstFourStep;

    firstFourStep.resize(4);
    xn_3.resize(equations.size());
	xn_2.resize(equations.size());
    xn_1.resize(equations.size());
    xn.resize(equations.size());

    ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
    firstFourStep = fourStepRK4();
	out << "method: " << method << endl;
	out << "test: " << test << endl;
    double tmp_t = t0;
    for (int i = 0; i < 4; i++) {
        out << tmp_t << " ";
        for (int j = 0; j < equations.size(); j++) {
            out << firstFourStep[i][j] << " ";
        }
        tmp_t += step;
        out << endl;
    }
    xn_3 = firstFourStep[0];
    xn_2 = firstFourStep[1];
    xn_1 = firstFourStep[2];
    xn = firstFourStep[3];

    vector<double> xn1;
    xn1.resize(equations.size());
	while (tmp_t < t) {
        out << step << " ";
        for (int j = 0; j < equations.size(); j++) {
            xn1[j] = xn[j] + step / 24 * (55 * equations[j](tmp_t, xn) - 59 * equations[j](tmp_t, xn_1) +
            37 * equations[j](tmp_t, xn_2) - 9 * equations[j](tmp_t, xn_3));
            out << xn1[j] << " ";
        }
        swap(xn_3, xn_2);
        swap(xn_2, xn_1);
        swap(xn_1, xn);
        swap(xn, xn1);
        out << endl;
        tmp_t += step;
    }
	out.close();
}