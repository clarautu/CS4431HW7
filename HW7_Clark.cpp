// HW 7
// Autumn Clark
// Numerical integration with trapezoid rule and Simpson's rule
// Done using class Function -- shoud be doen using pass-by-function

#include <iostream>
#include <vector>
#include "FunctionClass.h"

// Method that performs numerical intergration by the trapezoid rule
//     a and b are the start and end of the interval
//     n is the number of bins to be used -- directly tied to accuracy
//     f is a specified custom class Function
double TrapezoidInteg(double a, double b, int n, Function f){
  double delta = (b-a)/n; // Width of each trapeziod
  double total = f.EvaluateAt(a); // First call to function
  for(int i=1; i<n; i++){
    total += 2 * f.EvaluateAt(a + delta*(i)); // All inner calls -- multiply each call by 2
  }
  total += f.EvaluateAt(b); // Last call to the function
  total = (total * (delta/2)); // Multiply running total by delta / 2, then reassign
  return total;
}

// Method that performs numerical intergration by Simpson's Rule
//     a and b are the start and end of the interval
//     n is the number of bins to be used -- directly tied to accuracy -- must be even for Simpson's
//     f is a specified custom class Function
double SimpsonInteg(double a, double b, int n, Function f){
  if(n%2 != 0){ // Check if n is odd
    std::cout << "Bins must be even!" << std::endl;
    return -1; // If odd, return -1
  }
  double delta = (b-a)/n; // Width of each trapeziod
  double total = f.EvaluateAt(a); // First call to function
  for(int i=1; i<n; i++){
    if(i%2 == 0){ // Even calls are multiplied by 2
      total += 2 * f.EvaluateAt(a + delta*(i));
    } else{ // Odd calls are multiplied by 4
      total += 4 * f.EvaluateAt(a + delta*(i));
    }
  }
  total += f.EvaluateAt(b); // Last call to the function
  total = (total * (delta/3)); // Multiply running total by delta / 3, then reassign
  return total;
}

int main(){
  std::vector<double> v ={1,0,1};
  Function f(v);
  f.PrintFunction();
  double result = TrapezoidInteg(1,5,4,f);
  std::cout << "Result of trapezoid rule: " << result << std::endl;
  result = SimpsonInteg(1,5,4,f);
  std::cout << "Result of Simpson's Rule: " << result << std::endl;

  /* // Test code
  double x = 22;
  double y = f.EvaluateAt(x);
  std::cout << "Function at " << x << " = " << y << std::endl;
  */

  return 0;
}
