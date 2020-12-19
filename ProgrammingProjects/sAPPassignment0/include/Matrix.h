#ifndef __MATRIXH__
#define __MATRIXH__

//needed libraries 
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

//so an object of Matrix can choose between int or something else
//also use of unsigned for memory
template <class T>
class Matrix
{
//private
private:
	//friends for overloading (nonmember classes can access)
	template <typename TE> friend Matrix<TE> operator*(const Matrix<TE>& a, const Matrix<TE>& b);
	template <typename TE> friend std::ostream& operator<<(std::ostream &os, const Matrix<TE>& x);
	template <typename TE> friend std::istream& operator>>(std::istream &is, Matrix<TE>& x);

	//used instead of ** (vector is cpp's built in * with its own indexing)
	//a simple * with an index could also suffice but I really prefer [][]
	//this is also done to avoid deconstructors and badalloc
	std::vector<std::vector<T>> mat;
	//rows and cols
	unsigned N;
	unsigned M;
//public
public:
	//empty initializer
	Matrix<T>(): N(0), M(0) {}

	//initializer
	Matrix<T>(unsigned N, unsigned M, T init=0)
	{
		//give object dimensions N and M
		this->N=N;
		this->M=M;
		//resize
		mat.resize(N);
		//fill with init
		for (unsigned i=0; i<N; i++) {mat[i].resize(M); fill(mat[i].begin(),mat[i].end(),init);}

	}

	//to return pointed vector and access to cols 
	std::vector<T>& operator[](unsigned i) {return mat[i];}
	std::vector<T> operator[](unsigned i) const {return mat[i];}

	Matrix<T>& Fill(const T &val)
	{
		for (unsigned i=0; i<N; i++)
			fill(mat[i].begin(),mat[i].end(),val);
		return *this;
	}

	//append rows
	Matrix<T>& AppendRow(T init=0)
	{
		//new row
		std::vector<T> r(M,init);
		//add row to mat
		mat.push_back(r);
		//+1 row
		N++;
		return *this;
	}

	//append columns
	Matrix<T>& AppendCol(T init=0)
	{
		//go through cols and add init
		for (unsigned i=0;i<N;i++)
			mat[i].push_back(init);
		//+1 cols
		M++;
		return *this;
	}

	//clear matrix 
	Matrix<T>& Clear()
	{
		mat.clear();
		N=M=0;
		return *this;
	}

	//get rows and cols (private)
	unsigned Rows() const {return N;}
	unsigned Cols() const {return M;}

	//Determinant
	static T Det(const Matrix<T>& x);

	//cofactor
	Matrix<T> Cof(unsigned i, unsigned j) const;
	//det to return *this
	T Det() const;
	//inverse
	Matrix<T> Inv() const;
	//transpose
	Matrix<T> tp() const;
};

//location
#include "../class/Matrix.cpp"

#endif 
