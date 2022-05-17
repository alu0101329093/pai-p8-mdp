#include "mdp/mdp_solver.h"

namespace daa {

/**
 * @brief Construct a new Mdp Solver:: Mdp Solver object
 *
 */
MdpSolver::MdpSolver() : algorithm_{} {}

/**
 * @brief Solve the problem using the selected algorithm
 *
 * @param problem
 * @param options
 * @return MdpSolution
 */
MdpSolution MdpSolver::Solve(const MdpProblem& problem,
                             const std::unique_ptr<MdpOptions>& options) {
  if (algorithm_) {
    return algorithm_->Solve(problem, options);
  }
}

/**
 * @brief Set the algorithm to use when solving
 *
 * @param type
 */
void MdpSolver::SetAlgorithm(AlgorithmTypes type) {
  switch (type) {
    case AlgorithmTypes::kGreedy:
      algorithm_.reset(new MdpGreedy{});
      break;
    case AlgorithmTypes::kGrasp:
      algorithm_.reset(new MdpGrasp());
      break;
    default:
      break;
  }
}

}  // namespace daa
