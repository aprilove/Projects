//for the Matrix class
//make file will collect the objects and hand them to compiler
#include <conio.h> 
#include "include/Matrix.h"

//typically this is frowned upon but... 
using namespace std;

int main()
{
	//output expected input and formatting
	cout << "A Vandermonde Matrix is typically in the form of  [ 1 , x1 , x1^2 , ... , x1^N-1 ; 1 , x2 , x2^2 , ... , x2^N-1 ;  1 , xM , xM^2 , ... , xM^N-1 ]" << endl
		 << "Insert the Vandermonde Matrix as such: 1 2 4 " << endl
		 << "                                       1 9 81 " << endl
		 << "                                       1 3 9 " << endl
		 << "                                       1 4 16 " << endl;
	//define matrix
	Matrix<float> V1;
	
	Matrix<float> y;
	//cin values of V1
	cin >> V1;
	//find the transpose
	Matrix<float> V1T(V1.tp());
	//output the input matrix and transpose and the product of them
	cout << "V:\n"
		 << V1 << endl
		 << "V^T:\n"
		 << V1T << endl
		 << "(V^T)*(V):\n"
		 << V1T * V1 << endl;
	//find inverse of matrix
	//this is intialized later as the determinant of V1T * V1 may be 0
	Matrix<float> V1TV(V1T * V1);
	Matrix<float> V1I(V1TV.Inv());
	cout << "((V^T)*(V))^-1\n"
		 << V1I << endl
		 << "Insert y: " << endl;
	//cin values of y11
	//this is done later because the user may just want V1T * V1 and they can simply terminate program here
	cin >> y;
	//output the product of the (V1T * V1)^-1 , V1T and y
	cout << "The coefficients are: " << endl;
	Matrix<float> Vtemp(V1I * V1T);
	cout << Vtemp * y;
	return 0;
}
