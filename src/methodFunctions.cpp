#include "../includes/NumericMethodsFODU.h"

std::vector<double>		imp_eur_eq(double tau, std::vector<double> &yn,
			std::vector<double> &ym, std::vector<eq> &functions)
{
	std::vector<double> res;
	res.resize(yn.size());
	for (std::size_t i = 0; i < res.size(); i++)
	{
		res[i] = ym[i] - yn[i] - tau * functions[i](0.0, ym);
	}
	return res;
}