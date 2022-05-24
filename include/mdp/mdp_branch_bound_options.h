#ifndef P8MDP_MDP_MDP_BRANCH_BOUND_OPTIONS_H_
#define P8MDP_MDP_MDP_BRANCH_BOUND_OPTIONS_H_

#include <cstdlib>
#include <memory>

#include "mdp/mdp_options.h"
#include "mdp/mdp_solver.h"

namespace daa {

class MdpBranchBoundOptions : public MdpOptions {
 public:
  MdpBranchBoundOptions(std::size_t subset_max_elements,
                        MdpLocalSearch* local_search,
                        MdpSolver* heuristic_function);
  // virtual ~MdpBranchBoundOptions() override;

  inline const std::unique_ptr<MdpSolver>& GetHeuristicFuntion() const {
    return heuristic_function_;
  }
  inline void SetHeuristicFunction(MdpSolver* function) {
    heuristic_function_.reset(function);
  }

 private:
  std::unique_ptr<MdpSolver> heuristic_function_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_BRANCH_BOUND_OPTIONS_H_