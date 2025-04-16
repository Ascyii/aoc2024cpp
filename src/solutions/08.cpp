// Include the libs (essesntials)
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// Maybe used
// Dont care here when they are not used
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

// This needs to be changed to ../
// #include "helpers.h"

// Setting the constants
const std::string DAYNUMBER = "08";
const bool DEBUG = 0;

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
using inta = std::vector<int>;  // int array
using pos = std::array<int, 2>; // int array
//

bool checkbounds(pos p, int row_size, int column_size) {
  return 0 <= p[0] && p[0] < row_size && 0 <= p[1] && p[1] < column_size;
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

  int res1 = 0; // Start at 0
  int res2 = 0;

  // Datastructs for this problem
  std::map<char, std::vector<pos>> antennas;

  int row_size = 0, column_size = 0, ci;

  // Read input and populate lists

  while (std::getline(inputFile, line)) {
    // Populate antennas
    ci = 0;
    for (char c : line) {
      if (c != '.') {
        antennas[c].push_back({row_size, ci});
      }
      ci++;
    }

    // Set the sizes of the map
    if (!column_size)
      column_size = line.length();
    row_size++;
  }
  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here

  // Set of antinodes
  std::set<std::array<int, 2>> antinodes;
  std::set<std::array<int, 2>> add_antinodes;

  // Iterate over the antenna lists
  for (auto const &k : antennas) {
    // Antenna list
    std::vector<pos> p = k.second;

    // Size of the antenna list
    int s = p.size();
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (i != j) {

          // Calculate the antinodes here
          pos d = {p[j][0] - p[i][0], p[j][1] - p[i][1]};
          pos di = {-d[0], -d[1]};

          pos a1 = {p[j][0] + d[0], p[j][1] + d[1]};
          pos a2 = {p[i][0] + di[0], p[i][1] + di[1]};

          if (checkbounds(a1, row_size, column_size))
            antinodes.insert(a1);
          if (checkbounds(a2, row_size, column_size))
            antinodes.insert(a2);

          // Add the additional nodes here

          for (int o : {-1, 1}) {
            pos n;
            while (n[0] < row_size && n[1] < column_size) {
              if (o == 1) {

              } else {
              }
            }
          }
        }
      }
    }
  }

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  int first = antinodes.size() | 000;
  ///////////////
  int second = antinodes.size() + add_antinodes.size() | 000;
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
