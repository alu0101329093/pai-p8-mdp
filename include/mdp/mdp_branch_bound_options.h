#ifndef P8MDP_MDP_MDP_BRANCH_BOUND_OPTIONS_H_
#define P8MDP_MDP_MDP_BRANCH_BOUND_OPTIONS_H_

#include <cstdlib>
#include <memory>

#include "mdp/mdp_algorithm.h"
#include "mdp/mdp_node.h"
#include "mdp/mdp_options.h"

namespace daa {

class MdpBranchBoundOptions : public MdpOptions {
 public:
  MdpBranchBoundOptions(std::size_t subset_max_elements,
                        MdpLocalSearch* local_search,
                        MdpAlgorithm* heuristic_function,
                        MdpNode::ComparisonType comparison);
  // virtual ~MdpBranchBoundOptions() override;

  inline const std::unique_ptr<MdpAlgorithm>& GetHeuristicFuntion() const {
    return heuristic_function_;
  }
  inline void SetHeuristicFunction(MdpAlgorithm* function) {
    heuristic_function_.reset(function);
  }

  inline MdpNode::ComparisonType GetComparison() const { return comparison_; }
  inline void SetComparison(MdpNode::ComparisonType comparison) {
    comparison_ = comparison;
  }

 private:
  std::unique_ptr<MdpAlgorithm> heuristic_function_;
  MdpNode::ComparisonType comparison_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_BRANCH_BOUND_OPTIONS_H_