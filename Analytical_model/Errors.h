#pragma once

#include "interpolate.h"
using namespace std;

class Errors
{
public:
	Errors(void);

	static double BetaRelativeError (double E_i, double E_j, unsigned int I_0_i, unsigned int I_0_j, unsigned int I_i, unsigned int I_j, interpolate& soft);
	static double Var_t(interpolate* spec_after_filter, interpolate* mu_1, interpolate* mu_2, const double t1, const double t2, double* tau, int tau_size);
	static double Var_t_correlate(interpolate* spec_after_filter, interpolate* mu_1, interpolate* mu_2, const double t1, const double t2, double* tau, int tau_size, interpolate* convolution);

	static double func(const double value, const double energy);
	static double GetConvolution(interpolate* spec_i, double (*func)(const double value, const double energy), const double value);

	~Errors(void);

private:
	///static double Cov_dk_dl(const double dk, const double dl);
	static double cov(double* tau, double tau_size, int i, int j);
};

