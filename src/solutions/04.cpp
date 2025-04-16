#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

const int daynumber = 4;
const bool debug = 0;

const std::regex horizontal_regex("(?=(XMAS|SAMX))");
const std::regex mas_regex("(?=(MAS|SAM))");

#define dbg(expr)                                                              \
  (debug ? (std::cerr << "[dbg] " << __LINE__ << " (" << #expr                 \
                      << ") = " << (expr) << "\n",                             \
            (expr))                                                            \
         : (expr))

using smat = std::vector<std::string>;
using arr2 = std::array<int, 2>;

// Check if a substring matches "MAS" or "SAM"
int is_mas(const std::string &mas) { return (mas == "MAS" || mas == "SAM"); }

// Check for the "X-MAS" pattern at grid[row][col]
int check_xmas(const std::vector<std::string> &grid, int row, int col) {
  int n = grid.size();
  int m = grid[0].size();

  if (row < 1 || row >= n - 1 || col < 1 || col >= m - 1)
    return 0; // Out of bounds for the "X" pattern

  std::string mas1 = {grid[row - 1][col - 1], grid[row][col],
                      grid[row + 1][col + 1]};
  std::string mas2 = {grid[row - 1][col + 1], grid[row][col],
                      grid[row + 1][col - 1]};

  return is_mas(mas1) && is_mas(mas2);
}

int count_matches(const smat &rows, const std::regex &re) {
  int count = 0;
  for (const auto &row : rows)
    count += std::distance(std::sregex_iterator(row.begin(), row.end(), re),
                           std::sregex_iterator());
  return count;
}

smat rotate90(const smat &rows) {
  smat rotated(rows[0].size());
  for (const auto &row : rows)
    for (size_t i = 0; i < row.size(); ++i)
      rotated[i] += row[i];
  return rotated;
}

smat diagonalize(const smat &rows, bool reverse) {
  smat result(rows[0].size() + rows.size() - 1);
  for (size_t r = 0; r < rows.size(); ++r)
    for (size_t c = 0; c < rows[0].size(); ++c)
      result[reverse ? r + c : rows[0].size() - c - 1 + r] += rows[r][c];
  return result;
}

int main(int argc, char *argv[]) {
  bool second_part = (argc > 1);
  std::ifstream inputfile(
      debug ? "src/examples/0" + std::to_string(daynumber) + ".ex"
            : "src/inputs/0" + std::to_string(daynumber) + ".in");
  if (!inputfile)
    return 1;

  smat rows;
  for (std::string line; std::getline(inputfile, line);)
    rows.push_back(line);

  int count1 = count_matches(rows, horizontal_regex) +
               count_matches(rotate90(rows), horizontal_regex) +
               count_matches(diagonalize(rows, false), horizontal_regex) +
               count_matches(diagonalize(rows, true), horizontal_regex);

  dbg(count1);
  if (!second_part) {
    if (!debug)
      std::cout << count1 << "\n";
    return 0;
  }

  int count2 = 0;

  // Iterate through the grid to count "X-MAS" patterns
  for (int i = 0; i < rows.size(); i++) {
    for (int j = 0; j < rows[i].size(); j++) {
      count2 += check_xmas(rows, i, j);
    }
  }

  dbg(count2);
  if (!debug)
    std::cout << count2 << std::endl;

  return 0;
}

