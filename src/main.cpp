#include "../includes/NumericMethodsFODU.h"

using namespace std;

int main() {
   NumericODUSolver solver("settings/eurSettings1.txt");
   solver.printSolver();
   if (solver.getMethod() == "expEuler")
      solver.explicitEuler();
   else
      cout << "No such method as: \"" << solver.getMethod() << "\"";
   return 0;
}