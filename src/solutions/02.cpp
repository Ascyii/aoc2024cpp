// Include the libs (essesntials)
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Setting the constants
const std::string DAYNUMBER = "02";
const bool DEBUG = 0;

// Some Macros
#define DBG(expr)                                                              \
  (DEBUG ? (std::cerr << "[DBG] " << __FILE__ << ":" << __LINE__ << " ("       \
                      << #expr << ") = " << (expr) << "\n",                    \
            (expr))                                                            \
         : (expr))

std::vector<int> strToVec(const std::string &input) {
  std::vector<int> result;
  std::stringstream ss(input);
  int num;
  while (ss >> num) {
    result.push_back(num);
  }
  return result;
}

// Helper functions for just this puzzle

bool isValidLevelDifference(const std::vector<int> &vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    int diff = std::abs(vec[i] - vec[i - 1]);
    if (diff < 1 || diff > 3) {
      return false; // Found a difference that is not between 1 and 3
    }
  }
  return true;
}

bool isAscending(const std::vector<int> &vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    if (vec[i] < vec[i - 1]) {
      return false; // Found a pair that breaks the ascending order
    }
  }
  return true;
}

bool isDescending(const std::vector<int> &vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    if (vec[i] > vec[i - 1]) {
      return false; // Found a pair that breaks the descending order
    }
  }
  return true;
}

bool isSafeByRemovingOneLevel(const std::vector<int> &vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    // Remove a level and check if it works
    std::vector<int> modifiedVec = vec;
    modifiedVec.erase(modifiedVec.begin() + i); // Remove one level

    if (isValidLevelDifference(modifiedVec) &&
        (isAscending(modifiedVec) || isDescending(modifiedVec))) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  ///////////////////////////////
  // Preamble //////////////////
  //////////////////////////////

  // Check for part
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

  std::ifstream inputFile(file); // Replace "data.txt" with your file name

  // Getting the stream
  // Return when not found
  if (!inputFile) {
    return 1;
  }

  ///////////////////////////////////////////////
  /// Get the data /////////////////////////////
  /////////////////////////////////////////////

  // Define the datastructures
  std::string line;

  // Count variables for two parts
  int count = 0;
  int count2 = 0;

  // Read input and populate lists
  while (std::getline(inputFile, line)) {
    // Part 1
    std::vector<int> row = strToVec(line);
    if (isValidLevelDifference(row) &&
        (isAscending(row) || isDescending((row)))) {
      count += 1;
      count2 += 1;
      continue;
    }

    // Part 2
    if (isSafeByRemovingOneLevel(row)) {
      count2 += 1;
    }
  }

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here
  /// Dont need anything here

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  int first = count;
  ///////////////
  int second = count2;
  // Second result

  // Print results
  if (!DEBUG) {
    if (second_part == true) {
      std::cout << second;
    } else {
      std::cout << first;
    }
  }

  return 0;
}
