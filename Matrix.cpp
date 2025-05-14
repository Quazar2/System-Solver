#include "Matrix.h"
#include <cstring>
#ifndef _WIN32
#else
void clrscr() {
	system("cls");
}
#include <windows.h>
#include <conio.h>
void gotoxy(int x, int y)
{
	COORD coo;
	coo.X = x;
	coo.Y = y-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
}
#endif
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

Matrix_t::~Matrix_t(){
	if(ptr!=nullptr){
		free(ptr);
	}
}

Matrix_t::Matrix_t(int c) : width(c), height(c), ptr(nullptr){
	ptr = (double*)calloc(c*c,sizeof(double));
}

Matrix_t::Matrix_t(int w , int h) : width(w), height(h), ptr(nullptr){
	ptr = (double*)calloc(w*h,sizeof(double));
}
Matrix_t::Matrix_t(const Matrix_t& m) : width(m.width) , height(m.height) , ptr(nullptr){
	ptr = (double*)calloc(m.width*m.height,sizeof(double));
	memcpy(ptr,m.ptr,m.width*m.height*sizeof(double));
}

ostream& operator<<(ostream& os,Matrix_t& m){
	for(int i =0;i<m.height;i++){
			for(int j=0;j<m.width;j++){
				printf("%.6g\t",m.ptr[i*m.width+j]);
		}
			printf("\n");
	}
	return os;
}

int Matrix_t::get_width(){
	return width;
}

