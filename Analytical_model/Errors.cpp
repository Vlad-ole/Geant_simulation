#include "Errors.h"
#include <iostream>
using namespace std;

Errors::Errors(void)
{
}


Errors::~Errors(void)
{
}


double Errors::BetaRelativeError (const double E_i, const double E_j, const unsigned int I_0_i, const unsigned int I_0_j, const unsigned int I_i, const unsigned int I_j, interpolate& mu_soft)
{
	const double T_i = log(I_0_i / I_i);
	const double T_j = log(I_0_j / I_j);

	//cout << T_i << endl;
	//cout << T_j << endl;

	const double DeltaBetaSquare = pow(mu_soft.Eval_Data(E_i), 2.0) / I_j + pow(mu_soft.Eval_Data(E_j), 2.0) / I_i;
	const double DetBetaSquare = pow(mu_soft.Eval_Data(E_i) * T_j - mu_soft.Eval_Data(E_j) * T_i, 2.0 );

	cout << endl;
	cout << "DeltaBetaSquare \t" << DeltaBetaSquare << endl;
	cout << "DetBetaSquare \t" << DetBetaSquare << endl;
	cout << endl;

	return sqrt( DeltaBetaSquare / DetBetaSquare );
}