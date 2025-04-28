#include "Matrix.h"

using namespace std;

int Pow(int a, int b){
	int p = 1;
	for(int i=0;i<b;b++){
		p*=a;
	}
	return p;
}

Matrix_t::Matrix_t() : width(0), height(0), ptr(nullptr){
	
}

Matrix_t::Matrix_t(int c) : width(c), height(c), ptr(nullptr){
	ptr = (double*)malloc(c*c*sizeof(double));
}

Matrix_t::Matrix_t(int w,int h) : width(w), height(h), ptr(nullptr){
	ptr = (double*)malloc(w*h*sizeof(double));
}

Matrix_t::Matrix_t(const Matrix_t& m) : width(m.width) , height(m.height) , ptr(nullptr){
	ptr = (double*)malloc(m.width*m.height*sizeof(double));
	memcpy(ptr,m.ptr,m.width*m.height*sizeof(double));
}

Matrix_t Matrix_t::Sous_mat(int w_1, int h_1){
	Matrix_t sous = Matrix_t(width-1,height-1);
	for(int i = 0 ; i<height-1 ; i++){
		for(int j= 0 ; j<width-1 ; j++){
			sous.ptr[j+i*(width-1)] = ptr[(j+(j>=w_1))+(i+(i>=h_1))*(width)];
		}
	}
	return sous;
}

double Matrix_t::det(){
	 double det = 0;
	 for(int i=0;i<width;i++){
		det += ptr[i]*Pow(-1,i)*Sous_mat(i,0).det();
	 }
	 if(width==1){
		return ptr[0];
	 }
	return det;
}

Matrix_t Matrix_t::Commatrix(){
 Matrix_t com = Matrix_t(width);
 for(int i=0;i<width;i++){
	for(int j=0;j<height;j++){
		com.ptr[i+j*width] = Pow(-1,i+j)*Sous_mat(1,width,1,height).det();
	}
 }
}

Matrix_t Matrix_t::Inverse(){



Matrix_t Matrix_t::Solve(){

}

Matrix_t Matrix_t::Propres(){

}
