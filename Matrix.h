#include <math.h>
#include <iostream>
using namespace std;

class Matrix_t{
private:
	int width;
	int height;
	double* ptr; // On utilise un simple pointeur pour que les valeurs soit en un bloc dans la mémoire
public:
	Matrix_t();
	Matrix_t(int c);
	Matrix_t(int w,int h);
	Matrix_t(const Matrix_t&);
	double det();
	Matrix_t trans();
	Matrix_t Commatrix();
	Matrix_t Inverse();
	Matrix_t Solve(Matrix_t& b);
	Matrix_t Propres();
	Matrix_t Sous_mat(int w_1 ,int h_1);
	Matrix_t& operator*=(double d);
	Matrix_t& operator*(double d);
	Matrix_t& operator/(double d);
	Matrix_t& operator/=(double d);
	Matrix_t& operator+=(const Matrix_t& d);
	Matrix_t& operator+(const Matrix_t& d);
	Matrix_t& operator* (const Matrix_t& d);
};
