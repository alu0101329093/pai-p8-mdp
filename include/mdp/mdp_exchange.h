#ifndef P8MDP_MDP_MDP_EXCHANGE_H_
#define P8MDP_MDP_MDP_EXCHANGE_H_

#include "mdp/mdp_local_search.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"

namespace daa {

class MdpExchange : public MdpLocalSearch {
 public:
  MdpExchange();

  virtual MdpSolution Execute(const MdpSolution& solution,
                              const ElementsSet& unused_elements) override;

 private:
  float GetDistance(const std::vector<float>& first_element,
                    const std::vector<float>& second_element) const;
  float GetElementRemoveDiversity(const std::vector<float>& element_to_remove,
                                  const ElementsSet& elements_set,
                                  float solution_diversity) const;
  float GetElementAddDiversity(const std::vector<float>& element_to_add,
                               const std::vector<float>& removed_element,
                               const ElementsSet& elements_set,
                               float remove_diversity) const;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_EXCHANGE_H_
