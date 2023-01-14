#pragma once

#include "typedef.h"
#include <iostream>

#ifndef MATRIX_ALL_H
#define MATRIX_ALL_H

class Matrix
{
	public:
		ROW row;
		COLUMN column;
		ARRAY arr;

	public:
		void setRow(ROW n)
		{
			Matrix::row = n;
			Matrix::arr.resize(n);
		}

		void setColumn(COLUMN m)
		{
			Matrix::column = m;
			for (int i = 0; i < Matrix::arr.size(); i++)
			{
				Matrix::arr[i].resize(m);
			}
		}

		void setArray(ARRAY arr)
		{
			Matrix::arr = arr;
		}

	public:
		Matrix()
		{
			Matrix::row = 0;
			Matrix::column = 0;
		}
		Matrix(ROW row, COLUMN column)
		{
			Matrix::row = row;
			Matrix::column = column;

			Matrix::arr.resize(row);
			for (int i = 0; i < Matrix::row; i++)
			{
				Matrix::arr[i].resize(column);
			}
		}
		Matrix(VECTOR_DOUBLE vector)
		{
			ROW row = vector.size();
			COLUMN column = 1;

			Matrix::row = row;
			Matrix::column = column;

			Matrix::arr.resize(Matrix::row);
			for (int i = 0; i < Matrix::row; i++)
			{
				Matrix::arr[i].push_back(vector[i]);
			}
		}
		Matrix(ARRAY arr)
		{
			ROW row = arr.size();
			COLUMN column = arr[0].size();

			Matrix::row = row;
			Matrix::column = column;

			Matrix::arr.resize(Matrix::row);
			for (int i = 0; i < row; i++)
			{
				Matrix::arr[i].resize(Matrix::column);
				for (int j = 0; j < Matrix::column; j++)
				{
					Matrix::arr[i][j] = arr[i][j];
				}
			}
		}

