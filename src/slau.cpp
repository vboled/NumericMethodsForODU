#include "../includes/NumericMethodsFODU.h"

using namespace std;

vector<vector<double>> 	matrixJacoby(double tau, vector<double> &y_old, 
									vector<double> &y_new, vector<eq> &equations, method_func F)
{
	vector<vector<double>> res;
	double tmp_x;
	vector<double> tmp_f;
	res.resize(y_old.size());
	// cout << "yn: ";
	// print_v(yn);
	// cout << "ym: ";
	// print_v(ym);
	// cout << "tau = " << tau;
	// cout << "\nF: ";
	// print_v(tmp_f);
	// cout << endl;
	tmp_f = F(tau, y_old, y_new, equations);
	for (size_t i = 0; i < y_old.size(); i++)
	{
		res[i].resize(y_old.size());
		for (size_t j = 0; j < y_old.size(); j++)
		{
			tmp_x = y_new[j];
			y_new[j] += 10e-10;
			res[i][j] = (-tmp_f[i] + F(tau, y_old, y_new, equations)[i]) / 10e-10; 
			y_new[j] = tmp_x;
		}
	}
	return res;
}

vector<double>		multMatrixVector(vector<vector<double>> matr, vector<double> vec)
{
	vector<double> res_vec;
	res_vec.resize(vec.size());

	for (int i = 0; i < vec.size(); i++)
	{
		double sum = 0;
		for (int j = 0; j < vec.size(); j++)
			sum += matr[i][j] * vec[j];
		res_vec[i] = sum;
	}
	return res_vec;
}

double	vectorResidual(vector<double> &vec1, vector<double> &vec2)
{
	double x = 0.0, max = 0.0;
	for(size_t j = 0; j < vec1.size(); j++)
	{
		x = fabs(vec1[j] - vec2[j]);
		if (x > max)
			max = x;
	}
	return max;
}

int is_zero(double elem)
{
	if (fabs(elem) <= 10e-11)
		return 1;
	return 0;
}

int find_and_swap(vector<vector<double>> &A, vector<double> &B1, int k)
{
	if (!A.size() || !B1.size())
	{
		cout << "Matrix is not exist\n";
		return 1;
	}
	vector<double> tmp_a;
	double tmp_b;
	int num_max = 0;
	double max = 0.0;

	for (int i = k; i < A[0].size(); i++)
	{
		if (fabs(A[i][k]) > max)
		{
			max = fabs(A[i][k]);
			num_max = i;
		}
	}
	if (is_zero(max))
	{
		return 1;
	}
	tmp_a = A[num_max];
	A[num_max] = A[k];
	A[k] = tmp_a;
	tmp_b = B1[num_max];
	B1[num_max] = B1[k];
	B1[k] = tmp_b;
	return 0;
}

vector<double> reverse_move(vector<vector<double>> &A, vector<double> &B1)
{
	vector<double> result;
	result.resize(A[0].size());
	for (int i = A[0].size() - 1; i >= 0; i--)
	{
		double sum = 0.0;
		if (i != A[0].size() - 1)
			for (int j = i + 1; j < A[0].size(); j++)
			{
				sum += A[i][j] * result[j];
			}
		if (is_zero(A[i][i]))
		{
			cout << "0 on the diag\n";
			result.resize(0);
			return result;
		}
		else
		{
			result[i] = (B1[i] - sum) / A[i][i];
		}
		if (is_zero(result[i]))
		{
			result[i] = 0.0;
		}
	}
	return result;
}

vector<double> gauss(vector<vector<double>> &A, vector<double> &C)
{
	double koff = 0;
	for (int k = 0; k < A.size(); k++)
	{
		if (find_and_swap(A, C, k))
		{
			cout << "The matrix is degenerate\n";
			C.resize(0);
			return C;
		}
		for (int j = k + 1; j < A.size(); j++)
		{
			koff = A[j][k] / A[k][k];
			for (int i = k; i < A.size(); i++)
			{
				if (i == k)
					A[j][i] = 0.0;
				else
					A[j][i] -= koff * A[k][i];
				if (is_zero(A[i][j]))
					A[i][j] = 0.0;
			}
			C[j] -= koff * C[k];
			if (is_zero(C[j]))
			{
				C[j] = 0.0;
			}
		}
	}
	return reverse_move(A, C);
}

vector<vector<double>> inverseMatrix(vector<vector<double>> &A)
{
	vector<vector<double>> res_matr;
	res_matr.resize(A.size());
	for (int i = 0; i < A.size(); i++)
	{
		res_matr[i].resize(A[i].size());
	}

	vector<vector<double>> copy_A;
	copy_A.resize(A.size());
	for (int i = 0; i < A.size(); i++)
	{
		copy_A[i].resize(A[i].size());
	}

	vector<vector<double>> E;
	E.resize(A.size());
	vector<double> tmp;
	for (int i = 0; i < A.size(); i++)
	{
		E[i].resize(A[i].size());
		for (int j = 0; j < A[i].size(); j++)
		{
			if (i == j)
			{
				E[i][j] = 1.;
			}
			else
			{
				E[i][j] = 0.;
			}
		}
	}

	for (int i = 0; i < A.size(); i++)
	{
		for (int k = 0; k < A[i].size(); k++)
		{
			for (int l = 0; l < A[i].size(); l++)
			{
				copy_A[k][l] = A[k][l];
			}
		}

		tmp = gauss(copy_A, E[i]);
		if (!tmp.size())
		{
			res_matr.resize(0);
			return res_matr;
		}
		for (int j = 0; j < A.size(); j++)
		{
			res_matr[j][i] = tmp[j];
		}
		tmp.resize(0);
	}
	copy_A.resize(0);
	E.resize(0);
	return res_matr;
}

vector<double> 	newtonMethod(double tau, vector<double> &y_old,
						vector<double> &y_new, vector<eq> &equations, method_func F)
{
	vector<double> x_old; //xj = x(i+1)
	vector<double> x_new;
	vector<vector<double>> A;
	vector<double> tmp_v;
	tmp_v.resize(y_new.size());
	int iter = 0;
	x_old.resize(y_new.size());
	x_new.resize(y_new.size());
	for (size_t j = 0; j < x_old.size(); j++)
	{
		x_old[j] = y_new[j];
		x_new[j] = y_new[j];
	}
	//tmp_v = F(tau, y_old, x_old, equations);
	//print_v(tmp_v);
	do
	{
		A = matrixJacoby(tau, y_old, x_old, equations, F);
		A = inverseMatrix(A);
//		print_v(tmp_f);
//		cout << "\n";
		tmp_v = multMatrixVector(A, F(tau, y_old, x_old, equations));
		for (size_t j = 0; j < x_old.size(); j++)
		{
			x_new[j] = x_old[j] - tmp_v[j];
			x_old[j] = x_new[j];
		}
		iter++;
	} while (vectorResidual(x_old, x_new) > 10e-7 && iter < 100);
	if (iter == 100)
	{
        cout << "Too many iterations\n";
		x_new.resize(0);
	}
	return x_new;
}
