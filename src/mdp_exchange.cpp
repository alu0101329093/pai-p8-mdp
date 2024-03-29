#include "mdp/mdp_exchange.h"

namespace daa {

/**
 * @brief Construct a new Mdp Exchange:: Mdp Exchange object
 */
MdpExchange::MdpExchange() {}

/**
 * @brief Execute the local searchh of exchange
 *
 * @param solution
 * @param unused_elements
 * @return MdpSolution
 */
MdpSolution MdpExchange::Execute(const MdpSolution& solution,
                                 const ElementsSet& unused_elements) {
  float solution_diversity{solution.GetDiversity()};
  auto elements_set{solution.GetElementsSet()};
  float best_diversity{solution_diversity};
  std::vector<float> best_remove{};
  std::vector<float> best_add{};

  for (const auto& element : elements_set) {
    float remove_diversity{
        GetElementRemoveDiversity(element, elements_set, solution_diversity)};
    for (const auto& unused_element : unused_elements) {
      float add_diversity{GetElementAddDiversity(
          unused_element, element, elements_set, remove_diversity)};
      if (add_diversity > best_diversity) {
        best_diversity = add_diversity;
        best_remove = element;
        best_add = unused_element;
      }
    }
  }

  if (best_diversity > solution_diversity) {
    elements_set.erase(best_remove);
    elements_set.insert(best_add);
  }
  return MdpSolution{elements_set, solution.GetElementsAmount()};
}

/**
 * @brief Get the distance between two elements
 *
 * @param first_element
 * @param second_element
 * @return float
 */
float MdpExchange::GetDistance(const std::vector<float>& first_element,
                               const std::vector<float>& second_element) const {
  float squared_distance{};
  for (std::size_t i = 0; i < first_element.size(); ++i) {
    squared_distance += (first_element[i] - second_element[i]) *
                        (first_element[i] - second_element[i]);
  }
  return std::sqrt(squared_distance);
}

/**
 * @brief Get the diversity with the remove of a element
 *
 * @param element_to_remove
 * @param elements_set
 * @param solution_diversity
 * @return float
 */
float MdpExchange::GetElementRemoveDiversity(
    const std::vector<float>& element_to_remove,
    const ElementsSet& elements_set, float solution_diversity) const {
  float remove_diversity{solution_diversity};

  for (const auto& element : elements_set) {
    if (element == element_to_remove) continue;
    remove_diversity -= GetDistance(element_to_remove, element);
  }

  return remove_diversity;
}

/**
 * @brief Get the diversity with the addition of a element
 *
 * @param element_to_add
 * @param removed_element
 * @param elements_set
 * @param remove_diversity
 * @return float
 */
float MdpExchange::GetElementAddDiversity(
    const std::vector<float>& element_to_add,
    const std::vector<float>& removed_element, const ElementsSet& elements_set,
    float remove_diversity) const {
  float add_diversity{remove_diversity};

  for (const auto& element : elements_set) {
    if (element == removed_element) continue;
    add_diversity += GetDistance(element_to_add, element);
  }

  return add_diversity;
}

}  // namespace daa
