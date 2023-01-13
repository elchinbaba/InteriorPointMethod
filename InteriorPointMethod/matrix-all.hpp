#pragma once

#include "typedef.h"
#include <iostream>

#ifndef MATRIX_ALL_H
#define MATRIX_ALL_H

class Matrix
{
	private:
		ROW m_row;
		COLUMN m_column;
		ARRAY m_array;

	public:
		ROW getRow()
		{
			return Matrix::m_row;
		}
		void setRow(ROW n)
		{
			Matrix::m_row = n;
			Matrix::m_array.resize(n);
		}

		COLUMN getColumn()
		{
			return Matrix::m_column;
		}
		void setColumn(COLUMN m)
		{
			Matrix::m_column = m;
			for (int i = 0; i < Matrix::m_array.size(); i++)
			{
				Matrix::m_array[i].resize(m);
			}
		}

		ARRAY getArray()
		{
			return Matrix::m_array;
		}
		void setArray(ARRAY arr)
		{
			Matrix::m_array = arr;
		}

	public:
		Matrix()
		{
			Matrix::m_row = 0;
			Matrix::m_column = 0;
		}
		Matrix(ROW row, COLUMN column)
		{
			Matrix::m_row = row;
			Matrix::m_column = column;

			Matrix::m_array.resize(row);
			for (int i = 0; i < Matrix::m_row; i++)
			{
				Matrix::m_array[i].resize(column);
			}
		}
		Matrix(VECTOR_DOUBLE vector)
		{
			ROW row = vector.size();
			COLUMN column = 1;

			Matrix::m_row = row;
			Matrix::m_column = column;

			Matrix::m_array.resize(Matrix::m_row);
			for (int i = 0; i < Matrix::m_row; i++)
			{
				Matrix::m_array[i].push_back(vector[i]);
			}
		}
		Matrix(ARRAY arr)
		{
			ROW row = arr.size();
			COLUMN column = arr[0].size();

			Matrix::m_row = row;
			Matrix::m_column = column;

			Matrix::m_array.resize(Matrix::m_row);
			for (int i = 0; i < row; i++)
			{
				Matrix::m_array[i].resize(Matrix::m_column);
				for (int j = 0; j < Matrix::m_column; j++)
				{
					Matrix::m_array[i][j] = arr[i][j];
				}
			}
		}

