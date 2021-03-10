#include "../includes/NumericMethodsFODU.h"

using namespace std;

vector<vector<double >> NumericODUSolver::fourStepRK4() {
    vector<vector<double >> res;

    res.resize(4);
	vector<double> xi, xj; // xj = x(i + 1)
	vector<double> k1, k2, k3, k4, kn;
	double b2 = 0.5;
    double a2 = 0.5, b1 = 0.5, a3 = 0.5, b3 = 0.5, a4 = 1.0, b4 = 1.0;
    double s1 = 1/6, s2 = 1/3, s3 = 1/3, s4 = 1/6;
	xi.resize(equations.size());
	xj.resize(equations.size());
	k1.resize(equations.size());
	k2.resize(equations.size());
    k3.resize(equations.size());
	k4.resize(equations.size());
    kn.resize(equations.size());
	xi = initialCond;
	double tmp_t = t0;
    for (size_t i = 0; i < 4; i++)
	{
        res[i].resize(equations.size());
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

        for (size_t j = 0; j < equations.size(); j++) {
            xj[j] = xi[j] + step * kn[j];
        }
		swap(xi, xj);
        res[i] = xj;
		tmp_t += step;
	}
	return res;
}

void NumericODUSolver::predictionAndCorrection() {
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

    vector<double> x_prognose;
    vector<double> f_prognose;
    vector<double> x_correction;
    x_correction.resize(equations.size());
    x_prognose.resize(equations.size());
    f_prognose.resize(equations.size());
	while (tmp_t < t) {
        out << step << " ";
        //прогноз
        for (int j = 0; j < equations.size(); j++)
            x_prognose[j] = xn[j] + step / 24 * (55 * equations[j](tmp_t, xn) - 59 * equations[j](tmp_t, xn_1) +
            37 * equations[j](tmp_t, xn_2) - 9 * equations[j](tmp_t, xn_3));
        for (int j = 0; j < equations.size(); j++)
            f_prognose[j] = equations[j](tmp_t, x_prognose);
        //коррекция
        for (int j = 0; j < equations.size(); j++) {
            x_correction[j] = xn[j] + step / 24 * (9 * f_prognose[j] + 19 * equations[j](tmp_t, xn) -
            5 * equations[j](tmp_t, xn_1) + equations[j](tmp_t, xn_2));
            out << x_correction[j] << " ";
        }
        swap(xn_3, xn_2);
        swap(xn_2, xn_1);
        swap(xn_1, xn);
        swap(xn, x_correction);
        out << endl;
        tmp_t += step;
    }
	out.close();
}