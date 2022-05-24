#ifndef P8MDP_MDP_MDP_NODE_H_
#define P8MDP_MDP_MDP_NODE_H_

#include <vector>

#include "mdp/mdp_solution.h"

namespace daa {

class MdpNode {
 public:
  MdpNode(const ElementsSet& element_branch, std::vector<float> element);

  inline const ElementsSet& GetBranch() const { return branch_; }
  inline void SetBranch(const ElementsSet& branch) {
    branch_ = branch;
    CalculateDiversity();
  }

  inline float GetDiversity() const { return diversity_; }

  inline float GetUpperBound() const { return upper_bound_; }
  inline void SetUpperBound(float upper_bound) { upper_bound_ = upper_bound; }

  friend bool operator<(const MdpNode& first_node, const MdpNode& second_node) {
    return first_node.diversity_ < second_node.diversity_;
  }

  friend bool operator>(const MdpNode& first_node, const MdpNode& second_node) {
    return first_node.diversity_ > second_node.diversity_;
  }

 private:
  void CalculateDiversity();

  ElementsSet branch_;
  float diversity_;
  float upper_bound_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_NODE_H_