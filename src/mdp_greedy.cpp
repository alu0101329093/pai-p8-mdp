#include "mdp/mdp_greedy.h"

namespace daa {

/**
 * @brief Construct a new Mdp Greedy:: Mdp Greedy object
 *
 */
MdpGreedy::MdpGreedy() {}

/**
 * @brief Solve the greedy algorithm
 *
 * @param problem
 * @param subset_max_elements
 * @param local_search
 * @return MdpSolution
 */
MdpSolution MdpGreedy::Solve(const MdpProblem& problem,
                             std::size_t subset_max_elements,
                             MdpLocalSearch* local_search) {
  ElementsSet current_elements = problem.GetElementsSet();
  ElementsSet solution_set{};
  std::vector<float> center{GetCenter(current_elements)};
  std::unique_ptr<MdpLocalSearch> local_search_ptr{local_search};
  subset_max_elements =
      std::min(subset_max_elements, problem.GetElementsAmount() - 1);

  while (solution_set.size() < subset_max_elements) {
    std::vector<float> most_away_element{
        GetMostAwayElement(center, current_elements)};
    solution_set.insert(most_away_element);
    current_elements.erase(most_away_element);
    center = GetCenter(solution_set);
  }

  MdpSolution solution{solution_set, subset_max_elements};
  if (local_search_ptr)
    return local_search_ptr->Execute(solution, current_elements);
  return solution;
}

/**
 * @brief Get the center of a set of elements
 *
 * @param elements_set
 * @return std::vector<float>
 */
std::vector<float> MdpGreedy::GetCenter(const ElementsSet& elements_set) const {
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
float MdpGreedy::GetDistance(const std::vector<float>& first_element,
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
std::vector<float> MdpGreedy::GetMostAwayElement(
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

}  // namespace daa