	public:
		void show()
		{
			for (int i = 0; i < Matrix::m_row; i++)
			{
				for (int j = 0; j < Matrix::m_column; j++)
				{
					std::cout << Matrix::m_array[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		MATRIX add(Matrix matrix)
		{
			ROW row = matrix.m_row;
			COLUMN column = matrix.m_column;

			MATRIX* addedMatrix = new Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					addedMatrix->m_array[i][j] = Matrix::m_array[i][j] + matrix.m_array[i][j];
				}
			}

			return *addedMatrix;
		}
		MATRIX multiply(Matrix matrix)
		{
			if (Matrix::m_column != matrix.getRow())
			{
				throw std::exception("ValueError: matrices are not aligned");
			}

			ROW row = Matrix::m_row;
			ARRAY_SIZE mid = Matrix::m_column; //matrix.getRow()
			COLUMN column = matrix.getColumn();

			MATRIX* multipliedMatrix = new Matrix(row, column);
			VALUE sum;
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					sum = 0;
					for (int k = 0; k < mid; k++)
					{
						sum += Matrix::m_array[i][k] * matrix.m_array[k][j];
					}
					multipliedMatrix->m_array[i][j] = sum;
				}
			}

			return *multipliedMatrix;
		}
		MATRIX transpose()
		{
			ROW row = Matrix::m_column;
			COLUMN column = Matrix::m_row;

			MATRIX* transposedMatrix = new Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					transposedMatrix->m_array[i][j] = Matrix::m_array[j][i];
				}
			}

			return *transposedMatrix;
		}
		VALUE determinant()
		{
			ARRAY_SIZE N = Matrix::m_row;
			MATRIX massiv = Matrix(Matrix::m_array);
			int i, j;
			int r = 0, n = 0;
			int k;
			VALUE a_ii, a_ki;
			for (int i = 0; i < N - 1; i++)
			{
				if (massiv.m_array[i][i] != 0)
				{
					a_ii = massiv.m_array[i][i];
					for (k = i + 1; k < N; k++)
					{
						a_ki = -massiv.m_array[k][i];
						for (j = 0; j < N; j++)
						{
							massiv.m_array[k][j] += massiv.m_array[i][j] * (a_ki / a_ii);
						}
					}
				}
				else
				{
					int t;
					for (t = i + 1; t < N; t++)
					{
						if (massiv.m_array[i][t] != 0)
						{
							break;
						}
					}

					if (t != N)
					{
						n++;
						VECTOR_DOUBLE c;
						c.resize(N);
						for (j = 0; j < N; j++)
						{
							c[j] = massiv.m_array[j][i];
							massiv.m_array[j][i] = massiv.m_array[j][t];
							massiv.m_array[j][t] = c[j];
						}
						i = i - 1;
						continue;
					}
					else
					{
						r = 1; break;
					}
				}
			}
			VALUE D;
			switch (r)
			{
			case 0:
				D = pow(-1, n);
				for (i = 0; i < N; i++)
					D *= massiv.m_array[i][i];
				break;
			case 1:
				D = 0; break;
			}
			return D;
		}
		MATRIX inverse()
		{
			ARRAY_SIZE N = Matrix::m_row;
			MATRIX massiv = Matrix(N, 2 * N);
			int i, j;
			VALUE D = Matrix::determinant();

			if (D == 0) throw std::exception("Inverse matrix does not exist!");

			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					massiv.m_array[i][j] = Matrix::m_array[i][j];
				}
				for (j = N; j < 2 * N; j++)
				{
					if (j - N == i) massiv.m_array[i][j] = 1;
					else massiv.m_array[i][j] = 0;
				}
			}

			MATRIX ters_matris = Matrix(N, N);
			int k, t;
			VALUE a_ii, a_ki;
			for (i = 0; i < N; i++)
			{
				if (massiv.m_array[i][i] != 0)
				{
					a_ii = massiv.m_array[i][i];
					for (j = 0; j < 2 * N; j++)
					{
						massiv.m_array[i][j] /= a_ii;
					}
					for (k = 0; k < N; k++)
					{
						if (k != i)
						{
							a_ki = -massiv.m_array[k][i];
							for (j = 0; j < 2 * N; j++)
							{
								massiv.m_array[k][j] += massiv.m_array[i][j] * a_ki;
							}
						}
					}
				}
				else
				{
					for (t = i + 1; t < N; t++)
					{
						if (massiv.m_array[i][t] != 0)
						{
							break;
						}
					}
					if (t == N) throw std::exception("Inverse matrix does not exist!");
					VECTOR_DOUBLE c;
					c.resize(N);
					for (j = 0; j < N; j++)
					{
						try
						{
							c[j] = massiv.m_array[j][i];
							massiv.m_array[j][i] = massiv.m_array[j][t];
							massiv.m_array[j][t] = c[j];
						}
						catch (std::exception ex)
						{
							throw std::exception("Inverse matrix not found.");
						}
					}
					i = i - 1;
				}
			}
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					ters_matris.m_array[i][j] = massiv.m_array[i][j + N];
				}
			}

			return ters_matris;
		}

	public:
		MATRIX operator+(MATRIX& matrix)
		{
			return this->add(matrix);
		}

		MATRIX operator-()
		{
			ROW row = Matrix::m_row;
			COLUMN column = Matrix::m_column;

			MATRIX* minusMatrix = new Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					minusMatrix->m_array[i][j] = -this->m_array[i][j];
				}
			}

			return *minusMatrix;
		}
		MATRIX operator-(MATRIX& matrix)
		{
			MATRIX minusMatrix = -matrix;
			return this->add(minusMatrix);
		}
		MATRIX operator*(MATRIX& matrix)
		{
			return this->multiply(matrix);
		}

		friend MATRIX operator* (VALUE c, MATRIX& matrix)
		{
			ROW row = matrix.getRow();
			COLUMN column = matrix.getColumn();

			MATRIX* multipliedMatrix = new Matrix(row, column);

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					multipliedMatrix->m_array[i][j] = c * matrix.m_array[i][j];
				}
			}

			return *multipliedMatrix;
		}

	public:
		MATRIX static convert(VECTOR_DOUBLE& vector)
		{
			ROW row = vector.size();
			COLUMN column = 1;

			MATRIX* convertedMatrix = new Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				convertedMatrix->m_array[i][0] = vector[i];
			}

			return *convertedMatrix;
		}
		VECTOR_DOUBLE convertToVector()
		{
			VECTOR_DOUBLE vector;
			for (int i = 0; i < Matrix::getRow(); i++)
			{
				vector.push_back(Matrix::m_array[i][0]);
			}
			return vector;
		}
};

#endif