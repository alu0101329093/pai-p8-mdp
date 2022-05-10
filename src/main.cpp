#include "main.h"

int main(int argc, char* argv[]) {
  daa::MdpProblem problem{daa::ReadInfoFromFile("examples/max_div_15_2.txt")};

  daa::MdpSolver solver{};
  solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGreedy);
  daa::MdpSolution greedy_solution{solver.Solve(problem, 3)};
  std::cout << greedy_solution;

  return EXIT_SUCCESS;
}

namespace daa {

/**
 * @brief Read problem info from a file
 *
 * @param file_name
 * @return MdpProblem
 */
MdpProblem ReadInfoFromFile(const std::string& file_name) {
  std::ifstream input_file{file_name};
  MdpProblem problem{};
  std::size_t elements_amount{};
  std::size_t dimensions_amount{};
  input_file >> elements_amount >> dimensions_amount;
  problem.SetElementsAmount(elements_amount);
  problem.SetDimensionsAmount(dimensions_amount);

  std::stringstream input_stream{};
  input_stream << input_file.rdbuf();
  std::string input_string{input_stream.str()};
  std::replace(input_string.begin(), input_string.end(), ',', '.');
  input_stream.str(input_string);

  ElementsSet elements_set{};
  std::vector<float> dimensions{};
  for (std::size_t i = 0; i < elements_amount; ++i) {
    dimensions.clear();
    for (std::size_t j = 0; j < dimensions_amount; ++j) {
      float dimension{};
      input_stream >> dimension;
      dimensions.push_back(dimension);
    }
    elements_set.insert(dimensions);
  }
  problem.SetElementsSet(elements_set);

  return problem;
}

}  // namespace daa
