#include "../includes/NumericMethodsFODU.h"

using namespace std;

template <typename T>
void trig_function()
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>     expression_t;
   typedef exprtk::parser<T>             parser_t;

   const std::string expression_string =
                     "x + 1.0)";

   T x;

   symbol_table_t symbol_table;
   symbol_table.add_variable("x",x);
   symbol_table.add_constants();

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   parser_t parser;
   parser.compile(expression_string,expression);

   for (x = T(-5); x <= T(+5); x += T(0.001))
   {
      x = 5;
      const T y = expression.value();
      printf("%19.15f\t%19.15f\n", x, y);
   }
}

int main() {
    trig_function<double>();
    cout << "Hello, world!\n";
}