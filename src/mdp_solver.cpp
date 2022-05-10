#include "mdp/mdp_solver.h"

namespace daa {

MdpSolver::MdpSolver() : algorithm_{} {}

MdpSolution MdpSolver::Solve(const MdpProblem& problem,
                             std::size_t subset_max_elements) {
  if (algorithm_) {
    return algorithm_->Solve(problem, subset_max_elements);
  }
}

}  // namespace daa
