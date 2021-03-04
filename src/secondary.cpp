#include "../includes/NumericMethodsFODU.h"

using namespace std;

double NumericODUSolver::residual() {
    ifstream set(outputFile);
    string str;
    getline(set, str);
    cout << "for " << str;
    getline(set, str);
    cout << " with " << str << " is:\n";
    double x = 0.0, max = 0.0, t = 0.0;
	while(set >> t)
	{
		for (std::size_t i = 0; i < functions.size(); i++)
		{
			set >> x;
			x = fabs(x - functions[i](t));
			if (x > max)
				max = x;
		}
	}
	return max;
}