////// include the libs (essesntials)
// #include <array>
// #include <cstdio>
// #include <cstring>
// #include <fstream>
// #include <iostream>
// #include <iterator>
// #include <ostream>
// #include <regex>
// #include <string>
//
//// maybe used
//// dont care here when they are not used
// #include <algorithm>
// #include <cstddef>
// #include <sstream>
// #include <unordered_map>
// #include <vector>
//
//// setting the constants
// const int daynumber = 4;
// const bool debug = 1;
//
//// defining the regex
// const std::regex horizontal_regex("(?=(xmas|samx))");
// const std::regex mas_regex("(?=(mas|sam))");
//
// #d efine d bg( expr) \
//  (debug ? (std::cerr << "[dbg] " << __line__ << " (" << #expr \
//                      << ") = " << (expr) << "\n", \
//            (expr)) \
//         : (expr))
//
//// check occurences of xmas
// int occ_mas(std::vector<std::string> rows) {
//   int count = 0;
//   /// algorithms go here
//   for (std::string row : rows) {
//     // getting the horizontal words
//     auto words_begin =
//         std::sregex_iterator(row.begin(), row.end(), horizontal_regex);
//     auto words_end = std::sregex_iterator();
//     count += std::distance(words_begin, words_end);
//   }
//   return count;
// }
//
//// rotate the matrix
// std::vector<std::string> rotate90(std::vector<std::string> rows) {
//   std::vector<std::string> rot_rows(rows[0].length());
//   {
//     for (std::string row : rows) {
//       // getting the horizontal words
//       size_t index = 0;
//       for (char c : row) {
//         rot_rows[index] += c;
//         ++index;
//       };
//     }
//   }
//   return rot_rows;
// }
//
//// diagonalize the matrix
// std::vector<std::string> diag(std::vector<std::string> rows, bool rev) {
//   std::vector<std::string> dia_rows(rows[0].length() + (rows.size() - 1));
//   int rowi = 0;
//   for (std::string row : rows) {
//     int coli = 0;
//     for (char c : row) {
//       // here you have a loop over every char!
//       if (rev) {
//         dia_rows[rowi + coli] += c;
//         coli++;
//         continue;
//       }
//       dia_rows[rows[0].length() - coli - 1 + rowi] += c;
//       coli++;
//     }
//     rowi++;
//   }
//   return dia_rows;
// }
//
//// types
// using smat = std::vector<std::string>;
// using arr2 = std::array<int, 2>;
//
//// helpers
// void print_mat(smat mat) {
//   std::cout << "printing mat:\n";
//   for (std::string row : mat) {
//     std::cout << row << std::endl;
//   }
// }
//
// int main(int argc, char *argv[]) {
//   bool second_part;
//   if (argc > 1) { // going to the part two when provided arguments
//     second_part = true;
//   }
//   std::string file;
//   if (debug) {
//     file = "examples/" + std::to_string(daynumber) + ".ex";
//   } else {
//     file = "inputs/" + std::to_string(daynumber) + ".in";
//   }
//   std::ifstream inputfile(file); // replace "data.txt" with your file name
//   // return when not found
//   if (!inputfile) {
//     return 1;
//   }
//
//   ///////////////////////////////////////////////
//   /// get the data /////////////////////////////
//   /////////////////////////////////////////////
//
//   std::string line;
//   std::vector<std::string> rows;
//   while (std::getline(inputfile, line)) {
//     rows.push_back(line);
//   }
//   inputfile.close();
//
//   ////////////////////////////////////////
//   // evaluate the collected data /////////
//   ////////////////////////////////////////
//
//   // part 1
//
//   int count1 = 0;
//
//   // get normals
//   count1 += occ_mas(rows);
//
//   // get the rotated
//   count1 += occ_mas(rotate90(rows));
//
//   // get the diagonals
//   count1 += occ_mas(diag(rows, false));
//   count1 += occ_mas(diag(rows, true));
//
//   // part 2
//
//   int count2 = 0;
//
//   // here we only need the diagonal matrixes
//   smat diagr = diag(rows, true);
//   smat diagl = diag(rows, false);
//
//   print_mat(diagr);
//   print_mat(diagl);
//
//   std::vector<std::array<int, 2>> rstarts;
//   std::vector<std::array<int, 2>> lstarts;
//
//   int matnum = 0; // 0 for right 1 for left
//   for (smat diagmm : {diagr, diagl}) {
//     int rowi = 0;
//     for (std::string row : diagmm) {
//       // reversing helps??
//       // std::reverse(row.begin(), row.end());
//
//       auto begin = std::sregex_iterator(row.begin(), row.end(), mas_regex);
//       auto end = std::sregex_iterator();
//
//       // loop through all matches
//       for (auto it = begin; it != end; ++it) {
//         // get the match
//         std::smatch match = *it;
//
//         // get the beginning pos in diagonal format (need to convert back to
//         // kart)
//         int position =
//             match.position(0); // get the position of the current match
//         //
//         //
//         std::cout << row << std::endl;
//
//         // calculate the column here (very bad)
//         if (matnum == 0) {
//           rstarts.push_back(arr2{position, rowi});
//         } else {
//           lstarts.push_back(arr2{position, rowi});
//         }
//       }
//       // going to the next row(of translated one)
//       rowi++;
//     }
//     // traversing the other matrix
//     matnum++;
//   }
//
//   // here is the logic for finding crosses from starts
//   // hit is c, r (c, y)
//   for (arr2 hit : rstarts) {
//     for (arr2 cmp : lstarts) {
//       if (hit[1] - 1 == cmp[1] && cmp[0] == hit[0] - 1)
//         count2++;
//     }
//   }
//
//   dbg(count2);
//
//   ///////////////////////////////////////
//   /// output results ///////////////////
//   /////////////////////////////////////
//
//   if (debug == false) {
//     if (second_part == true) {
//       std::cout << count2;
//     } else {
//       std::cout << count1;
//     }
//   }
//
//   return 0;
// }
