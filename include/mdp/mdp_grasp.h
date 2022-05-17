#ifndef P8MDP_MDP_MDP_GRASP_H_
#define P8MDP_MDP_MDP_GRASP_H_

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>

#include "mdp/mdp_algorithm.h"
#include "mdp/mdp_grasp_options.h"
#include "mdp/mdp_options.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpGrasp : public MdpAlgorithm {
 public:
  virtual MdpSolution Solve(const MdpProblem& problem,
                            const std::unique_ptr<MdpOptions>& options =
                                std::unique_ptr<MdpOptions>{}) override;

 private:
  struct ConstructionSolution {
    MdpSolution solution;
    ElementsSet unused_elements;
  };

  ConstructionSolution ConstructionPhase(const MdpProblem& problem,
                                         MdpGraspOptions* options) const;
  ElementsSet GenerateLRC(const MdpProblem& problem,
                          std::size_t random_solutions_amount) const;
  std::vector<float> GetRandomElement(const ElementsSet& elements_set) const;
  std::vector<float> GetCenter(const ElementsSet& elements_set) const;
  float GetDistance(const std::vector<float>& first_element,
                    const std::vector<float>& second_element) const;
  std::vector<float> GetMostAwayElement(const std::vector<float>& center,
                                        const ElementsSet& elements_set) const;
  ConstructionSolution SolvePartialSolution(const MdpProblem& problem,
                                            const MdpSolution& partial_solution,
                                            MdpGraspOptions* options) const;

  MdpSolution PostProcessing(const MdpSolution& solution,
                             MdpGraspOptions* options,
                             const ElementsSet& unused_elements) const;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_GRASP_H_
