#include "../includes/NumericMethodsFODU.h"

using namespace std;

vector<vector<double >> NumericODUSolver::fourStepRK4() {
    vector<vector<double >> res;

    res.resize(4);
	vector<double> xi, xj; // xj = x(i + 1)
	vector<double> k1, k2, k3, k4, kn, y_n;
	double b21 = 0.5;
	double b32 = 0.5;
	double b43 = 1;

	double a2 = 0.5, a3 = 0.5, a4 = 1;
	double s1 = 1. / 6, s2 = 2. / 6, s3 = 2. / 6, s4 = 1. / 6;
	xi.resize(equations.size());
	xj.resize(equations.size());
	k1.resize(equations.size());
	k2.resize(equations.size());
    k3.resize(equations.size());
	k4.resize(equations.size());
    kn.resize(equations.size());
    y_n.resize(equations.size());
	xi = initialCond;
	double tmp_t = t0;
    for (size_t i = 0; i < 4; i++)
	{
        res[i].resize(equations.size());
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
    int countOfR = 0;
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
        for (int j = 0; j < equations.size(); j++) {
            x_prognose[j] = xn[j] + step / 24 * (55 * equations[j](tmp_t, xn) - 59 * equations[j](tmp_t, xn_1) +
            37 * equations[j](tmp_t, xn_2) - 9 * equations[j](tmp_t, xn_3));
            countOfR += 4;
        }
        for (int j = 0; j < equations.size(); j++) {
            f_prognose[j] = equations[j](tmp_t, x_prognose);
            countOfR++;
        }
        //коррекция
        for (int j = 0; j < equations.size(); j++) {
            x_correction[j] = xn[j] + step / 24 * (9 * f_prognose[j] + 19 * equations[j](tmp_t, xn) -
            5 * equations[j](tmp_t, xn_1) + equations[j](tmp_t, xn_2));
            countOfR += 3;
            out << x_correction[j] << " ";
        }
        swap(xn_3, xn_2);
        swap(xn_2, xn_1);
        swap(xn_1, xn);
        swap(xn, x_correction);
        out << endl;
        tmp_t += step;
    }
    cout << "count of evaluate right: " << countOfR;
	out.close();
}