#ifndef P8MDP_MDP_MDP_BRANCH_BOUND_H_
#define P8MDP_MDP_MDP_BRANCH_BOUND_H_

#include <functional>
#include <memory>
#include <queue>
#include <set>
#include <vector>

#include "mdp/mdp_algorithm.h"
#include "mdp/mdp_branch_bound_options.h"
#include "mdp/mdp_grasp_options.h"
#include "mdp/mdp_node.h"
#include "mdp/mdp_options.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpBranchBound : public MdpAlgorithm {
 public:
  virtual MdpSolution Solve(const MdpProblem& problem,
                            const std::unique_ptr<MdpOptions>& options =
                                std::unique_ptr<MdpOptions>{}) override;

 private:
  ElementsSet GetChilds(const ElementsSet& branch,
                        const ElementsSet& elements_set) const;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_BRANCH_BOUND_H_