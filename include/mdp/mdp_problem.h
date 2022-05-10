#ifndef P8MDP_MDP_MDP_PROBLEM_H_
#define P8MDP_MDP_MDP_PROBLEM_H_

#include <set>
#include <vector>

namespace daa {

typedef std::set<std::vector<float>> ElementsSet;

class MdpProblem {
 public:
  MdpProblem();
  MdpProblem(const ElementsSet& elements_set, std::size_t elements_amount,
             std::size_t dimensions_amount);

  inline const ElementsSet& GetElementsSet() const { return elements_set_; }
  inline void SetElementsSet(const ElementsSet& elements_set) {
    elements_set_ = elements_set;
  }
  inline std::size_t GetElementsAmount() const { return elements_amount_; }
  inline void SetElementsAmount(std::size_t amount) {
    elements_amount_ = amount;
  }
  inline std::size_t GetDimensionsAmount() const { return dimensions_amount_; }
  inline void SetDimensionsAmount(std::size_t amount) {
    dimensions_amount_ = amount;
  }

 private:
  ElementsSet elements_set_;
  std::size_t elements_amount_;
  std::size_t dimensions_amount_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_PROBLEM_H_