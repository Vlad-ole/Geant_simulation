#pragma once

#include "interpolate.h"
using namespace std;

class Errors
{
public:
	Errors(void);

	static double BetaRelativeError (double E_i, double E_j, unsigned int I_0_i, unsigned int I_0_j, unsigned int I_i, unsigned int I_j, interpolate& soft);


	~Errors(void);
};

