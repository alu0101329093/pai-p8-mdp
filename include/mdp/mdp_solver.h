#ifndef P7VRP_MDP_MDP_SOLVER_H_
#define P7VRP_MDP_MDP_SOLVER_H_

#include <memory>

#include "mdp/mdp_algorithm.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpSolver {
 public:
  enum class AlgorithmTypes { kGreedy, kGrasp };

  MdpSolver();

  MdpSolution Solve(const MdpProblem& problem, std::size_t subset_max_elements);

  void SetAlgorithm(AlgorithmTypes type);

 private:
  std::unique_ptr<MdpAlgorithm> algorithm_;
};

}  // namespace daa

#endif  // P7VRP_MDP_MDP_SOLVER_H_