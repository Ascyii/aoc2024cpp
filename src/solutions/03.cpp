// Include the libs (essesntials)
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Setting the constants
const int DAYNUMBER = 3;
const bool DEBUG = 0;

#define DBG(expr)                                                              \
  (std::cerr << "[DBG] " << __FILE__ << ":" << __LINE__ << " (" << #expr       \
             << ") = " << (expr) << "\n",                                      \
   (expr))

// Defining structures
struct Struktur {};

int ex2int(char *ex) { return 0; }

int main(int argc, char *argv[]) {
  ///////////////////////////////
  // Preamble //////////////////
  //////////////////////////////

  // Check for part
  bool second_part;
  if (argc > 1) { // Going to the part two when provided arguments
    second_part = true;
  }

  // This messed everything up!!
  std::ifstream inputFile("src/inputs/0" + std::to_string(DAYNUMBER) + ".in");
  // std::ifstream inputFile("examples/" + std::to_string(DAYNUMBER) + ".ex");

  // Return when not found
  if (!inputFile) {
    return 1;
  }

  ///////////////////////////////////////////////
  /// Get the data /////////////////////////////
  /////////////////////////////////////////////

  // Define the datastructures

  // Read to string
  std::stringstream buffer;
  buffer << inputFile.rdbuf(); // Dump the file content into the buffer
  std::string text = buffer.str();

  // Setup for regexing
  std::string line;
  std::regex pattern(R"(do\(\)|don't\(\)|mul\(\s*(\d+)\s*,\s*(\d+)\s*\))");
  std::smatch match;
  std::vector<std::vector<int>> captures;

  auto begin = std::sregex_iterator(text.begin(), text.end(), pattern);
  auto end = std::sregex_iterator();
  bool enabled = true;
  int sum = 0;

  // Iterate through all matches
  for (auto it = begin; it != end; ++it) {
    std::smatch match = *it;
    // Store the captures in a vector
    if (match[0] == "do()") {
      enabled = true;
    } else if (match[0] == "don't()") {
      if (second_part) {
        enabled = false;
      }
    } else if (enabled) {
      int x = std::stoi(match[1]);
      int y = std::stoi(match[2]);
      sum += x * y;
      captures.push_back(
          {std::stoi(match[1].str()), std::stoi(match[2].str())});
    }
  }

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here
  // Part 1
  int res = 0;
  // Print the captured groups
  for (const auto &capture : captures) {
    // Adding to the result
    // May do this with a fold in the future
    res += (capture[0] * capture[1]);
  }

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  int first = res;
  ///////////////
  int second = sum;
  // Second result
  //
  //
  // Print results
  if (second_part == true) {
    std::cout << "Second: " << second << std::endl;
  } else {
    std::cout << "First: " << first << std::endl;
  }

  return 0;
}
