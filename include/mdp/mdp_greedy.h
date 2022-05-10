#ifndef P8MDP_MDP_MDP_GREEDY_H_
#define P8MDP_MDP_MDP_GREEDY_H_

#include <cmath>
#include <set>
#include <vector>

#include "mdp/mdp_algorithm.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpGreedy : public MdpAlgorithm {
 public:
  MdpGreedy();

  virtual MdpSolution Solve(const MdpProblem& problem,
                            std::size_t subset_max_elements) override;

 private:
  std::vector<float> GetCenter(const ElementsSet& elements_set) const;
  std::size_t GetDistance(const std::vector<float>& first_element,
                          const std::vector<float>& second_element) const;
  std::vector<float> GetMostAwayElement(const std::vector<float>& center,
                                        const ElementsSet& elements_set) const;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_GREEDY_H_
