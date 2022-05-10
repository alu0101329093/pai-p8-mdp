#include "mdp/mdp_solver.h"

namespace daa {

MdpSolver::MdpSolver() : algorithm_{} {}

MdpSolution MdpSolver::Solve(const MdpProblem& problem,
                             std::size_t subset_max_elements) {
  if (algorithm_) {
    return algorithm_->Solve(problem, subset_max_elements);
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
