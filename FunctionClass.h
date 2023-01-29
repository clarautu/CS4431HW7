// Function - header file
// Autumn Clark
// Custom class for containing and evaluating a specified linear function
//     The function is specified by its coeffecients -- see below for additional details
//     Implementation is simple, so source and header files are the same

#include <vector>
#include <iostream>

class Function {
private:
  std::vector<double> coeff; // Vector of doubles to hold the function's coeffecients
  //     The format of coeff should be ascending order, with the first value being x^0
  //     DON'T SKIP ZERO COEFFECIENTS!
  //     i.e. x^2 + 2 would be stored as <2,0,1>
  //     i.e. 9x^3 + 6x^2 would be stored as <0,0,6,9>

  // Private method that evaluates a specified x at the specified power
  double XToThePower(double const x, int power){
    double total = x; // Have total start at x's value
    while(power>1){ // While the power is above 1 -- starts multipling at x^2
      total *= x; // Times total by the original x
      power--; // Decrement power
    }
    return total; // Return total
  }

public:
  // Constructor
  Function(std::vector<double> coeffecients) : coeff(coeffecients){}

  // Method that evaluates the specified x in the current function
  double EvaluateAt(double const x) {
    double total = coeff.at(0); // Double to hold the total value -- start at value of first coeffecient (x^0)
    for(int i=1; i<coeff.size(); i++){ // Loop through coeff -- don't do the first entry (x^0)
      double temp = XToThePower(x, i); // Evaluate x at the correct power -- store in temp
      total += (temp*coeff.at(i)); // Multiply temp and the current position's coeffecient, then add to total
    }
    return total; // Return the total
  }

  // Setter that allows the function to be changed via altering the coeffecients
  void SetCoeff(std::vector<double> c) {
    coeff = c;
  }

  // Method that prints the function
  void PrintFunction() {
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

};
