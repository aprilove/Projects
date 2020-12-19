#ifndef __MATRIXCPP__
#define __MATRIXCPP__
#include <iostream>
#include "Matrix.h"

//overload * operator accepts 2 Matrix
template <typename TE>
Matrix<TE> operator*(const Matrix<TE> &a, const Matrix<TE> &b)
{
	//if dimensions don't mtach
	if (a.M != b.N)
		throw std::logic_error("Wrong Dimensions");

	//returned mat
	Matrix<TE> y(a.N, b.M);

	//multiply row entry a by col entry b and sum
	for (unsigned i = 0; i < y.N; i++)
	{
		for (unsigned j = 0; j < y.M; j++)
		{
			TE sum = 0;
			for (unsigned k = 0; k < b.N; k++)
				sum += a.mat[i][k] * b.mat[k][j];

			y.mat[i][j] = sum;
		}
	}

	return y;
}

//overload << 
template <typename TE>
std::ostream &operator<<(std::ostream &os, const Matrix<TE> &x)
{
	//displays the matrix
	for (unsigned i = 0; i < x.N; i++)
	{
		for (unsigned j = 0; j < x.M - 1; j++)
		{
			os << x.mat[i][j] << ",\t";
		}
		//adds a ; to the last one in the row
		os << x.mat[i][x.M - 1] << " ;" << std::endl;
	}
	return os;
}

//over load >> 
template <typename TE>
std::istream &operator>>(std::istream &is, Matrix<TE> &x)
{
	//find the rows and cols
	unsigned a, b;
	std::cout << "Enter the number of rows: " << std::endl;
	is >> a;
	std::cout << "Enter the number of cols: " << std::endl;
	is >> b;
	//temp to get data
	TE t;

	//get all the data by loop
	for (unsigned i = 0; i < a; i++)
	{
		//append rows when needed
		x.AppendRow();
		for (unsigned j = 0; j < b; j++)
		{
			//append columns on first loop
			if (i == 0)
				x.AppendCol();
			//get value
			is >> t;
			x.mat[i][j] = t;
		}
	}

	return is;
}

//find cofactor
template <class T>
Matrix<T> Matrix<T>::Cof(unsigned i, unsigned j) const
{
	//cofactor
	Matrix<T> y(N - 1, M - 1);

	unsigned kc = 0;
	for (unsigned kx = 0; kx < N; kx++)
	{
		//"crosses" out row i
		if (kx == i)
			continue;

		unsigned jc = 0;
		for (unsigned jx = 0; jx < N; jx++)
		{
			//"crosses" out col j
			if (jx == j)
				continue;
			//smaller mat y
			y.mat[kc][jc] = mat[kx][jx];
			jc++;
		}

		kc++;
	}

	return y;
}

//find determinant
template <class T>
T Matrix<T>::Det(const Matrix<T> &x)
{
	//non square
	if (x.N != x.M)
		throw std::logic_error("Non square matrix");

	//empty
	if (x.N == 0)
		throw std::logic_error("Empty matrix");

	//1 row
	if (x.N == 1)
		return x.mat[0][0];

	//determinant value
	T y = 0;

	//sign
	signed char d = 1;

	//sum a rows cofactors
	for (unsigned i = 0; i < x.N; i++)
	{
		y += d * x.mat[i][0] * Det(x.Cof(i, 0));
		d = -d;
	}

	return y;
}

//for det()
template <class T>
T Matrix<T>::Det() const
{
	return Det(*this);
}

template <class T>
Matrix<T> Matrix<T>::Inv() const
{
	//if det = 0
	double det_x = Det();
	if (abs(det_x) == 0)
		throw std::logic_error("Can't invert matrix  (determinant=0)");

	//inverse
	Matrix<T> y(N, M);

	//signed
	signed int d = 1;

	//goes through matrix
	for (unsigned i = 0; i < N; i++)
		for (unsigned j = 0; j < N; j++)
		{
			//adjoint method
			y.mat[j][i] = d * Det(Cof(i, j)) / det_x;
			d = -d;
		}

	return y;
}

template <class T>
Matrix<T> Matrix<T>::tp() const
{
	//transposed mat
	Matrix<T> t(M, N);

	//transposed
	for (unsigned i = 0; i < N; i++)
		for (unsigned j = 0; j < M; j++)
			t.mat[j][i] = this->mat[i][j];

	return t;
}
#endif
