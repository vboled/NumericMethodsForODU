#include "../includes/NumericMethodsFODU.h"

using namespace std;

double getR(std::vector<double> init, double a) {
   return -1;
}

double getA(std::vector<double> init) {
   return -3;
}

int main() {
   NumericODUSolver solver("settings/rk4Settings.txt");
   solver.printSolver();
   if (solver.getMethod() == "expEuler")
      solver.explicitEuler();
   else if (solver.getMethod() == "rk2")
      solver.rk2();
   else if (solver.getMethod() == "rk4")
      solver.rk4();
   else if (solver.getMethod() == "impEuler")
      solver.implicitEuler();
   else
      cout << "No such method as: \"" << solver.getMethod() << "\"";
   if (solver.getTest() == "myTest1" || solver.getTest() == "pendulum") {
      cout.precision(10);
      cout << "residual " << solver.residual();
   }
   return 0;
}