#include "mdp/mdp_greedy.h"

#include <iostream>

namespace daa {

MdpGreedy::MdpGreedy() {}

MdpSolution MdpGreedy::Solve(const MdpProblem& problem,
                             std::size_t subset_max_elements) {
  ElementsSet current_elements = problem.GetElementsSet();
  ElementsSet solution_set{};
  std::vector<float> center{GetCenter(current_elements)};

  while (solution_set.size() < subset_max_elements) {
    std::vector<float> most_away_element{
        GetMostAwayElement(center, current_elements)};
    solution_set.insert(most_away_element);
    current_elements.erase(most_away_element);
    center = GetCenter(current_elements);
  }

  return MdpSolution{solution_set, subset_max_elements};
}

std::vector<float> MdpGreedy::GetCenter(const ElementsSet& elements_set) const {
  std::vector<float> center_dimensions{0, 0, 0};

  for (const auto& element : elements_set) {
    for (std::size_t i = 0; i < element.size(); ++i) {
      center_dimensions[i] += element[i];
    }
  }
  std::cout << center_dimensions[0] << std::endl;
  for (auto dimension : center_dimensions) {
    dimension /= elements_set.size();
  }
  std::cout << center_dimensions[0] << std::endl;

  return center_dimensions;
}

std::size_t MdpGreedy::GetDistance(
    const std::vector<float>& first_element,
    const std::vector<float>& second_element) const {
  std::size_t squared_distance{};
  for (std::size_t i = 0; i < first_element.size(); ++i) {
    squared_distance += (first_element[i] - second_element[i]) *
                        (first_element[i] - second_element[i]);
  }
  return std::sqrt(squared_distance);
}

const std::vector<float>& MdpGreedy::GetMostAwayElement(
    const std::vector<float>& center, const ElementsSet& elements_set) const {
  std::vector<float> most_away_element{0, 0, 0};
  std::size_t best_distance{};

  for (const auto& element : elements_set) {
    std::size_t new_distance{GetDistance(center, element)};
    if (new_distance > best_distance) {
      best_distance = new_distance;
      most_away_element = element;
    }
  }

  return most_away_element;
}

}  // namespace daa
