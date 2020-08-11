#pragma once
#include <vector>

class Matrix
{
public:
	Matrix(unsigned int numRows, unsigned int numCols);
	Matrix(std::vector<std::vector<float>> mat);
	float& operator() (unsigned int row, unsigned int col);
	float operator() (unsigned int row, unsigned int col) const;

	Matrix operator+ (const Matrix& m);
	Matrix operator- (const Matrix& m);
	Matrix operator* (const Matrix& m);

	Matrix(const Matrix& m); // copy constructor
	Matrix& operator= (const Matrix& m); // assignment operator

	float determinant();
	Matrix transpose();
	Matrix inverse();

private:
	std::vector<float> m_matrix;
	unsigned int m_rows;
	unsigned int m_cols;

	float& operator() (unsigned int contiguousIndex);
	float operator() (unsigned int contiguousIndex) const;
};

// constructor
inline Matrix::Matrix(unsigned int numRows, unsigned int numCols)
{
	if (numRows == 0) { throw "matrix assigned 0 rows"; }
	if (numCols == 0) { throw "matrix assigned 0 cols"; }

	m_rows = numRows;
	m_cols = numCols;
	m_matrix.resize(m_rows * m_cols, 0.f);
}

//constructor
inline Matrix::Matrix(std::vector<std::vector<float>> mat)
{
	if (mat.size() == 0) { throw "matrix assigned 0 rows or columns"; }
	else if (mat.at(0).size() == 0) { throw "matrix assigned 0 columns"; }

	m_rows = mat.size();
	m_cols = mat.at(0).size();
	for (unsigned i = 0; i < m_rows; i++)
	{
		if (mat.at(i).size() != m_cols) { throw "not all rows provided for the matrix have the same size"; }
	}

	m_matrix.resize(m_rows * m_cols, 0.f);

	for (unsigned r = 0; r < m_rows; r++)
	{
		for (unsigned c = 0; c < m_cols; c++)
		{
			m_matrix.at(r * m_cols + c) = mat.at(r).at(c);
		}
	}
}

// operator (row, col) by reference
inline float& Matrix::operator() (unsigned int row, unsigned int col)
{
	if (row > m_rows) { throw "row out of range of matrix"; }
	if (col > m_cols) { throw "col out of range of matrix"; }

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
	if (contiguousIndex > m_matrix.size() - 1) { throw "contiguousIndex operator() (by ref) called for index out of range of matrix"; }

	return m_matrix.at(contiguousIndex);
}

// operator (index) by reference
// private function
inline float Matrix::operator() (unsigned int contiguousIndex) const
{
	if (contiguousIndex > m_matrix.size() - 1) { throw "contiguousIndex operator() (by val) called for index out of range of matrix"; }

	return m_matrix.at(contiguousIndex);
}

inline float Matrix::determinant()
{
	if (m_rows != m_cols) { throw "Cannot compute determinant of a matrix that is not square"; }

	float det = 1.f; // meaningless initialization

	if (m_rows == 1)
	{
		det = m_matrix.at(0);
	}

	else if (m_rows == 2)
	{
		det = m_matrix.at(0) * m_matrix.at(3) - m_matrix.at(1) * m_matrix.at(2);
	}

	else if (m_rows == 3)
	{
		det = m_matrix.at(0) * m_matrix.at(4) * m_matrix.at(8)
			- m_matrix.at(0) * m_matrix.at(5) * m_matrix.at(7)
			- m_matrix.at(1) * m_matrix.at(3) * m_matrix.at(8)
			+ m_matrix.at(1) * m_matrix.at(5) * m_matrix.at(6)
			+ m_matrix.at(2) * m_matrix.at(3) * m_matrix.at(7)
			- m_matrix.at(2) * m_matrix.at(4) * m_matrix.at(6);
	}
	
	else if (m_rows == 4)
	{
		float m_0 = m_matrix.at(0);
		float m_1 = m_matrix.at(1);
		float m_2 = m_matrix.at(2);
		float m_3 = m_matrix.at(3);
		float m_4 = m_matrix.at(4);
		float m_5 = m_matrix.at(5);
		float m_6 = m_matrix.at(6);
		float m_7 = m_matrix.at(7);
		float m_8 = m_matrix.at(8);
		float m_9 = m_matrix.at(9);
		float m10 = m_matrix.at(10);
		float m11 = m_matrix.at(11);
		float m12 = m_matrix.at(12);
		float m13 = m_matrix.at(13);
		float m14 = m_matrix.at(14);
		float m15 = m_matrix.at(15);

		det = m_0 * m_5 * m10 * m15
			- m_0 * m_5 * m11 * m14
			- m_0 * m_6 * m_9 * m15
			+ m_0 * m_6 * m11 * m13
			+ m_0 * m_7 * m_9 * m14
			- m_0 * m_7 * m10 * m13
			- m_1 * m_4 * m10 * m15
			+ m_1 * m_4 * m11 * m14
			+ m_1 * m_6 * m_8 * m15
			- m_1 * m_6 * m11 * m12
			- m_1 * m_7 * m_8 * m14
			+ m_1 * m_7 * m10 * m12
			+ m_2 * m_4 * m_9 * m15
			- m_2 * m_4 * m11 * m13
			- m_2 * m_5 * m_8 * m15
			+ m_2 * m_5 * m11 * m12
			+ m_2 * m_7 * m_8 * m13
			- m_2 * m_7 * m_9 * m12
			- m_3 * m_4 * m_9 * m14
			+ m_3 * m_4 * m10 * m13
			+ m_3 * m_5 * m_8 * m14
			- m_3 * m_5 * m10 * m12
			- m_3 * m_6 * m_8 * m13
			+ m_3 * m_6 * m_9 * m12;
	}

	else
	{
		throw "Code not written for calculating determinant of matrix of size > 4x4";
	}

	return det;
}

