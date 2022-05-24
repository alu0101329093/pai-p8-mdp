#ifndef P8MDP_MDP_MDP_SOLVER_H_
#define P8MDP_MDP_MDP_SOLVER_H_

#include <memory>

#include "mdp/mdp_algorithm.h"
#include "mdp/mdp_branch_bound.h"
#include "mdp/mdp_grasp.h"
#include "mdp/mdp_greedy.h"
#include "mdp/mdp_options.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpSolver {
 public:
  enum class AlgorithmTypes { kGreedy, kGrasp, kBranchBound };

  MdpSolver();

  MdpSolution Solve(const MdpProblem& problem,
                    const std::unique_ptr<MdpOptions>& options =
                        std::unique_ptr<MdpOptions>{});

  void SetAlgorithm(AlgorithmTypes type);

 private:
  std::unique_ptr<MdpAlgorithm> algorithm_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_SOLVER_H_