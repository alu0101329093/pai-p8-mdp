#include "mdp/mdp_solution.h"

namespace daa {

/**
 * @brief Construct a new Mdp Problem:: Mdp Problem object
 *
 * @param elements_set
 * @param elements_amount
 */
MdpSolution::MdpSolution(const ElementsSet& elements_set,
                         std::size_t elements_amount)
    : elements_set_{elements_set}, elements_amount_{elements_amount} {}

float MdpSolution::GetDiversity() const {
  float diversity{};

  auto last_iterator = std::prev(elements_set_.end());
  for (auto i = elements_set_.begin(); i != last_iterator; ++i) {
    for (auto j = std::next(i); j != elements_set_.end(); ++j) {
      diversity += GetDistance(*i, *j);
    }
  }

  return diversity;
}

/**
 * @brief Get the distance between two elements
 *
 * @param first_element
 * @param second_element
 * @return float
 */
float MdpSolution::GetDistance(const std::vector<float>& first_element,
                               const std::vector<float>& second_element) const {
  float squared_distance{};
  for (std::size_t i = 0; i < first_element.size(); ++i) {
    squared_distance += (first_element[i] - second_element[i]) *
                        (first_element[i] - second_element[i]);
  }
  return std::sqrt(squared_distance);
}

}  // namespace daa
