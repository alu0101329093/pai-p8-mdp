#include "mdp/mdp_node.h"

namespace daa {

MdpNode::MdpNode(const ElementsSet& element_branch, std::vector<float> element)
    : branch_{element_branch}, diversity_{}, upper_bound_{} {
  branch_.insert(element);
  CalculateDiversity();
}

void MdpNode::CalculateDiversity() {
  MdpSolution solution{branch_};
  diversity_ = solution.GetDiversity();
}

}  // namespace daa
