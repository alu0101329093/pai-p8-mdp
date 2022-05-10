#ifndef P8MDP_MDP_MDP_ALGORITHM_H_
#define P8MDP_MDP_MDP_ALGORITHM_H_

#include <cstdlib>

#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpAlgorithm {
 public:
  virtual MdpSolution Solve(const MdpProblem& problem,
                            std::size_t subset_max_elements);
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_ALGORITHM_H_