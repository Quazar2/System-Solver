#include "Matrix.h"

int main(int argc, char *argv[]) {

  Matrix_t cramer =Matrix_t();
  cramer.editor();

  Matrix_t b = Matrix_t();
  b.v_editor(cramer.get_height());
  Matrix_t solut = cramer.Solve(b);
  cout<<solut;
  return 0;
}