int Matrix_t::get_height(){
	return height;
}
void Matrix_t::v_editor(int h){
	char c = 'a';
	char arrow =0;
	int size = h;
	int cursor_x = 0;
	int cursor_y = 0;
	int cell_x = 0;
	int cell_y = 0;
	double* grid = (double*)calloc(h, sizeof(double));
	bool EDITING = false;
	char* buffer = (char*)calloc(1024, sizeof(char));
	int buff_head = 0;
	clrscr();
	printf("Please input your system's B matrix in this Matrix\n\n");
		for (int j = 0; j < size; j++) {
			printf("%.6g\n", grid[j]);
		}
		printf("\n");
	printf("s = confirm  | k = up | j = down | enter = edit \n");

	gotoxy(cursor_x, cursor_y + 3);
	while (1 == 1) {
		if (_kbhit()) {
			c = _getch();
			while(c==91|c==27){
				c= _getch();
				arrow=1;
			}
			if (c == 's') { 
				
				sscanf_s(buffer, "%lf", &grid[cell_y]);
				break; 
			}
			if (c == '\n' || c == '\r') {
				if (EDITING) {
					sscanf_s(buffer, "%lf", &grid[cell_y]);
					memset(buffer, '\0', 1024);
					buff_head = 0;
				}
				EDITING = !EDITING;
			}
			else if (((c == '-' && buff_head == 0) || ((c >= '0') && (c <= '9')) || (c == '.')) && (buff_head < 1024)) {
				EDITING = true;
				buffer[buff_head] = c;
				buff_head++;
				cursor_x++;
			}
			else if ((c == '\b' || c==127) && (buff_head > 0)) {
				buffer[buff_head-1] = '\0';
				buff_head--;
				cursor_x--;
			}
			else if ((c == 'j' || ((c==66 || c==80)&&arrow==1)) && cell_y < size - 1) {
				if (EDITING) {
					sscanf_s(buffer, "%lf", &grid[cell_y]);
					memset(buffer, '\0', 1024);
					buff_head = 0;
					EDITING = !EDITING;
				}
				cell_y++;
			}
			else if ((c == 'k' || ((c == 65 || c==72)&&arrow==1)) && cell_y > 0) {
				if (EDITING) {
					sscanf_s(buffer, "%lf", &grid[cell_y]);
					memset(buffer, '\0', 1024);
					buff_head = 0;
					EDITING = !EDITING;
				}
				cell_y--;
			}
			clrscr();
			printf("Please input your system's B matrix in this Matrix\n\n");
			for (int j = 0; j < size; j++) {
				if (EDITING && cell_y == j) {
					printf("%s\n", buffer);
				}
				else {
					printf("%.6lg\n", grid[j]);
				}
			}
			
			printf("\n");
			printf("s = confirm | + = bigger | - = smaller | h = left | l = right | k = up | j = down | enter = edit \n");
			cursor_x = cell_x * 8 + 4;
			cursor_y = cell_y;
			printf("%d", c);
			gotoxy(cursor_x, cursor_y + 3);
		}
	}
	ptr = (double*)realloc(ptr,size * sizeof(double));
	for (int i = 0; i < size; i++) {
		memcpy(ptr, grid, size * sizeof(double));
	}
	width = 1;
	height = size;
	clrscr();
	free(buffer);
	free(grid);
}
void Matrix_t::editor (){
  char c = 'a';
  char arrow =0;
  int size = width;
  int cursor_x=0;
  int cursor_y=0;
  int cell_x = 0;
  int cell_y = 0;
  double** grid =(double**) calloc(size,sizeof(double*));
  for(int i=0;i<size;i++){
	  grid[i] = (double*) calloc(size,sizeof(double));
	  memcpy(grid[i],&ptr[i],size*sizeof(double));
  }
  bool EDITING = false;
  char* buffer =(char*) calloc(1024,sizeof(char));
  int buff_head =0;
  clrscr();
  printf("Please input your n * n sytem in this Matrix\n\n");
  for (int i = 0; i < size; i++) {
	  for (int j = 0; j < size; j++) {
		  if (EDITING && cell_x == j && cell_y == i) {
			  printf("%s\t", buffer);
		  }
		  else {
			  printf("%.6lg\t", grid[i][j]);
		  }
	  }
	  printf("\n");
  }
  printf("\ns = confirm | + = bigger | - = smaller | h = left | l = right | k = up | j = down | enter = edit \n");
  while(1==1){
    if(_kbhit()){
		c= _getch();
		while(c==91|c==27){
			c= _getch();
			arrow=1;
		}
		if (c=='s'){
			sscanf_s(buffer, "%lf", &grid[cell_y][cell_x]);
			break;
		}
		if(c=='\n'||c=='\r') {
			if(EDITING){
				sscanf_s(buffer,"%lf",&grid[cell_y][cell_x]);
				memset(buffer,'\0',1024);
				buff_head=0;
			}
			EDITING = !EDITING;
		}else if((!EDITING)&&c=='+'){
			grid =(double**) realloc(grid,(size+1)*sizeof(double*));
			grid[size]=nullptr;
			for(int i=0;i<size+1;i++){
				grid[i] = (double*) realloc(grid[i],(size+1)*sizeof(double));
				
			}
			for (int j = 0; j <= size; j++) {
				for (int i = 0; i < size + 1; i++) {
					grid[j][i] = 0;
				}
			}
			size+=1;
		}
		else if((!EDITING)&&c=='-'){
			grid =(double**) realloc(grid,(size-1)*sizeof(double*));
			for(int i=0;i<size-1;i++){
				grid[i] = (double*) realloc(grid[i],(size-1)*sizeof(double));
			}
			size -= 1;
		}else if(((EDITING&&c=='-'&&buff_head==0)||((c>='0') && (c<='9'))||(c=='.')) && (buff_head<1024)){
			    EDITING = true;
				buffer[buff_head]=c;
				buff_head++;
				cursor_x++;
			}else if((c=='\b'||c==127)&&(buff_head>0)){
				buffer[buff_head-1] = '\0';
				buff_head--;
				cursor_x--;
			}
			else if ((c == 'l'||((c==67||c==77)&&arrow==1)) && cell_x < size - 1) {
			if(EDITING){
				sscanf_s(buffer,"%lf",&grid[cell_y][cell_x]);
				memset(buffer,'\0',1024);
				buff_head=0;
				EDITING = !EDITING;
			}
			cell_x++;
		}
			else if ((c == 'h'||((c==68||c==75)&&arrow==1)) && cell_x > 0) {
			if(EDITING){
				sscanf_s(buffer,"%lf",&grid[cell_y][cell_x]);
				memset(buffer,'\0',1024);
				buff_head=0;
				EDITING = !EDITING;
			}
			
			cell_x--;
		}else if((c=='j'||((c==66||c==80)&&arrow==1)) && cell_y<size - 1) {
			if(EDITING){
				sscanf_s(buffer,"%lf",&grid[cell_y][cell_x]);
				memset(buffer,'\0',1024);
				buff_head=0;
				EDITING = !EDITING;
			}
			cell_y++;
		}else if((c=='k'||((c==65||c==72)&&arrow==1)) && cell_y>0) {
			if(EDITING){
				sscanf_s(buffer,"%lf",&grid[cell_y][cell_x]);
				memset(buffer,'\0',1024);
				buff_head=0;
				EDITING = !EDITING;
			}
			cell_y--;
		}
		clrscr();
		printf("Please input your n * n sytem in this Matrix\n\n");
		for(int i =0;i<size;i++){
			for(int j=0;j<size;j++){
				if(EDITING&&cell_x==j&&cell_y==i){
					printf("%s\t",buffer);
				}else{
				printf("%.6lg\t",grid[i][j]);
				}
			}
			printf("\n");
		}
		printf("\ns = confirm | + = bigger | - = smaller | h = left | l = right | k = up | j = down | enter = edit \n");
		cursor_x=cell_x*8+4;
		cursor_y=cell_y;
		printf("%c",c);
		gotoxy(cursor_x,cursor_y+3);
		arrow=0;
	}
 }
	ptr =(double*) realloc(ptr,size*size*sizeof(double));
	for(int i=0;i<size;i++){
		memcpy(&ptr[i*size],grid[i],size*sizeof(double));
	}
	width = size;
	height = size;
	clrscr();
	free(buffer);
	  for(int i=0;i<size;i++){
		  free(grid[i]);
	  }
	free(grid);
}

