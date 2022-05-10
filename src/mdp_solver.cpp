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
 * @param subset_max_elements
 * @param local_search
 * @return MdpSolution
 */
MdpSolution MdpSolver::Solve(const MdpProblem& problem,
                             std::size_t subset_max_elements,
                             MdpLocalSearch* local_search) {
  if (algorithm_) {
    return algorithm_->Solve(problem, subset_max_elements, local_search);
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
    default:
      break;
  }
}

}  // namespace daa
