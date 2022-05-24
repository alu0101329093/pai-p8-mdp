#include "mdp/mdp_node.h"

namespace daa {

MdpNode::MdpNode(const ElementsSet& element_branch,
                 const std::vector<float>& element, ComparisonType comparison,
                 const ElementsSet& unselected_elements,
                 std::size_t solution_length)
    : branch_{element_branch},
      diversity_{},
      upper_bound_{},
      comparison_{comparison} {
  CalculateDiversity();
  CalculateUpperBound(element, element_branch, unselected_elements,
                      solution_length);
  branch_.insert(element);
  CalculateDiversity();
}

void MdpNode::CalculateDiversity() {
  MdpSolution solution{branch_};
  diversity_ = solution.GetDiversity();
}

void MdpNode::CalculateUpperBound(const std::vector<float>& element,
                                  const ElementsSet& selected_elements,
                                  const ElementsSet& unselected_elements,
                                  std::size_t solution_length) {
  upper_bound_ = diversity_ + CalculateZSel(element, selected_elements) +
                 CalculateZUnsel(element, unselected_elements, solution_length);
}

float MdpNode::CalculateZSel(const std::vector<float>& element,
                             const ElementsSet& selected_elements) {
  float selected_diversity{};
  for (const auto& selected : selected_elements) {
    selected_diversity += CalculateDistance(selected, element);
  }
  return selected_diversity;
}

float MdpNode::CalculateZUnsel(const std::vector<float>& element,
                               const ElementsSet& unselected_elements,
                               std::size_t solution_length) {
  std::priority_queue<float> distances{};

  for (const auto& unselected : unselected_elements) {
    distances.push(CalculateDistance(unselected, element));
  }

  std::size_t size = solution_length - unselected_elements.size() - 1;
  float unselected_diversity{};
  for (std::size_t i = 0; i < size; ++i) {
    unselected_diversity += distances.top();
    distances.pop();
  }
  return unselected_diversity / 2;
}

/**
 * @brief Get the distance between two elements
 *
 * @param first_element
 * @param second_element
 * @return float
 */
float MdpNode::CalculateDistance(
    const std::vector<float>& first_element,
    const std::vector<float>& second_element) const {
  float squared_distance{};
  for (std::size_t i = 0; i < first_element.size(); ++i) {
    squared_distance += (first_element[i] - second_element[i]) *
                        (first_element[i] - second_element[i]);
  }
  return std::sqrt(squared_distance);
}

}  // namespace daa
