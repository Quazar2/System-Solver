#include "Matrix.h"

int main(int argc, char *argv[]) {

  Matrix_t cramer =Matrix_t();
  cramer.editor();
  while((cramer.det()>-0.00005)&&(cramer.det()<0.00005)){
	printf("Det is null press any key to retry\n");
	_getch();
  	cramer.editor();
	
  }

  Matrix_t b = Matrix_t();
  b.v_editor(cramer.get_height());
  Matrix_t solut = cramer.Solve(b);
  Matrix_t solut_pivot = cramer.Solve_Pivot(b);

  Matrix_t test = cramer*solut;
  cout<<"La solution par Cramer :\n"<<solut<<endl<<"La solution par le pivot de Gauss :\n"<<solut_pivot<<endl;
  Matrix_t diff = Matrix_t(solut);
  diff-=solut_pivot;
  auto mult_1 =cramer*solut;
  auto mult_2 =cramer*solut_pivot;
  cout<<"La différence entre les deux :\n"<<mult_1<<endl<<mult_2;
  return 0;
}