inline Matrix Matrix::transpose()
{
	if (m_rows < 1) { throw "Error: matrix has less than 1 row"; }
	if (m_cols < 1) { throw "Error: matrix has less than 1 column"; }

	Matrix transposedMatrix(m_cols, m_rows);

	for (unsigned r = 1; r <= m_rows; r++)
	{
		for (unsigned c = 1; c <= m_cols; c++)
		{
			transposedMatrix(c, r) = m_matrix.at((r - 1) * m_cols + c - 1);
		}
	}

	return transposedMatrix;
}

inline Matrix Matrix::inverse()
{
	float det = determinant();
	if (det == 0) { throw "matrix has determinant == 0; cannot compute inverse"; }
	float invDet = 1.f / det;

	Matrix invertedMatrix(m_rows, m_cols); // rows and cols will be the same if determinant calculation is successful.

	if (m_rows == 1)
	{
		invertedMatrix(0) = invDet;
	}

	else if (m_rows == 2)
	{
		invertedMatrix(0) = invDet * m_matrix.at(3);
		invertedMatrix(1) = invDet * m_matrix.at(1) * -1;
		invertedMatrix(2) = invDet * m_matrix.at(2) * -1;
		invertedMatrix(3) = invDet * m_matrix.at(0);
	}

	else if (m_rows == 3)
	{
		// translation matrix
		if (m_matrix.at(0) == 1 && m_matrix.at(1) == 0 && m_matrix.at(2) == 0 &&
			m_matrix.at(3) == 0 && m_matrix.at(4) == 1 && m_matrix.at(5) == 0 &&
			m_matrix.at(8) == 1)
		{
			invertedMatrix(0) = 1;
			invertedMatrix(1) = 0;
			invertedMatrix(2) = 0;
			invertedMatrix(3) = 0;
			invertedMatrix(4) = 1;
			invertedMatrix(5) = 0;
			invertedMatrix(6) = -1 * m_matrix.at(6);
			invertedMatrix(7) = -1 * m_matrix.at(7);
			invertedMatrix(8) = 1;
		}

		// scaling matrix
		else if (m_matrix.at(0) != 0 && m_matrix.at(1) == 0 && m_matrix.at(2) == 0 &&
			m_matrix.at(3) == 0 && m_matrix.at(4) != 0 && m_matrix.at(5) == 0 &&
			m_matrix.at(6) == 0 && m_matrix.at(7) == 0 && m_matrix.at(8) == 1)
		{
			invertedMatrix(0) = 1.f / m_matrix.at(0);
			invertedMatrix(1) = 0;
			invertedMatrix(2) = 0;
			invertedMatrix(3) = 0;
			invertedMatrix(4) = 1.f / m_matrix.at(4);
			invertedMatrix(5) = 0;
			invertedMatrix(6) = 0;
			invertedMatrix(7) = 0;
			invertedMatrix(8) = 1;
		}

		// rotation matrix
		else if (m_matrix.at(0) == m_matrix.at(4) && m_matrix.at(1) - sinf(acosf(m_matrix.at(0))) < powf(10, -7)
			&& m_matrix.at(2) == 0 &&
			m_matrix.at(3) == -1 * m_matrix.at(1) && m_matrix.at(5) == 0 &&
			m_matrix.at(6) == 0 && m_matrix.at(7) == 0 && m_matrix.at(8) == 1)
		{
			invertedMatrix(0) = m_matrix.at(0);
			invertedMatrix(1) = m_matrix.at(3);
			invertedMatrix(2) = 0;
			invertedMatrix(3) = m_matrix.at(1);
			invertedMatrix(4) = m_matrix.at(4);
			invertedMatrix(5) = 0;
			invertedMatrix(6) = 0;
			invertedMatrix(7) = 0;
			invertedMatrix(8) = 1;
		}

		// general 3x3 inverse
		else
		{
			invertedMatrix(0) = invDet * (m_matrix.at(4) * m_matrix.at(8) - m_matrix.at(5) * m_matrix.at(7));
			invertedMatrix(1) = invDet * (m_matrix.at(2) * m_matrix.at(7) - m_matrix.at(1) * m_matrix.at(8));
			invertedMatrix(2) = invDet * (m_matrix.at(1) * m_matrix.at(5) - m_matrix.at(2) * m_matrix.at(4));
			invertedMatrix(3) = invDet * (m_matrix.at(5) * m_matrix.at(6) - m_matrix.at(3) * m_matrix.at(8));
			invertedMatrix(4) = invDet * (m_matrix.at(0) * m_matrix.at(8) - m_matrix.at(2) * m_matrix.at(6));
			invertedMatrix(5) = invDet * (m_matrix.at(2) * m_matrix.at(3) - m_matrix.at(0) * m_matrix.at(5));
			invertedMatrix(6) = invDet * (m_matrix.at(3) * m_matrix.at(7) - m_matrix.at(4) * m_matrix.at(6));
			invertedMatrix(7) = invDet * (m_matrix.at(1) * m_matrix.at(6) - m_matrix.at(0) * m_matrix.at(7));
			invertedMatrix(8) = invDet * (m_matrix.at(0) * m_matrix.at(4) - m_matrix.at(1) * m_matrix.at(3));
		}
	}

	else if (m_rows == 4)
	{

	}

	else
	{
		throw "Code not written for calculating inverse of matrix of size > 4x4";
	}

	return invertedMatrix;

}




