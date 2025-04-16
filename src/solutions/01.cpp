// Include the libs
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
  // Check for part
  bool second_part;
  if (argc > 1) { // Going to the part two when provided arguments
    second_part = true;
  }

  // Reading the input file
  std::ifstream inputFile(
      "src/inputs/01.in"); // Replace "data.txt" with your file name
  if (!inputFile) {
    return 1;
  }

  std::vector<int> leftList, rightList;
  std::string line;

  // Read input and populate lists
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    int left, right;
    if (iss >> left >> right) {
      leftList.push_back(left);
      rightList.push_back(right);
    }
  }

  inputFile.close();

  ////////////////////////////////////////
  ///
  // Evaluate the collected data
  //
  // Count occurrences of each number in the right list
  std::unordered_map<int, int> rightCount;
  for (int num : rightList) {
    rightCount[num]++;
  }

  // Calculate the similarity score
  int similarityScore = 0;
  for (int num : leftList) { // remember this way of iterating with the colon
    similarityScore +=
        num *
        rightCount[num]; // Multiply the number with its frequency in right list
  }

  // Part 1

  // Sort both lists never modify the data!! (Here im too lazy)
  std::sort(leftList.begin(), leftList.end());
  std::sort(rightList.begin(), rightList.end());

  // Calculate total distance Can this be done in just one loop??
  int totalDistance = 0;
  for (size_t i = 0; i < leftList.size(); ++i) {
    totalDistance += std::abs(leftList[i] - rightList[i]);
  }

  // First result
  int first = totalDistance;
  ///////////////
  int second = similarityScore;
  // Second result

  // Output result
  if (second_part == true) {
    // Output for the second part
    std::cout << second;
  } else {
    // Output for the first part
    std::cout << first;
  }

  std::cout << "HELLO";

  // Old code from gpt

  //  // Create some variables
  //  std::vector<std::pair<int, int>>
  //      numbers; // Vector to store the pairs of numbers
  //  std::string line;
  //
  //  // Iterate over the file
  //  while (std::getline(inputFile, line)) {
  //    // Find the position of the delimiter "   "
  //    size_t delimiterPos = line.find("   ");
  //    if (delimiterPos != std::string::npos) {
  //      try {
  //        // Extract the two numbers as substrings
  //        std::string part1 = line.substr(0, delimiterPos);
  //        std::string part2 = line.substr(delimiterPos + 3);
  //
  //        // Convert substrings to integers
  //        int num1 = std::stoi(part1);
  //        int num2 = std::stoi(part2);
  //
  //        // Add the pair to the vector
  //        numbers.emplace_back(num1, num2);
  //      } catch (const std::invalid_argument &e) {
  //        std::cerr << "Error: Invalid number in line \"" << line << "\""
  //                  << std::endl;
  //      }
  //    } else {
  //      std::cerr << "Error: Malformed line \"" << line << "\"" << std::endl;
  //    }
  //  }

  // Close the file
  // inputFile.close();

  // Print the output
  //  std::cout << "Parsed numbers:" << std::endl;
  //  auto minIt = std::min_element(numbers.begin(), numbers.end());
  //  for (const auto &pair : numbers) {
  //
  //    std::cout << pair.first << " " << pair.second << std::endl;
  //  }

  return 0;
}
