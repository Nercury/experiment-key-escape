#pragma once

#include <string>

template<class _T, int _WIDTH, int _HEIGHT>
class Matrix
{
public:
	typedef _T Type;

public:
	Matrix();
	Matrix(const _T *data);
	Matrix(const Matrix<_T, _WIDTH, _HEIGHT> &m);

	template<class _U>
	Matrix& operator = (const Matrix<_U, _WIDTH, _HEIGHT> &m);
	
	static const Matrix& identityMatrix();
	static const Matrix& zeroMatrix();

	template <int _MW, int _MH>
	static Matrix subMatrix(int r, int c, const Matrix<_T, _MW, _MH> &m);

	bool operator == (const Matrix &m) const;
	bool operator != (const Matrix &m) const;

	const _T* operator [] (int row) const;
	_T* operator [] (int row);

	int width() const;
	int height() const;

	const _T* ptr() const;
	_T* ptr();

	template<class _U>
	Matrix& copy(const _U *data);

	Matrix operator + (const Matrix &rhs) const;
	Matrix& operator += (const Matrix &rhs);
	Matrix operator - (const Matrix &rhs) const;
	Matrix& operator -= (const Matrix &rhs);
	Matrix& operator - ();

	template<int _RHSWIDTH>
	Matrix<_T, _RHSWIDTH, _HEIGHT> operator * (const Matrix<_T, _RHSWIDTH, _WIDTH> &rhs) const;
	Matrix operator *= (const Matrix<_T, _WIDTH, _HEIGHT> &rhs);

	Matrix operator * (const _T &rhs) const;
	Matrix& operator *= (const _T &rhs);

	Matrix operator / (const _T &rhs) const;
	Matrix& operator /= (const _T &rhs);
	
	Matrix& negative();
	bool inverse(Matrix& out);

	Matrix<_T, _HEIGHT, _WIDTH> transposed() const;

	// for square matrix
	void transpose();

	bool hasNan() const;
	bool hasInf() const;
	
	std::string serialize() const;
	static Matrix deSerialize(const std::string &str);

	template<int _MW, int _MH>
	Matrix<_T, _WIDTH, _HEIGHT>& copy(int r, int c, const Matrix<_T, _MW, _MH> &m);

	Matrix<_T, _WIDTH, _HEIGHT>& copyRow(int index, const Matrix<_T, _WIDTH, 1> &m);
	Matrix<_T, _WIDTH, _HEIGHT>& copyCol(int index, const Matrix<_T, 1, _HEIGHT> &m);

	Matrix<_T, _WIDTH, 1> row(int index) const;
	Matrix<_T, 1, _HEIGHT> col(int index) const;

	Matrix<_T, _WIDTH, _HEIGHT+1> addBackRow(const Matrix<_T, _WIDTH, 1> &r ) const;
	Matrix<_T, _WIDTH+1, _HEIGHT> addBackCol(const Matrix<_T, 1, _HEIGHT> &c) const;

	Matrix<_T, _WIDTH, _HEIGHT+1> addFrontRow(const Matrix<_T, _WIDTH, 1> &r ) const;
	Matrix<_T, _WIDTH+1, _HEIGHT> addFrontCol(const Matrix<_T, 1, _HEIGHT> &c) const;

	Matrix<_T, _WIDTH, _HEIGHT+1> addRow(int index, const Matrix<_T, _WIDTH, 1> &r ) const;
	Matrix<_T, _WIDTH+1, _HEIGHT> addCol(int index, const Matrix<_T, 1, _HEIGHT> &c) const;

	Matrix<_T, _WIDTH-1, _HEIGHT> removeBackCol() const;
	Matrix<_T, _WIDTH-1, _HEIGHT> removeFrontCol() const;
	Matrix<_T, _WIDTH-1, _HEIGHT> removeCol(int index) const;

	Matrix<_T, _WIDTH, _HEIGHT-1> removeBackRow() const;
	Matrix<_T, _WIDTH, _HEIGHT-1> removeFrontRow() const;
	Matrix<_T, _WIDTH, _HEIGHT-1> removeRow(int index) const;

public:
	_T element[_WIDTH*_HEIGHT];

private:
	size_t size() const;
	int count() const;
};

typedef Matrix<float, 1, 1> Matrix1f;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<double, 1, 1> Matrix1d;
typedef Matrix<double, 2, 2> Matrix2d;
typedef Matrix<double, 3, 3> Matrix3d;
typedef Matrix<double, 4, 4> Matrix4d;

#include "Matrix.inline.h"

