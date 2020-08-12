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
	if (m_rows != m_cols) { throw "matrix is not square; cannot compute inverse"; }
	Matrix invertedMatrix(m_rows, m_cols);

	if (m_rows == 1)
	{
		if (m_matrix.at(0) == 0) { throw "1x1 matrix has determinant == 0; cannot compute inverse"; }

		invertedMatrix(0) = m_matrix.at(0);
	}

	else if (m_rows == 2)
	{
		float det = determinant();
		if (det == 0) { throw "2x2 matrix has determinant == 0; cannot compute inverse"; }
		float invDet = 1.f / det;

		invertedMatrix(0) = invDet * m_matrix.at(3);
		invertedMatrix(1) = invDet * m_matrix.at(1) * -1;
		invertedMatrix(2) = invDet * m_matrix.at(2) * -1;
		invertedMatrix(3) = invDet * m_matrix.at(0);
	}

	else if (m_rows == 3)
	{
		float det = determinant();
		if (det == 0) { throw "3x3 matrix has determinant == 0; cannot compute inverse"; }
		float invDet = 1.f / det;

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
			&& m_matrix.at(1) == -1 * m_matrix.at(3) &&
			m_matrix.at(2) == 0 && m_matrix.at(5) == 0 &&
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

		// used for determinant and adjoint
		float m10m15_m11m14 = m10 * m15 - m11 * m14;
		float m9m15_m11m13  = m_9 * m15 - m11 * m13;
		float m9m14_m10m13  = m_9 * m14 - m10 * m13;
		float m8m15_m11m12  = m_8 * m15 - m11 * m12;
		float m8m14_m10m12  = m_8 * m14 - m10 * m12;
		float m8m13_m9m12   = m_8 * m13 - m_9 * m12;

		float det
			= m_0 * (m_5 * m10m15_m11m14 - m_6 * m9m15_m11m13 + m_7 * m9m14_m10m13)
			- m_1 * (m_4 * m10m15_m11m14 - m_6 * m8m15_m11m12 + m_7 * m8m14_m10m12)
			+ m_2 * (m_4 * m9m15_m11m13 - m_5 * m8m15_m11m12 + m_7 * m8m13_m9m12)
			- m_3 * (m_4 * m9m14_m10m13 - m_5 * m8m14_m10m12 + m_6 * m8m13_m9m12);

		if (det == 0) { throw "4x4 matrix has determinant == 0; cannot compute inverse"; }
		float invDet = 1.f / det;

		// translation matrix
		if (m_0 == 1 && m_1 == 0 && m_2 == 0 && m_3 == 0 &&
			m_4 == 0 && m_5 == 1 && m_6 == 0 && m_7 == 0 &&
			m_8 == 0 && m_9 == 0 && m10 == 1 && m11 == 0 &&
			m15 == 1)
		{
			invertedMatrix(0) = 1;
			invertedMatrix(1) = 0;
			invertedMatrix(2) = 0;
			invertedMatrix(3) = 0;

			invertedMatrix(4) = 0;
			invertedMatrix(5) = 1;
			invertedMatrix(6) = 0;
			invertedMatrix(7) = 0;

			invertedMatrix(8) = 0;
			invertedMatrix(9) = 0;
			invertedMatrix(10) = 1;
			invertedMatrix(11) = 0;

			invertedMatrix(12) = -1 * m12;
			invertedMatrix(13) = -1 * m13;
			invertedMatrix(14) = -1 * m14;
			invertedMatrix(15) = 1;
		}

		// scaling matrix
		else if (
			m_0 != 0 && m_1 == 0 && m_2 == 0 && m_3 == 0 &&
			m_4 == 0 && m_5 != 0 && m_6 == 0 && m_7 == 0 &&
			m_8 == 0 && m_9 == 0 && m10 != 0 && m11 == 0 &&
			m12 == 0 && m13 == 0 && m14 == 0 && m15 == 1)
		{
			invertedMatrix(0) = 1.f / m_0;
			invertedMatrix(1) = 0;
			invertedMatrix(2) = 0;
			invertedMatrix(3) = 0;

			invertedMatrix(4) = 0;
			invertedMatrix(5) = 1.f / m_5;
			invertedMatrix(6) = 0;
			invertedMatrix(7) = 0;

			invertedMatrix(8) = 0;
			invertedMatrix(9) = 0;
			invertedMatrix(10) = 1.f / m10;
			invertedMatrix(11) = 0;

			invertedMatrix(12) = 0;
			invertedMatrix(13) = 0;
			invertedMatrix(14) = 0;
			invertedMatrix(15) = 1;
		}

		// rotation matrix about x-axis
		else if (m_5 == m10 && m_6 - sinf(acosf(m_5)) < powf(10, -7) && m_6 == -1 * m_9 &&
			m_0 == 1 && m_1 == 0 && m_2 == 0 && m_3 == 0 &&
			m_4 == 0 && m_7 == 0 &&
			m_8 == 0 && m11 == 0 &&
			m12 == 0 && m13 == 0 && m14 == 0 && m15 == 1)
		{
			invertedMatrix(0) = 1;
			invertedMatrix(1) = 0;
			invertedMatrix(2) = 0;
			invertedMatrix(3) = 0;

			invertedMatrix(4) = 0;
			invertedMatrix(5) = m_5;
			invertedMatrix(6) = -1 * m_6;
			invertedMatrix(7) = 0;

			invertedMatrix(8) = 0;
			invertedMatrix(9) = -1 * m_9;
			invertedMatrix(10) = m10;
			invertedMatrix(11) = 0;

			invertedMatrix(12) = 0;
			invertedMatrix(13) = 0;
			invertedMatrix(14) = 0;
			invertedMatrix(15) = 1;
		}

		// rotation matrix about y-axis
		else if (m_0 == m10 && m_8 - sinf(acosf(m_0)) < powf(10, -7) && m_8 == -1 * m_2 &&
			m_1 == 0 && m_3 == 0 &&
			m_4 == 0 && m_5 == 1 && m_6 == 0 && m_7 == 0 &&
			m_9 == 0 && m11 == 0 &&
			m12 == 0 && m13 == 0 && m14 == 0 && m15 == 1)
		{
			invertedMatrix(0) = m_0;
			invertedMatrix(1) = 0;
			invertedMatrix(2) = -1 * m_2;
			invertedMatrix(3) = 0;

			invertedMatrix(4) = 0;
			invertedMatrix(5) = 1;
			invertedMatrix(6) = 0;
			invertedMatrix(7) = 0;

			invertedMatrix(8) = -1 * m_8;
			invertedMatrix(9) = 0;
			invertedMatrix(10) = m10;
			invertedMatrix(11) = 0;

			invertedMatrix(12) = 0;
			invertedMatrix(13) = 0;
			invertedMatrix(14) = 0;
			invertedMatrix(15) = 1;
		}

		// rotation matrix about z-axis
		else if (m_0 == m_5 && m_1 - sinf(acosf(m_0)) < powf(10, -7) && m_1 == -1 * m_4 &&
		m_2 == 0 && m_3 == 0 &&
		m_6 == 0 && m_7 == 0 &&
		m_8 == 0 && m_9 == 0 && m10 == 1 && m11 == 0 &&
		m12 == 0 && m13 == 0 && m14 == 0 && m15 == 1)
		{
		invertedMatrix(0) = m_0;
		invertedMatrix(1) = -1 * m_1;
		invertedMatrix(2) = 0;
		invertedMatrix(3) = 0;

		invertedMatrix(4) = -1 * m_4;
		invertedMatrix(5) = m_5;
		invertedMatrix(6) = 0;
		invertedMatrix(7) = 0;

		invertedMatrix(8) = 0;
		invertedMatrix(9) = 0;
		invertedMatrix(10) = 1;
		invertedMatrix(11) = 0;

		invertedMatrix(12) = 0;
		invertedMatrix(13) = 0;
		invertedMatrix(14) = 0;
		invertedMatrix(15) = 1;
		}

		// general 4x4 inverse
		else
		{
			// used only for adjoint
			float m6m15_m7m14 = m_6 * m15 - m_7 * m14;
			float m5m15_m7m13 = m_5 * m15 - m_7 * m13;
			float m9m14_m10m13 = m_9 * m14 - m10 * m13;
			float m5m11_m7m9 = m_5 * m11 - m_7 * m_9;
			float m6m11_m7m10 = m_6 * m11 - m_7 * m10;
			float m5m10_m6m9 = m_5 * m10 - m_6 * m_9;
			float m4m15_m7m12 = m_4 * m15 - m_7 * m12;
			float m4m14_m6m12 = m_4 * m14 - m_6 * m12;
			float m4m11_m7m8 = m_4 * m11 - m_7 * m_8;
			float m4m10_m6m8 = m_4 * m10 - m_6 * m_8;
			float m4m13_m5m12 = m_4 * m13 - m_5 * m12;
			float m4m9_m5m8 = m_4 * m_9 - m_5 * m_8;
			float m5m14_m6m13 = m_5 * m14 - m_6 * m13;

			invertedMatrix(0) = invDet * (m_5 * m10m15_m11m14 - m_6 * m9m15_m11m13 + m_7 * m9m14_m10m13);
			invertedMatrix(1) = invDet * (m_2 * m9m15_m11m13 - m_1 * m10m15_m11m14 - m_3 * m9m14_m10m13);
			invertedMatrix(2) = invDet * (m_1 * m6m15_m7m14 - m_2 * m5m15_m7m13 + m_3 * m5m14_m6m13);
			invertedMatrix(3) = invDet * (m_2 * m5m11_m7m9 - m_1 * m6m11_m7m10 - m_3 * m5m10_m6m9);

			invertedMatrix(4) = invDet * (m_6 * m8m15_m11m12 - m_4 * m10m15_m11m14 - m_7 * m8m14_m10m12);
			invertedMatrix(5) = invDet * (m_0 * m10m15_m11m14 - m_2 * m8m15_m11m12 + m_3 * m8m14_m10m12);
			invertedMatrix(6) = invDet * (m_2 * m4m15_m7m12 - m_0 * m6m15_m7m14 - m_3 * m4m14_m6m12);
			invertedMatrix(7) = invDet * (m_0 * m6m11_m7m10 - m_2 * m4m11_m7m8 + m_3 * m4m10_m6m8);

			invertedMatrix(8) = invDet * (m_4 * m9m15_m11m13 - m_5 * m8m15_m11m12 + m_7 * m8m13_m9m12);
			invertedMatrix(9) = invDet * (m_1 * m8m15_m11m12 - m_0 * m9m15_m11m13 - m_3 * m8m13_m9m12);
			invertedMatrix(10) = invDet * (m_0 * m5m15_m7m13 - m_1 * m4m15_m7m12 + m_3 * m4m13_m5m12);
			invertedMatrix(11) = invDet * (m_1 * m4m11_m7m8 - m_0 * m5m11_m7m9 - m_3 * m4m9_m5m8);

			invertedMatrix(12) = invDet * (m_5 * m8m14_m10m12 - m_4 * m9m14_m10m13 - m_6 * m8m13_m9m12);
			invertedMatrix(13) = invDet * (m_0 * m9m14_m10m13 - m_1 * m8m14_m10m12 + m_2 * m8m13_m9m12);
			invertedMatrix(14) = invDet * (m_1 * m4m14_m6m12 - m_0 * m5m14_m6m13 - m_2 * m4m13_m5m12);
			invertedMatrix(15) = invDet * (m_0 * m5m10_m6m9 - m_1 * m4m10_m6m8 + m_2 * m4m9_m5m8);
		}
	}

	else
	{
		throw "Code not written for calculating inverse of matrix of size > 4x4";
	}

	return invertedMatrix;

}




