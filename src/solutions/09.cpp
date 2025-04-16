// Include the libs (essesntials)
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// Maybe used
// Dont care here when they are not used
#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

// This needs to be changed to ../
// #include "helpers.h"

// Setting the constants
const std::string DAYNUMBER = "09";
const bool DEBUG = false;

// Some Macros
#define dbg(expr)                                                              \
  (DEBUG ? (std::cerr << "[DBG] " << __FILE__ << ":" << __LINE__ << " ("       \
                      << #expr << ") = " << (expr) << "\n",                    \
            (expr))                                                            \
         : (expr))

// Defining structures
struct Struktur {};

// Defining classes
class Klasse;

// Defining types
using inta = std::vector<int>; // int array

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

  long long res1 = 0; // Start at 0
  int res2 = 0;

  std::vector<int> disk;

  int id = 0;
  bool free = false;
  // Read input and populate lists
  while (std::getline(inputFile, line)) {
    for (char c : line) {
      // Get the number
      int n = (int)c - 48;

      // Iterate over the input
      if (free) {
        for (int i = 0; i < n; i++) {
          // -1 represents the dot here
          disk.push_back(-1);
        }
        // Increment id
      } else {
        // Push_back with id
        for (int i = 0; i < n; i++) {
          disk.push_back(id);
        }
        id++;
      }
      // Change the input type
      free = !free;
    }
  }

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here

  bool found = 1;
  while (found) {
    // Get the last element
    int n = disk[disk.size() - 1];

    // Find the first free space
    found = false;
    for (int i = 0; i < disk.size(); i++) {
      if (disk[i] == -1) {
        // Sway the elemnents
        disk[i] = n;
        disk.pop_back();

        // Break
        found = true;
        break;
      }
    }
  }

  for (long long i = 0; i < disk.size(); i++) {
    res1 += i * disk[i];
  }

  dbg(res1);

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  long long first = res1 | 000;
  ///////////////
  int second = res2 | 000;
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
