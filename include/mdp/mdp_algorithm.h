#ifndef P8MDP_MDP_MDP_ALGORITHM_H_
#define P8MDP_MDP_MDP_ALGORITHM_H_

#include <cstdlib>

#include "mdp/mdp_options.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpAlgorithm {
 public:
  virtual MdpSolution Solve(const MdpProblem& problem,
                            const std::unique_ptr<MdpOptions>& options =
                                std::unique_ptr<MdpOptions>{}) = 0;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_ALGORITHM_H_