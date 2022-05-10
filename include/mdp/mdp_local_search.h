#ifndef P8MDP_MDP_MDP_LOCAL_SEARCH_H_
#define P8MDP_MDP_MDP_LOCAL_SEARCH_H_

#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpLocalSearch {
 public:
  virtual MdpSolution Execute(const MdpSolution& solution,
                              const ElementsSet& unused_elements) = 0;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_LOCAL_SEARCH_H_