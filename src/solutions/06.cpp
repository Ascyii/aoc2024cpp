// Parse to vec<string>
// Find the start [sy, sx]
// R X C; [y, x] Start at 0
//
// < size() for checking if out of bounds
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
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
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

// This needs to be changed to ../
// #include "helpers.h"

// Setting the constants
const std::string DAYNUMBER = "06";
const bool DEBUG = true;

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
using vint = std::vector<int>;         // int array
using vstr = std::vector<std::string>; // int array
using pos = std::array<int, 2>;        // int array
using str = std::string;

// Defining enums
enum orientation {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

void rotate(orientation &o) {
  if (o == UP) {
    o = RIGHT;
  } else if (o == DOWN) {
    o = LEFT;
  } else if (o == RIGHT) {
    o = DOWN;
  } else {
    o = UP;
  }
}

void step(pos &p, orientation o) {
  if (o == UP) {
    p[0]--;
  } else if (o == DOWN) {
    p[0]++;
  } else if (o == RIGHT) {
    p[1]++;
  } else {
    p[1]--;
  }
}

bool obstacle(pos &p, orientation o, vstr &g) {
  if (o == UP) {
    return g[p[0] - 1][p[1]] == '#';
  } else if (o == DOWN) {
    return g[p[0] + 1][p[1]] == '#';
  } else if (o == RIGHT) {
    return g[p[0]][p[1] + 1] == '#';
  } else {
    return g[p[0]][p[1] - 1] == '#';
  }
}

bool hittank(pos &p, orientation o, pos t) {
  if (o == UP) {
    return p[0] - 1 == t[0] && p[1] == t[1];
  } else if (o == DOWN) {
    return p[0] + 1 == t[0] && p[1] == t[1];
  } else if (o == RIGHT) {
    return p[0] == t[0] && p[1] + 1 == t[1];
  } else {
    return p[0] == t[0] && p[1] - 1 == t[1];
  }
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

  // Container for rows
  vstr rows;

  std::set<pos> trace;

  // Read input and populate lists
  while (std::getline(inputFile, line)) {
    // Push back while wrapping in 'X'
    rows.push_back('X' + line + 'X');
  }

  // Wrap the input
  str deckel(rows[0].size(), 'X');
  rows.insert(rows.begin(), deckel);
  rows.push_back(deckel);

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here

  // Current position
  pos cpos;
  pos spos;
  orientation o(UP);

  // Find the start
  int rowi = 0;
  for (str row : rows) {
    dbg(row);
    int coli = 0;
    for (char chr : row) {
      if (chr == '^') {
        cpos = {rowi, coli};
        spos = cpos;
      }
      coli++;
    }
    rowi++;
  }

  // Part 1

  while (rows[cpos[0]][cpos[1]] != 'X') {
    // Insert the starting pos

    // Check for obstacle
    if (obstacle(cpos, o, rows)) {
      rotate(o);
    } else {
      trace.insert(cpos);
      step(cpos, o);
    }
  }

  res1 = std::distance(trace.begin(), trace.end());

  // Part 2: Calculate positions that cause the guard to get stuck in a loop

  // Iterate over all positions in the trace to test possible obstacle
  // placements
  for (const pos &tank : trace) {
    // Skip the starting position
    if (tank == spos) {
      continue;
    }

    // Simulate guard's patrol with the obstacle at `tank`
    pos cpos2 = spos;
    orientation o2 = UP;
    std::set<pos> visited_positions;

    bool loop_detected = false;

    while (rows[cpos2[0]][cpos2[1]] != 'X') {
      // Mark the current position as visited

      // Check for obstacle or if guard hits the proposed tank
      if (obstacle(cpos2, o2, rows) || hittank(cpos2, o2, tank)) {
        rotate(o2); // Rotate if blocked
      } else {
        step(cpos2, o2); // Otherwise, move forward
        if (cpos2 == spos) {
          loop_detected = true;
          break;
        }
      }

      // Check if we've returned to a previously visited position
    }

    // If a loop is detected, count this tank position as valid
    if (loop_detected) {
      res2++;
    }
  }
  dbg(res2);

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  int first = res1 | 000;
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