	public:
		void show()
		{
			for (int i = 0; i < Matrix::row; i++)
			{
				for (int j = 0; j < Matrix::column; j++)
				{
					std::cout << Matrix::arr[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		MATRIX add(const Matrix &matrix)
		{
			ROW row = matrix.row;
			COLUMN column = matrix.column;

			MATRIX addedMatrix = Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					addedMatrix.arr[i][j] = Matrix::arr[i][j] + matrix.arr[i][j];
				}
			}

			return addedMatrix;
		}
		MATRIX multiply(const Matrix &matrix)
		{
			if (Matrix::column != matrix.row)
			{
				throw std::exception("ValueError: matrices are not aligned");
			}

			ROW row = Matrix::row;
			ARRAY_SIZE mid = Matrix::column; //matrix.row
			COLUMN column = matrix.column;

			MATRIX multipliedMatrix = Matrix(row, column);
			VALUE sum;
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					sum = 0;
					for (int k = 0; k < mid; k++)
					{
						sum += Matrix::arr[i][k] * matrix.arr[k][j];
					}
					multipliedMatrix.arr[i][j] = sum;
				}
			}

			return multipliedMatrix;
		}
		MATRIX* transpose()
		{
			ROW row = Matrix::column;
			COLUMN column = Matrix::row;

			MATRIX* transposedMatrix = new Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					transposedMatrix->arr[i][j] = Matrix::arr[j][i];
				}
			}
			this->setRow(row);
			this->setColumn(column);
			this->setArray(transposedMatrix->arr);
			delete transposedMatrix;

			return this;
		}
		VALUE determinant()
		{
			ARRAY_SIZE N = Matrix::row;
			MATRIX* massiv = new Matrix(Matrix::arr);
			int i, j;
			int r = 0, n = 0;
			int k;
			VALUE a_ii, a_ki;
			for (int i = 0; i < N - 1; i++)
			{
				if (massiv->arr[i][i] != 0)
				{
					a_ii = massiv->arr[i][i];
					for (k = i + 1; k < N; k++)
					{
						a_ki = -massiv->arr[k][i];
						for (j = 0; j < N; j++)
						{
							massiv->arr[k][j] += massiv->arr[i][j] * (a_ki / a_ii);
						}
					}
				}
				else
				{
					int t;
					for (t = i + 1; t < N; t++)
					{
						if (massiv->arr[i][t] != 0)
						{
							break;
						}
					}

					if (t != N)
					{
						n++;
						VALUE c;
						for (j = 0; j < N; j++)
						{
							c = massiv->arr[j][i];
							massiv->arr[j][i] = massiv->arr[j][t];
							massiv->arr[j][t] = c;
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
					D *= massiv->arr[i][i];
				break;
			case 1:
				D = 0; break;
			}
			delete massiv;
			return D;
		}
		MATRIX* inverse()
		{
			ARRAY_SIZE N = Matrix::row;
			MATRIX* massiv = new Matrix(N, 2 * N);
			int i, j;
			VALUE D = Matrix::determinant();

			if (D == 0) throw std::exception("Inverse matrix does not exist!");

			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					massiv->arr[i][j] = Matrix::arr[i][j];
				}
				for (j = N; j < 2 * N; j++)
				{
					if (j - N == i) massiv->arr[i][j] = 1;
					else massiv->arr[i][j] = 0;
				}
			}

			int k, t;
			VALUE a_ii, a_ki;
			for (i = 0; i < N; i++)
			{
				if (massiv->arr[i][i] != 0)
				{
					a_ii = massiv->arr[i][i];
					for (j = 0; j < 2 * N; j++)
					{
						massiv->arr[i][j] /= a_ii;
					}
					for (k = 0; k < N; k++)
					{
						if (k != i)
						{
							a_ki = -massiv->arr[k][i];
							for (j = 0; j < 2 * N; j++)
							{
								massiv->arr[k][j] += massiv->arr[i][j] * a_ki;
							}
						}
					}
				}
				else
				{
					for (t = i + 1; t < N; t++)
					{
						if (massiv->arr[i][t] != 0)
						{
							break;
						}
					}
					if (t == N) throw std::exception("Inverse matrix does not exist!");
					VALUE c;
					for (j = 0; j < N; j++)
					{
						try
						{
							c = massiv->arr[j][i];
							massiv->arr[j][i] = massiv->arr[j][t];
							massiv->arr[j][t] = c;
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
					this->arr[i][j] = massiv->arr[i][j + N];
				}
			}
			delete massiv;

			return this;
		}

	public:
		MATRIX operator+(const MATRIX& matrix)
		{
			return this->add(matrix);
		}

		MATRIX operator-()
		{
			return -1 * *this;
		}
		MATRIX operator-(MATRIX& matrix)
		{
			return this->add(-matrix);
		}
		MATRIX operator*(const MATRIX& matrix)
		{
			return this->multiply(matrix);
		}
		friend MATRIX operator* (const MATRIX& matrix1, const MATRIX& matrix2)
		{
			if (matrix1.column != matrix2.row)
			{
				throw std::exception("ValueError: matrices are not aligned");
			}

			ROW row = matrix1.row;
			ARRAY_SIZE mid = matrix1.column;
			COLUMN column = matrix2.column;

			MATRIX multipliedMatrix = Matrix(row, column);
			VALUE sum;
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					sum = 0;
					for (int k = 0; k < mid; k++)
					{
						sum += matrix1.arr[i][k] * matrix2.arr[k][j];
					}
					multipliedMatrix.arr[i][j] = sum;
				}
			}

			return multipliedMatrix;
		}

		friend MATRIX operator* (const VALUE c, const MATRIX& matrix)
		{
			ROW row = matrix.row;
			COLUMN column = matrix.column;

			MATRIX multipliedMatrix = Matrix(row, column);

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					multipliedMatrix.arr[i][j] = c * matrix.arr[i][j];
				}
			}

			return multipliedMatrix;
		}

		friend MATRIX operator+ (const MATRIX& matrix1, const MATRIX& matrix2)
		{
			MATRIX addedMatrix = Matrix(matrix1.row, matrix2.column);

			for (int i = 0; i < matrix1.row; i++)
			{
				for (int j = 0; j < matrix2.column; j++)
				{
					addedMatrix.arr[i][j] = matrix1.arr[i][j] + matrix2.arr[i][j];
				}
			}

			return addedMatrix;
		}

		friend MATRIX operator- (const MATRIX& matrix1, const MATRIX& matrix2)
		{
			MATRIX subtractedMatrix = Matrix(matrix1.row, matrix2.column);

			for (int i = 0; i < matrix1.row; i++)
			{
				for (int j = 0; j < matrix2.column; j++)
				{
					subtractedMatrix.arr[i][j] = matrix1.arr[i][j] - matrix2.arr[i][j];
				}
			}

			return subtractedMatrix;
		}

	public:
		MATRIX static convert(VECTOR_DOUBLE& vector)
		{
			ROW row = vector.size();
			COLUMN column = 1;

			MATRIX* convertedMatrix = new Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				convertedMatrix->arr[i][0] = vector[i];
			}

			return *convertedMatrix;
		}
		static VECTOR_DOUBLE convertToVector(MATRIX matrix)
		{
			VECTOR_DOUBLE vector;
			for (int i = 0; i < matrix.row; i++)
			{
				vector.push_back(matrix.arr[i][0]);
			}
			return vector;
		}
};

#endif