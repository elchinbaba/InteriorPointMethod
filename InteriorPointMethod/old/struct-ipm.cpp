#include "struct-ipm.hpp";

IPM::IPM()
{
	this->c = COEFFICIENTS();
	this->A = INEQUALITY_CONSTRAINT_ARRAY();
	this->b = INEQUALITY_CONSTRAINT_VECTOR();
}

IPM::IPM(COEFFICIENTS c, INEQUALITY_CONSTRAINT_ARRAY A, INEQUALITY_CONSTRAINT_VECTOR b)
{
	this->c = c;
	this->A = A;
	this->b = b;
}