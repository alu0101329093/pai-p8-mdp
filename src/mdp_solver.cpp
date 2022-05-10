#include "mdp/mdp_solver.h"

namespace daa {

MdpSolver::MdpSolver() : algorithm_{} {}

MdpSolution MdpSolver::Solve(const MdpProblem& problem,
                             std::size_t subset_max_elements,
                             MdpLocalSearch* local_search) {
  if (algorithm_) {
    return algorithm_->Solve(problem, subset_max_elements, local_search);
  }
}

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
