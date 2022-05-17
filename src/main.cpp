#include "main.h"

int main(int argc, char* argv[]) {
  daa::MdpProblem problem{daa::ReadInfoFromFile("examples/max_div_15_2.txt")};

  daa::MdpSolver solver{};
  solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGreedy);
  auto greedy_start_time = std::chrono::steady_clock::now();
  daa::MdpSolution greedy_solution{
      solver.Solve(problem, std::make_unique<daa::MdpOptions>(5, nullptr))};
  auto greedy_actual_time = std::chrono::steady_clock::now();
  auto greedy_execution_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(greedy_actual_time -
                                                            greedy_start_time);
  std::cout << "Without Exchange:\n" << greedy_solution;
  std::cout << greedy_execution_time.count() << "ms\n\n";

  greedy_start_time = std::chrono::steady_clock::now();
  daa::MdpSolution greedy_solution_exchange{solver.Solve(
      problem, std::make_unique<daa::MdpOptions>(5, new daa::MdpExchange))};
  greedy_actual_time = std::chrono::steady_clock::now();
  greedy_execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      greedy_actual_time - greedy_start_time);
  std::cout << "With Exchange:\n" << greedy_solution_exchange;
  std::cout << greedy_execution_time.count() << "ms\n";

  solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGrasp);
  auto grasp_start_time = std::chrono::steady_clock::now();
  daa::MdpSolution grasp_solution_exchange{
      solver.Solve(problem, std::make_unique<daa::MdpGraspOptions>(
                                5, new daa::MdpExchange, 1000, 5, 100))};
  auto grasp_actual_time = std::chrono::steady_clock::now();
  auto grasp_execution_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(grasp_actual_time -
                                                            grasp_start_time);
  std::cout << "Grasp With Exchange:\n" << grasp_solution_exchange;
  std::cout << grasp_execution_time.count() << "ms\n";

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
