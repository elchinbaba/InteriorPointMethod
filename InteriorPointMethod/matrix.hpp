#pragma once

#include "typedef.h"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	private:
		ARRAY m_array;
	public:
		ARRAY getMatrix() { return Matrix::m_array; }

	private:
		unsigned int m_row, m_col;
	public:
		unsigned int getRow() { return Matrix::m_row; }
		unsigned int getCol() { return Matrix::m_col; }

	public:
		Matrix();
		Matrix(unsigned int, unsigned int);
		Matrix(ARRAY&);

		void show();
		Matrix add(Matrix&);
		Matrix multiply(Matrix&);
		Matrix transpose();

	public:
		Matrix operator+ (Matrix&);
		Matrix operator- ();
		Matrix operator- (Matrix&);
		Matrix operator* (Matrix&);

	friend Matrix operator* (double, Matrix&);
	
	public:
		Matrix static convert(VECTOR_DOUBLE&);
};

Matrix operator* (double, Matrix&);

#endif