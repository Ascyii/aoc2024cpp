// Include the libs (essesntials)
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>

///////////////// PREAMBLE /////////////////////////////

// Settings
const std::string DAYNUMBER = "00";
const bool DEBUG = true;

// For efficient debugging
#define dbg(expr)                                                              \
  (DEBUG ? (std::cerr << "[DBG] " << __FILE__ << ":" << __LINE__ << " ("       \
                      << #expr << ") = " << (expr) << "\n",                    \
            (expr))                                                            \
         : (expr))

// Strucutres
struct Struktur {};

// Classes
class Klasse;

// New Types
using inta = std::vector<int>; // int array
using str = std::string;       // python like str
using stra = std::vector<str>; // str array

//////////////////////// Main //////////////////////////

int main(int argc, char *argv[]) {
  ///////////////////////////////
  // Preamble for Main //////////
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

  long res1 = 0, res2 = 0; // Starting at 0

  // Read input and populate lists
  while (std::getline(inputFile, line)) {
    // Parsing goes here
  }

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  long first = res1 | 000;
  ///////////////
  long second = res2 | 000;
  // Second result

  // Print results
  if (DEBUG == false) {
    if (second_part == true) {
      std::cout << second;
    } else {
      std::cout << first;
    }
  }

  return 0;
}
