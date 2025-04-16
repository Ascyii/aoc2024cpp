// Include the libs (essesntials)
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// Setting the constants
const std::string DAYNUMBER = "07";
const bool DEBUG = true;

// Some Macros
#define dbg(expr)                                                              \
  (DEBUG ? (std::cerr << "[DBG] " << __FILE__ << ":" << __LINE__ << " ("       \
                      << #expr << ") = " << (expr) << "\n",                    \
            (expr))                                                            \
         : (expr))

// Class to store big ints represented as strings
class BigInt {
private:
  std::string value; // Store the number as a string
  bool isNegative;

  // Helper function to add two positive numbers as strings
  static std::string addStrings(const std::string &num1,
                                const std::string &num2) {
    std::string result;
    int carry = 0, sum = 0;
    int n1 = num1.size(), n2 = num2.size();

    // Perform addition digit by digit
    for (int i = 0; i < std::max(n1, n2) || carry; ++i) {
      int digit1 = (i < n1) ? num1[n1 - i - 1] - '0' : 0;
      int digit2 = (i < n2) ? num2[n2 - i - 1] - '0' : 0;
      sum = digit1 + digit2 + carry;
      result.push_back((sum % 10) + '0');
      carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  // Helper function to multiply two positive numbers as strings
  static std::string multiplyStrings(const std::string &num1,
                                     const std::string &num2) {
    int n1 = num1.size(), n2 = num2.size();
    std::vector<int> product(n1 + n2, 0);

    // Perform multiplication digit by digit
    for (int i = n1 - 1; i >= 0; --i) {
      for (int j = n2 - 1; j >= 0; --j) {
        int mul = (num1[i] - '0') * (num2[j] - '0');
        int sum = product[i + j + 1] + mul;
        product[i + j + 1] = sum % 10;
        product[i + j] += sum / 10;
      }
    }

    // Convert the product vector to a string
    std::string result;
    for (int num : product) {
      if (!result.empty() || num != 0) // Skip leading zeros
        result.push_back(num + '0');
    }
    return result.empty() ? "0" : result;
  }

public:
  // Constructor
  BigInt(const std::string &str = "0") : value(str), isNegative(false) {
    if (str[0] == '-') {
      isNegative = true;
      value = str.substr(1);
    }
  }

  // Addition
  BigInt operator+(const BigInt &other) const {
    return BigInt(addStrings(this->value, other.value));
  }

  // Comparison operators
  bool operator==(const BigInt &other) const {
    return isNegative == other.isNegative && value == other.value;
  }

  // Multiplication
  BigInt operator*(const BigInt &other) const {
    return BigInt(multiplyStrings(this->value, other.value));
  }

  // Function to get the value
  std::string get_value() { return value; }

  // Print the value
  friend std::ostream &operator<<(std::ostream &os, const BigInt &bigint) {
    if (bigint.isNegative)
      os << '-';
    os << bigint.value;
    return os;
  }
};

// Structure to strore and parse equations
struct equation {
  BigInt res;
  std::vector<BigInt> numbers;

  // Constructor
  equation(const std::string &str) {
    // Set the seperator
    auto separator_pos = str.find(':');

    if (separator_pos == std::string::npos) {
      throw std::invalid_argument("Invalid format: Missing ':' separator");
    }
    try {
      // Parse the result
      res = BigInt(str.substr(0, separator_pos));

      // Parse the numbers
      std::stringstream iss(str.substr(separator_pos + 1));
      std::string number;
      while (iss >> number)
        numbers.push_back(BigInt(number));

    } catch (const std::exception &e) {
      throw std::invalid_argument("Invalid format: Non-integer values");
    }
  }
};

// Gnererate a bitmap of combinatinons
std::vector<std::vector<int>> generateCombinations(int n, int m) {
  std::vector<std::vector<int>> combinations;
  int totalCombinations = 1;

  // Calculate m^n combinations
  for (int i = 0; i < n; ++i) {
    totalCombinations *= m;
  }

  for (int i = 0; i < totalCombinations; ++i) {
    std::vector<int> combination;
    int current = i;

    // Generate a combination by extracting each digit in base m
    for (int j = 0; j < n; ++j) {
      combination.push_back(current % m);
      current /= m;
    }

    // Since we're generating from least to most significant digits, reverse the
    // combination
    std::reverse(combination.begin(), combination.end());

    combinations.push_back(combination);
  }

  return combinations;
}

//////////////////////// Main //////////////////////////

int main(int argc, char *argv[]) {
  ///////////////////////////////
  // Preamble //////////////////
  //////////////////////////////

  // Check for part
  // This works by just providing a random argument to the execution
  bool second_part;
  if (argc > 1) { // Going to the part two when provided arguments
    second_part = true;
  }

  std::string file;
  if (DEBUG) {
    file = "src/examples/" + DAYNUMBER + ".ex";
  } else {
    file = "src/inputs/" + DAYNUMBER + ".in";
  }

  std::ifstream inputFile(file);
  // Return when not found
  if (!inputFile) {
    return 1;
  }

  ///////////////////////////////////////////////
  /// Get the data /////////////////////////////
  /////////////////////////////////////////////

  // Define the datastructures
  std::string line;

  BigInt res1; // Start at 0
  BigInt res2;

  // Store the equations
  std::vector<equation> equations;

  // Read input and populate lists
  while (std::getline(inputFile, line)) {
    equations.push_back(equation(line));
  }

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here

  // Part 2

  // Iterate over equations
  for (equation eq : equations) {
    // This is what we need
    BigInt goal = eq.res;
    BigInt result;

    std::vector<std::vector<int>> combinations =
        generateCombinations(eq.numbers.size() - 1, 2);

    // Iterate over possible arrangements of operators
    for (std::vector<int> combination : combinations) {
      // Get the result for this combination
      int i = 0;
      BigInt p = eq.numbers[0];
      for (int op : combination) {
        if (op) {
          p = p + eq.numbers[i + 1];
        } else {
          p = p * eq.numbers[i + 1];
        }
        i++;
      }

      // Check the result
      if (p.get_value() == goal.get_value()) {
        res1 = res1 + goal;
        break;
      }
    }
  }

  // Part2

  // Iterate over equations
  for (equation eq : equations) {
    // This is what we need
    BigInt goal = eq.res;
    BigInt result = BigInt("0");

    std::vector<std::vector<int>> combinations =
        generateCombinations(eq.numbers.size() - 1, 3);

    // Iterate over possible arrangements of operators
    for (std::vector<int> combination : combinations) {
      // Get the result for this combination
      int i = 0;
      BigInt p = eq.numbers[0];
      for (int op : combination) {
        if (op == 0) {
          p = p + eq.numbers[i + 1];
        } else if (op == 1) {
          p = p * eq.numbers[i + 1];
        } else {
          p = BigInt(p.get_value() + eq.numbers[i + 1].get_value());
        }
        i++;
      }

      // Check the result
      if (p == goal) {
        res2 = res2 + goal;
        break;
      }
    }
  }

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  BigInt first = res1;
  ///////////////
  BigInt second = res2;
  // Second result

  // Print results
  std::cout << "First: " << first << std::endl;
  std::cout << "Second: " << second << std::endl;

  return 0;
}
