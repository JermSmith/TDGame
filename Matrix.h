#pragma once
#include <vector>

class Matrix
{
public:
	Matrix(unsigned int numRows, unsigned int numCols);
	float& operator() (unsigned int row, unsigned int col);
	float operator() (unsigned int row, unsigned int col) const;

	Matrix operator+ (const Matrix& m);
	Matrix operator- (const Matrix& m);
	Matrix operator* (const Matrix& m);

	Matrix(const Matrix& m); // copy constructor
	Matrix& operator= (const Matrix& m); // assignment operator

private:
	std::vector<float> m_matrix;
	unsigned int m_rows;
	unsigned int m_cols;

	float& operator() (unsigned int contiguousIndex);
};

// constructor
inline Matrix::Matrix(unsigned int numRows, unsigned int numCols)
{
	if (numRows == 0) { throw "matrix assigned 0 rows"; }
	if (numCols == 0) { throw "matrix assigned 0 cols"; }

	m_rows = numRows;
	m_cols = numCols;
	m_matrix.resize(numRows * numCols, 0.f);
}

// operator (row, col) by reference
inline float& Matrix::operator() (unsigned int row, unsigned int col)
{
	//if (row > m_rows) { throw "row out of range of matrix"; }
	//if (col > m_cols) { throw "col out of range of matrix"; }

	return m_matrix.at((row - 1) * m_cols + col - 1);
}

// operator (row, col) by value
inline float Matrix::operator() (unsigned int row, unsigned int col) const
{
	if (row > m_rows) { throw "row out of range of matrix"; }
	if (col > m_cols) { throw "col out of range of matrix"; }

	return m_matrix.at((row - 1) * m_cols + col - 1);
}

// operator + on matrices
inline Matrix Matrix::operator+ (const Matrix& m)
{
	if (m_rows != m.m_rows) { throw "matrices cannot be added; different number of rows"; }
	if (m_cols != m.m_cols) { throw "matrices cannot be added; different number of cols"; }

	Matrix newMatrix(m_rows, m_cols);

	for (unsigned i = 0; i < m_matrix.size(); i++)
	{
		newMatrix(i) = m_matrix.at(i) + m.m_matrix.at(i);
	}

	return newMatrix;
}

// operator - on matrices
inline Matrix Matrix::operator- (const Matrix& m)
{
	if (m_rows != m.m_rows) { throw "matrix cannot be subtracted; different number of rows"; }
	if (m_cols != m.m_cols) { throw "matrix cannot be subtracted; different number of cols"; }

	Matrix newMatrix(m_rows, m_cols);

	for (unsigned i = 0; i < m_matrix.size(); i++)
	{
		newMatrix(i) = m_matrix.at(i) - m.m_matrix.at(i);
	}

	return newMatrix;
}

// operator * on matrices
inline Matrix Matrix::operator* (const Matrix& m)
{
	if (m_cols != m.m_rows) { throw "Matrix 1's # cols does not match Matrix 2's # rows for multiplication"; }

	Matrix newMatrix(m_rows, m.m_cols);

	for (unsigned r = 0; r < m_rows; r++)
	{
		for (unsigned c = 0; c < m.m_cols; c++)
		{
			for (unsigned i = 0; i < m_cols; i++)
			{
				newMatrix(r+1, c+1) += m_matrix.at(r * m_cols + i) * m.m_matrix.at(i * m.m_cols + c);
			}
		}
	}

	return newMatrix;
}

// copy constructor
inline Matrix::Matrix(const Matrix& m)
{
	m_matrix = m.m_matrix;
	m_rows = m.m_rows;
	m_cols = m.m_cols;
}

// assignment operator
inline Matrix& Matrix::operator= (const Matrix& m)
{
	m_matrix = m.m_matrix;
	m_rows = m.m_rows;
	m_cols = m.m_cols;
}

// operator (index) by reference
// private function
inline float& Matrix::operator() (unsigned int contiguousIndex)
{
	if (contiguousIndex > m_matrix.size() - 1) { throw "function called for index out of range of matrix"; }

	return m_matrix.at(contiguousIndex);
}