Matrix_t Matrix_t::trans(){
	Matrix_t t = Matrix_t(width);
	for(int i = 0 ; i<width;i++){
		for(int j=0;j<height;j++){
			t.ptr[j+i*width] = ptr[i+j*width];
		}
	}
	return t;
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
	 int coffac = 1;
	 for(int i=0;i<width;i++){
		det += ptr[i]*coffac*Sous_mat(i,0).det();
		coffac*=-1;
	 }
	 if(width==1){
		return ptr[0];
	 }
	return det;
}

Matrix_t Matrix_t::Commatrix(){
 Matrix_t com = Matrix_t(*this);
 int coffac =1;
 for(int i=0;i<width;i++){
	for(int j=0;j<height;j++){
		com.ptr[i+j*width] = coffac*Sous_mat(i,j).det();
		coffac*=-1;
	}
	coffac*=-1;
 }
 if(width==1){
	 com.ptr[0]=1;
 }
 return com;
}

Matrix_t Matrix_t::operator*=(double d){
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			ptr[i+j*width]*=d;
		}
	}

	return *this;
}

Matrix_t Matrix_t::operator*(double d){

	Matrix_t res = Matrix_t(*this);
	res*=d;
	return res;
}

Matrix_t Matrix_t::operator/=(double d){
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			ptr[i+j*width]/=d;
		}
	}

	return *this;
}

Matrix_t Matrix_t::operator/(double d){
	Matrix_t res = Matrix_t(*this);
	res/=d;
	return res;
}

Matrix_t Matrix_t::operator+=(const Matrix_t& d){
	if(width==d.width&height==d.height){
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				ptr[i+j*width]+=d.ptr[i+j*width];
			}
		}
	}
	return *this;
}
Matrix_t Matrix_t::operator+(const Matrix_t& d){
	Matrix_t mat  = Matrix_t(*this);
	mat+=d;
	return mat;
}

Matrix_t Matrix_t::operator*(Matrix_t& d){
	Matrix_t res = Matrix_t(d.width,height);
	for(int h =0;h<height;h++){
		for(int i = 0;i<d.width;i++){
			res.ptr[i+h*(d.width)]=0;
			for(int j=0;j<width;j++) {
				res.ptr[i+h*(d.width)] += ptr[j+h*width]*d.ptr[i+j*d.width];
			}
		}
	}
	return res;
}

Matrix_t Matrix_t::Inverse(){
	Matrix_t co = Commatrix().trans();
	return co/det();
}


Matrix_t Matrix_t::Solve(Matrix_t& b){
	if(det()>0.00001||det()<-0.00001){
		Matrix_t inv = Inverse();
		return inv*b;
	}else{
		return NULL;
	}
}

Matrix_t Matrix_t::Solve_Pivot(Matrix_t& b){
	if(det()>0.00001||det()<-0.00001){
		Matrix_t temp = Matrix_t(*this);
		Matrix_t solut = Matrix_t(1,b.height);
		for(int i=0;i<b.height;i++){
			for(int j =0;j<b.height;j++){
				temp.ptr[i+j*width]= b.ptr[j];
			}
			solut.ptr[i]=temp.det()/det();
			for(int j =0;j<b.height;j++){
				temp.ptr[i+j*width]= ptr[i+j*width];
			}
		}
		return solut;
	}
	return NULL;

}
Matrix_t Matrix_t::Propres(){
	return NULL;
}
