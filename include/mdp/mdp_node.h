#ifndef P8MDP_MDP_MDP_NODE_H_
#define P8MDP_MDP_MDP_NODE_H_

#include <queue>
#include <vector>

#include "mdp/mdp_solution.h"

namespace daa {

class MdpNode {
 public:
  enum class ComparisonType { kLessUpperBound, kDeeper };

  MdpNode(const ElementsSet& element_branch, const std::vector<float>& element,
          ComparisonType comparison, const ElementsSet& unselected_elements,
          std::size_t solution_length);

  inline const ElementsSet& GetBranch() const { return branch_; }
  inline void SetBranch(const ElementsSet& branch) {
    branch_ = branch;
    CalculateDiversity();
  }

  inline float GetDiversity() const { return diversity_; }

  inline float GetUpperBound() const { return upper_bound_; }
  inline void SetUpperBound(float upper_bound) { upper_bound_ = upper_bound; }

  friend bool operator<(const MdpNode& first_node, const MdpNode& second_node) {
    if (first_node.comparison_ == MdpNode::ComparisonType::kLessUpperBound)
      return first_node.upper_bound_ < second_node.upper_bound_;
    if (first_node.comparison_ == MdpNode::ComparisonType::kDeeper)
      return first_node.branch_.size() > second_node.branch_.size();
  }

  friend bool operator>(const MdpNode& first_node, const MdpNode& second_node) {
    if (first_node.comparison_ == MdpNode::ComparisonType::kLessUpperBound)
      return first_node.upper_bound_ > second_node.upper_bound_;
    if (first_node.comparison_ == MdpNode::ComparisonType::kDeeper)
      return first_node.branch_.size() < second_node.branch_.size();
  }

 private:
  void CalculateDiversity();

  void CalculateUpperBound(const std::vector<float>& element,
                           const ElementsSet& selected_elements,
                           const ElementsSet& unselected_elements,
                           std::size_t solution_length);
  float CalculateZSel(const std::vector<float>& element,
                      const ElementsSet& selected_elements);
  float CalculateZUnsel(const std::vector<float>& element,
                        const ElementsSet& unselected_elements,
                        std::size_t solution_length);
  float CalculateDistance(const std::vector<float>& first_element,
                          const std::vector<float>& second_element) const;

  ElementsSet branch_;
  float diversity_;
  float upper_bound_;
  ComparisonType comparison_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_NODE_H_