// HW 7
// Autumn Clark
// Numerical integration with trapezoid rule and Simpson's rule

#include <iostream>
#include <vector>
#include <functional>

// Global vector to hold the coefficients to define the function
//     The format of coeff should be ascending order, with the first value being x^0
//     DON'T SKIP ZERO COEFFECIENTS!
//     i.e. x^2 + 2 would be stored as <2,0,1>
//     i.e. 9x^3 + 6x^2 would be stored as <0,0,6,9>
std::vector<double> coeff;

// Method that prints the function to the screen
void PrintFunction(){
  // If first coeff is zero, it will still print out -- looks weird without it, because of the + sign
  std::cout << "Function is:\n\t" << coeff.at(0);
  for(int i=1; i<coeff.size(); i++){
    if(coeff.at(i) == 0){
      // Print nothing, as coeff is a zero -- can be omitted
    } else{
      std::cout << " + " << coeff.at(i) << "x^" << i;
    }
  }
  std::cout << "\n";
}

// Method that evaluates a specified x at the specified power -- used by Function()
double XToThePower(double const x, int power){
  double total = x; // Have total start at x's value
  while(power>1){ // While the power is above 1 -- starts multipling at x^2
    total *= x; // Times total by the original x
    power--; // Decrement power
  }
  return total; // Return total
}

// Function that evaluates the global function at x
double Function(double x){
  double total = coeff.at(0); // Double to hold the total value -- start at value of first coeffecient (x^0)
  for(int i=1; i<coeff.size(); i++){ // Loop through coeff -- don't do the first entry (x^0)
    double temp = XToThePower(x, i); // Evaluate x at the correct power -- store in temp
    total += (temp*coeff.at(i)); // Multiply temp and the current position's coeffecient, then add to total
  }
  return total; // Return the total
}

// Method that performs numerical intergration by the trapezoid rule
//     a and b are the start and end of the interval
//     n is the number of bins to be used -- directly tied to accuracy
//     function Function() is passed as an argument
double TrapezoidInteg(double a, double b, int n, std::function<double(double x)> Function){
  double delta = (b-a)/n; // Width of each trapeziod
  double total = Function(a); // First call to function
  for(int i=1; i<n; i++){
    total += 2 * Function(a + delta*(i)); // All inner calls -- multiply each call by 2
  }
  total += Function(b); // Last call to the function
  total = (total * (delta/2)); // Multiply running total by delta / 2, then reassign
  return total;
}

// Method that performs numerical intergration by Simpson's Rule
//     a and b are the start and end of the interval
//     n is the number of bins to be used -- directly tied to accuracy -- must be even for Simpson's
//     function Function() is passed as an argument
double SimpsonInteg(double a, double b, int n, std::function<double(double x)> Function){
  if(n%2 != 0){ // Check if n is odd
    std::cout << "Bins must be even to use Simpson's Rule!" << std::endl;
    return -1; // If odd, return -1
  }
  double delta = (b-a)/n; // Width of each trapeziod
  double total = Function(a); // First call to function
  for(int i=1; i<n; i++){
    if(i%2 == 0){ // Even calls are multiplied by 2
      total += 2 * Function(a + delta*(i));
    } else{ // Odd calls are multiplied by 4
      total += 4 * Function(a + delta*(i));
    }
  }
  total += Function(b); // Last call to the function
  total = (total * (delta/3)); // Multiply running total by delta / 3, then reassign
  return total;
}

int main(){
  coeff = {1,0,1}; // Store the function x^2 + 1 into the global vector
  PrintFunction(); // Display the function to the screen
  double result = TrapezoidInteg(1,5,4,Function); // Compute by the trapeziod rule
  std::cout << "Result of trapezoid rule: " << result << std::endl;
  result = SimpsonInteg(1,5,4,Function); // Compute by Simpson's Rule
  std::cout << "Result of Simpson's Rule: " << result << std::endl;

  return 0;
}
