#include "matrix.hpp";

#include <iostream>;

Matrix::Matrix(unsigned int row, unsigned int col)
{
	Matrix::m_row = row;
	Matrix::m_col = col;

	Matrix::m_array.resize(row);
	for (int i = 0; i < Matrix::m_row; i++)
	{
		Matrix::m_array[i].resize(col);
	}
}

Matrix::Matrix(ARRAY &matrix)
{
	unsigned int row = matrix.size();
	unsigned int col = matrix[0].size();

	Matrix::m_row = row;
	Matrix::m_col = col;

	Matrix::m_array.resize(row);
	for (int i = 0; i < row; i++)
	{
		Matrix::m_array[i].resize(col);
		for (int j = 0; j < col; j++)
		{
			Matrix::m_array[i][j] = matrix[i][j];
		}
	}
}

void Matrix::show()
{
	for (int i = 0; i < Matrix::m_row; i++)
	{
		for (int j = 0; j < Matrix::m_col; j++)
		{
			std::cout << Matrix::m_array[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix Matrix::add(Matrix *matrix)
{
	unsigned int row = matrix->m_row;
	unsigned int col = matrix->m_col;

	Matrix *addedMatrix = new Matrix(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			addedMatrix->m_array[i][j] = Matrix::m_array[i][j] + matrix->m_array[i][j];
		}
	}

	return *addedMatrix;
}

Matrix Matrix::multiply(Matrix* matrix)
{
	if (Matrix::m_col != matrix->getRow())
	{
		throw std::exception("ValueError: matrices are not aligned");
	}

	unsigned int row = Matrix::m_row;
	unsigned int mid = Matrix::m_col; //matrix.getRow()
	unsigned int col = matrix->getCol();

	Matrix* multipliedMatrix = new Matrix(row, col);
	int sum;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sum = 0;
			for (int k = 0; k < mid; k++)
			{
				sum += Matrix::m_array[i][k] * matrix->m_array[k][j];
			}
			multipliedMatrix->m_array[i][j] = sum;
		}
	}

	return *multipliedMatrix;
}

Matrix Matrix::transpose()
{
	unsigned int row = Matrix::m_col;
	unsigned int col = Matrix::m_row;

	Matrix* transposedMatrix = new Matrix(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			transposedMatrix->m_array[i][j] = Matrix::m_array[j][i];
		}
	}

	return *transposedMatrix;
}

Matrix Matrix::operator+(Matrix& matrix)
{
	return this->add(&matrix);
}

Matrix Matrix::operator-()
{
	unsigned int row = Matrix::m_row;
	unsigned int col = Matrix::m_col;

	Matrix* minusMatrix = new Matrix(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			minusMatrix->m_array[i][j] = -this->m_array[i][j];
		}
	}

	return *minusMatrix;
}

Matrix Matrix::operator-(Matrix& matrix)
{
	return this->add(&(-matrix));
}

Matrix Matrix::operator*(Matrix& matrix)
{
	return this->multiply(&matrix);
}

Matrix operator* (float c, Matrix& matrix)
{
	unsigned int row = matrix.getRow();
	unsigned int col = matrix.getCol();

	Matrix* multipliedMatrix = new Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			multipliedMatrix->m_array[i][j] = c * matrix.m_array[i][j];
		}
	}

	return *multipliedMatrix;
}