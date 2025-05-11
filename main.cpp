#include "Matrix.h"

int main(int argc, char *argv[]) {

  Matrix_t cramer =Matrix_t();
  cramer.editor();

  Matrix_t b = Matrix_t();
  b.v_editor(cramer.get_height());
  Matrix_t solut = cramer.Solve(b);
  Matrix_t solut_pivot = cramer.Solve_Pivot(b);

  Matrix_t test = cramer*solut;
  cout<<solut<<endl<<solut_pivot<<endl;
  cout<<test<<endl;
  return 0;
}
