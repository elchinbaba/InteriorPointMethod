#pragma once

#include "typedef.h"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	private:
		ROW m_row;
		COLUMN m_column;
		ARRAY m_array;

	public:
		ROW getRow();
		void setRow(ROW n);

		COLUMN getColumn();
		void setColumn(COLUMN m);

		ARRAY getArray();
		void setArray(ARRAY);

	public:
		Matrix();
		Matrix(ROW, COLUMN);
		Matrix(VECTOR_DOUBLE);
		Matrix(ARRAY&);

	public:
		void show();
		MATRIX add(MATRIX&);
		MATRIX multiply(MATRIX&);
		MATRIX transpose();
		VALUE determinant();
		MATRIX inverse();

	public:
		MATRIX operator+ (MATRIX&);
		MATRIX operator- ();
		MATRIX operator- (MATRIX&);
		MATRIX operator* (MATRIX&);

	friend MATRIX operator* (VALUE, MATRIX&);
	
	public:
		MATRIX static convert(VECTOR_DOUBLE&);
		VECTOR_DOUBLE convertToVector();
};

#endif