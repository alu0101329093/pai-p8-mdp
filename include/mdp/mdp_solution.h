#ifndef P8MDP_MDP_MDP_SOLUTION_H_
#define P8MDP_MDP_MDP_SOLUTION_H_

#include <set>
#include <vector>

namespace daa {

typedef std::set<std::vector<float>> ElementsSet;

class MdpSolution {
 public:
  MdpSolution(const ElementsSet& elements_set, std::size_t elements_amount);

  inline const ElementsSet& GetElementsSet() const { return elements_set_; }
  inline void SetElementsSet(const ElementsSet& elements_set) {
    elements_set_ = elements_set;
  }
  inline std::size_t GetElementsAmount() const { return elements_amount_; }

 private:
  ElementsSet elements_set_;
  std::size_t elements_amount_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_SOLUTION_H_