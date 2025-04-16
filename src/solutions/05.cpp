// Include the libs (essesntials)
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

// Maybe used
// Dont care here when they are not used
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <unordered_map>
#include <vector>

// Setting the constants
const int DAYNUMBER = 5;
const bool DEBUG = 0;

// Some Macros
#define DBG(expr)                                                              \
  (DEBUG ? (std::cerr << "[DBG] " << __FILE__ << ":" << __LINE__ << " ("       \
                      << #expr << ") = " << (expr) << "\n",                    \
            (expr))                                                            \
         : (expr))

// Defining structures
struct Struktur {};

struct rule {
  int first;
  int second;

  rule(const std::string &str) {
    auto separator_pos = str.find('|');
    if (separator_pos == std::string::npos) {
      throw std::invalid_argument("Invalid format: Missing '|' separator");
    }
    try {
      first = std::stoi(str.substr(0, separator_pos));
      second = std::stoi(str.substr(separator_pos + 1));
    } catch (const std::exception &e) {
      throw std::invalid_argument("Invalid format: Non-integer values");
    }
  }

  // Overload << operator for printing
  friend std::ostream &operator<<(std::ostream &os, const rule &obj) {
    os << "first: " << obj.first << ", second: " << obj.second;
    return os;
  }

  void print() const {
    std::cout << "first: " << first << ", second: " << second << std::endl;
  }
};

struct instruction {
  std::vector<int> jobs;

  // Constructor: Parse a comma-separated string into the jobs vector
  instruction(const std::string &str) {
    std::istringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ',')) {
      try {
        jobs.push_back(std::stoi(token));
      } catch (const std::exception &e) {
        throw std::invalid_argument("Invalid input format for instruction: " +
                                    str);
      }
    }
  }

  // Overload << operator for printing
  friend std::ostream &operator<<(std::ostream &os, const instruction &obj) {
    os << "Jobs: [";
    for (size_t i = 0; i < obj.jobs.size(); ++i) {
      os << obj.jobs[i];
      if (i != obj.jobs.size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    return os;
  }

  // Print method (optional, but << is usually preferred)
  void print() const {
    std::cout << *this << '\n'; // Reuse the << operator
  }
};

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
    file = "src/examples/0" + std::to_string(DAYNUMBER) + ".ex";
  } else {
    file = "src/inputs/0" + std::to_string(DAYNUMBER) + ".in";
  }

  std::ifstream inputFile(file); // Replace "data.txt" with your file name
  // Return when not found
  if (!inputFile) {
    return 1;
  }

  ///////////////////////////////////////////////
  /// Get the data /////////////////////////////
  /////////////////////////////////////////////

  // Define the datastructures
  std::string line;

  // Here are the rules and instructions stored
  std::vector<rule> rules;
  std::vector<instruction> instructions;

  // Here for every job there is a list mapped that contains all jobs that
  // should be higher than this one
  std::map<int, std::vector<int>> highers;

  // Read input and populate lists
  int section = 0;
  while (std::getline(inputFile, line, '\n')) {
    if (line.empty()) { // A blank line switches the section
      section++;
    } else {
      if (section == 0) {
        rules.push_back(line);
      } else {
        instructions.push_back(line);
      }
    }
  }

  // Populate the higher list
  for (rule rule : rules) {
    highers[rule.first].push_back(rule.second);
  }

  // Closing the file (all the information is in cpp data structures now)
  inputFile.close();

  ////////////////////////////////////////
  // Evaluate the collected data /////////
  ////////////////////////////////////////

  /// Algorithms go here

  // Store the mid values
  std::vector<int> middles;

  // Store the wrong instructions for part 2
  std::vector<instruction> wrongs;

  // Part 1

  for (instruction instr_set : instructions) {
    // get the jobs
    std::vector<int> jobs = instr_set.jobs;

    // Not failed by default
    bool failed = false;

    // Iterating over the jobs in order
    int job_num = 0;
    for (int job : jobs) {
      if (job_num == 0) {
      } else {
        int prev = instr_set.jobs[job_num - 1];
        for (rule rule : rules) {
          if (rule.first == job && rule.second == prev) {
            // The Instrucdtion is wrong
            failed = true;
          }
        }
      }
      job_num++;
    }

    // Passed all rules
    if (!failed) {
      middles.push_back(instr_set.jobs[jobs.size() / 2]);
    } else {
      // Push back the wrong for second part
      wrongs.push_back(instr_set);
    }
  }

  // Summing the middle values
  int count = 0;
  for (int mid : middles) {
    count += mid;
  }

  // Part 2

  int count2 = 0;

  // Sort the wrongs
  for (instruction &wrong_set : wrongs) {
    std::vector<int> &jobs = wrong_set.jobs;
    std::sort(jobs.begin(), jobs.end(), [&](int a, int b) {
      return std::count(highers[a].begin(), highers[a].end(), b) == 0;
    });
    count2 += jobs[jobs.size() / 2];
  }

  DBG(count2);

  ///////////////////////////////////////
  /// Output results ///////////////////
  /////////////////////////////////////

  // First result
  int first = count;
  ///////////////
  int second = count2;
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
