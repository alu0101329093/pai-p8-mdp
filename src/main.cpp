#include "main.h"

int main(int argc, char* argv[]) {
  std::cout << "Greedy\n";
  daa::ShowGreedyOutput(argv[1]);
  std::cout << "Greedy Exchange\n";
  daa::ShowGreedyExchangeOutput(argv[1]);
  std::cout << "Grasp\n";
  daa::ShowGraspOutput(argv[1]);
  std::cout << "BB Less Greedy\n";
  daa::ShowBBLessGreedyOutput(argv[1]);
  // std::cout << "BB Less Grasp\n";
  // daa::ShowBBLessGraspOutput(argv[1]);
  std::cout << "BB Deep Greedy\n";
  daa::ShowBBDeepGreedyOutput(argv[1]);
  // std::cout << "BB Deep Grasp\n";
  // daa::ShowBBDeepGraspOutput(argv[1]);
  // daa::MdpProblem
  // problem{daa::ReadInfoFromFile("examples/max_div_15_2.txt")};

  // daa::MdpSolver solver{};
  // solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGreedy);
  // auto greedy_start_time = std::chrono::steady_clock::now();
  // daa::MdpSolution greedy_solution{
  //     solver.Solve(problem, std::make_unique<daa::MdpOptions>(5, nullptr))};
  // auto greedy_actual_time = std::chrono::steady_clock::now();
  // auto greedy_execution_time =
  //     std::chrono::duration_cast<std::chrono::milliseconds>(greedy_actual_time
  //     -
  //                                                           greedy_start_time);
  // std::cout << "Without Exchange:\n" << greedy_solution;
  // std::cout << greedy_execution_time.count() << "ms\n\n";

  // greedy_start_time = std::chrono::steady_clock::now();
  // daa::MdpSolution greedy_solution_exchange{solver.Solve(
  //     problem, std::make_unique<daa::MdpOptions>(5, new daa::MdpExchange))};
  // greedy_actual_time = std::chrono::steady_clock::now();
  // greedy_execution_time =
  // std::chrono::duration_cast<std::chrono::milliseconds>(
  //     greedy_actual_time - greedy_start_time);
  // std::cout << "With Exchange:\n" << greedy_solution_exchange;
  // std::cout << greedy_execution_time.count() << "ms\n\n";

  // solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGrasp);
  // auto grasp_start_time = std::chrono::steady_clock::now();
  // daa::MdpSolution grasp_solution_exchange{
  //     solver.Solve(problem, std::make_unique<daa::MdpGraspOptions>(
  //                               5, new daa::MdpExchange, 1000, 5, 100))};
  // auto grasp_actual_time = std::chrono::steady_clock::now();
  // auto grasp_execution_time =
  //     std::chrono::duration_cast<std::chrono::milliseconds>(grasp_actual_time
  //     -
  //                                                           grasp_start_time);
  // std::cout << "Grasp With Exchange:\n" << grasp_solution_exchange;
  // std::cout << grasp_execution_time.count() << "ms\n";

  // solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kBranchBound);
  // auto bb_start_time = std::chrono::steady_clock::now();
  // daa::MdpSolution bb_solution_exchange{solver.Solve(
  //     problem, std::make_unique<daa::MdpBranchBoundOptions>(
  //                  5, new daa::MdpExchange, new daa::MdpGreedy,
  //                  daa::MdpNode::ComparisonType::kLessUpperBound))};
  // auto bb_actual_time = std::chrono::steady_clock::now();
  // auto bb_execution_time =
  //     std::chrono::duration_cast<std::chrono::milliseconds>(bb_actual_time -
  //                                                           bb_start_time);
  // std::cout << "BB With Exchange:\n" << bb_solution_exchange;
  // std::cout << bb_execution_time.count() << "ms\n";

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

void ShowGreedyOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGrasp);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{
          solver.Solve(problem, std::make_unique<daa::MdpOptions>(i, nullptr))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

void ShowGreedyExchangeOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGrasp);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{solver.Solve(
          problem, std::make_unique<daa::MdpOptions>(i, new daa::MdpExchange))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

void ShowGraspOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kGrasp);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{
          solver.Solve(problem, std::make_unique<daa::MdpGraspOptions>(
                                    i, new daa::MdpExchange, 1000, 5, 100))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

void ShowBBLessGreedyOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kBranchBound);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{solver.Solve(
          problem, std::make_unique<daa::MdpBranchBoundOptions>(
                       i, new daa::MdpExchange, new daa::MdpGreedy,
                       daa::MdpNode::ComparisonType::kLessUpperBound))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

void ShowBBLessGraspOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kBranchBound);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{solver.Solve(
          problem, std::make_unique<daa::MdpBranchBoundOptions>(
                       i, new daa::MdpExchange, new daa::MdpGrasp,
                       daa::MdpNode::ComparisonType::kLessUpperBound))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

void ShowBBDeepGreedyOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kBranchBound);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{
          solver.Solve(problem, std::make_unique<daa::MdpBranchBoundOptions>(
                                    i, new daa::MdpExchange, new daa::MdpGreedy,
                                    daa::MdpNode::ComparisonType::kDeeper))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

void ShowBBDeepGraspOutput(const std::string& path) {
  daa::MdpSolver solver{};
  std::cout << "|  FileName |    m    |    Diversity    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    for (std::size_t i = 2; i < 6; ++i) {
      daa::MdpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
      std::cout << "| " << entry.path().string() << " | ";
      solver.SetAlgorithm(daa::MdpSolver::AlgorithmTypes::kBranchBound);
      auto start_time = std::chrono::steady_clock::now();
      std::cout << "| " << i << " | ";
      daa::MdpSolution solution{
          solver.Solve(problem, std::make_unique<daa::MdpBranchBoundOptions>(
                                    i, new daa::MdpExchange, new daa::MdpGrasp,
                                    daa::MdpNode::ComparisonType::kDeeper))};
      auto actual_time = std::chrono::steady_clock::now();
      auto execution_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(actual_time -
                                                                start_time);
      std::cout << "   " << solution.GetDiversity() << "   | ";
      std::cout << "   " << execution_time.count() << "ms   | \n";
    }
  }
}

}  // namespace daa
