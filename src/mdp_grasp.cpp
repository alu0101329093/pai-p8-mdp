#include "mdp/mdp_grasp.h"

namespace daa {

MdpSolution MdpGrasp::Solve(const MdpProblem& problem,
                            const std::unique_ptr<MdpOptions>& options) {
  float best_solution_diversity{0};
  MdpSolution best_solution{};
  std::size_t unchanged_iterations{};

  MdpGraspOptions* parsed_options =
      reinterpret_cast<MdpGraspOptions*>(options.get());
  std::size_t iterations{parsed_options->GetIterations()};
  std::size_t max_unchanged_iterations =
      parsed_options->GetMaxUnchangedIterations();
  std::srand(std::time(nullptr));

  for (std::size_t i = 0;
       i < iterations && unchanged_iterations < max_unchanged_iterations; ++i) {
    MdpGrasp::ConstructionSolution construction_solution{
        ConstructionPhase(problem, parsed_options)};

    MdpSolution solution{PostProcessing(construction_solution.solution,
                                        parsed_options,
                                        construction_solution.unused_elements)};
    float solution_diversity{solution.GetDiversity()};

    if (solution_diversity > best_solution_diversity) {
      best_solution.SetElementsSet(solution.GetElementsSet());
      best_solution.SetElementsAmount(solution.GetElementsAmount());
      best_solution_diversity = solution_diversity;
      unchanged_iterations = 0;
    } else {
      ++unchanged_iterations;
    }
  }

  return best_solution;
}

MdpGrasp::ConstructionSolution MdpGrasp::ConstructionPhase(
    const MdpProblem& problem, MdpGraspOptions* options) const {
  std::size_t random_solutions_amount = options->GetRandomSolutionsAmount();
  ElementsSet lrc_elements{GenerateLRC(problem, random_solutions_amount)};
  MdpSolution partial_solution{{GetRandomElement(lrc_elements)}, 1};
  return SolvePartialSolution(problem, partial_solution, options);
}

ElementsSet MdpGrasp::GenerateLRC(const MdpProblem& problem,
                                  std::size_t random_solutions_amount) const {
  ElementsSet elements{problem.GetElementsSet()};
  ElementsSet lrc_elements{};

  for (std::size_t i = 0; i < random_solutions_amount; ++i) {
    std::vector<float> center{GetCenter(elements)};
    std::vector<float> most_away_element{GetMostAwayElement(center, elements)};
    lrc_elements.insert(elements.extract(most_away_element));
  }

  return lrc_elements;
}

std::vector<float> MdpGrasp::GetRandomElement(
    const ElementsSet& elements_set) const {
  auto iterator{elements_set.cbegin()};
  std::size_t random_amount{std::rand() % elements_set.size()};
  std::advance(iterator, random_amount);
  return *iterator;
}

/**
 * @brief Get the center of a set of elements
 *
 * @param elements_set
 * @return std::vector<float>
 */
std::vector<float> MdpGrasp::GetCenter(const ElementsSet& elements_set) const {
  std::vector<float> center_dimensions{0, 0, 0};

  for (const auto& element : elements_set) {
    for (std::size_t i = 0; i < element.size(); ++i) {
      center_dimensions[i] += element[i];
    }
  }
  for (auto& dimension : center_dimensions) {
    dimension /= elements_set.size();
  }

  return center_dimensions;
}

/**
 * @brief Get the distance between two elements
 *
 * @param first_element
 * @param second_element
 * @return float
 */
float MdpGrasp::GetDistance(const std::vector<float>& first_element,
                            const std::vector<float>& second_element) const {
  float squared_distance{};
  for (std::size_t i = 0; i < first_element.size(); ++i) {
    squared_distance += (first_element[i] - second_element[i]) *
                        (first_element[i] - second_element[i]);
  }
  return std::sqrt(squared_distance);
}

/**
 * @brief Get the most away element in a set of elements
 *
 * @param center
 * @param elements_set
 * @return std::vector<float>
 */
std::vector<float> MdpGrasp::GetMostAwayElement(
    const std::vector<float>& center, const ElementsSet& elements_set) const {
  std::vector<float> most_away_element{};
  float best_distance{};

  for (const auto& element : elements_set) {
    float new_distance{GetDistance(center, element)};
    if (new_distance > best_distance) {
      best_distance = new_distance;
      most_away_element = element;
    }
  }

  return most_away_element;
}

/**
 * @brief Solve problem with a initial partial solution
 *
 * @param problem
 * @param partial_solution
 * @return MdpSolution
 */
MdpGrasp::ConstructionSolution MdpGrasp::SolvePartialSolution(
    const MdpProblem& problem, const MdpSolution& partial_solution,
    MdpGraspOptions* options) const {
  ElementsSet current_elements = problem.GetElementsSet();
  ElementsSet solution_elements{partial_solution.GetElementsSet()};
  for (const auto& element : solution_elements) {
    current_elements.erase(element);
  }

  std::vector<float> center{GetCenter(current_elements)};
  std::size_t subset_max_elements = std::min(options->GetSubsetMaxElements(),
                                             problem.GetElementsAmount() - 1);

  while (solution_elements.size() < subset_max_elements) {
    std::vector<float> most_away_element{
        GetMostAwayElement(center, current_elements)};
    solution_elements.insert(most_away_element);
    current_elements.erase(most_away_element);
    center = GetCenter(solution_elements);
  }

  MdpSolution solution{solution_elements, subset_max_elements};
  // if (options->GetLocalSearch())
  //   return options->GetLocalSearch()->Execute(solution, current_elements);
  return {solution, current_elements};
}

MdpSolution MdpGrasp::PostProcessing(const MdpSolution& solution,
                                     MdpGraspOptions* options,
                                     const ElementsSet& unused_elements) const {
  return options->GetLocalSearch()->Execute(solution, unused_elements);
}

}  // namespace daa
