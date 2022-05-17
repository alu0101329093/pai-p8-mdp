#ifndef P8MDP_MDP_MDP_SOLUTION_H_
#define P8MDP_MDP_MDP_SOLUTION_H_

#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

namespace daa {

typedef std::set<std::vector<float>> ElementsSet;

class MdpSolution {
 public:
  MdpSolution(const ElementsSet& elements_set = {},
              std::size_t elements_amount = 0);

  inline const ElementsSet& GetElementsSet() const { return elements_set_; }
  inline void SetElementsSet(const ElementsSet& elements_set) {
    elements_set_ = elements_set;
  }
  inline std::size_t GetElementsAmount() const { return elements_amount_; }
  inline void SetElementsAmount(std::size_t amount) {
    elements_amount_ = amount;
  }

  float GetDiversity() const;

  friend std::ostream& operator<<(std::ostream& os,
                                  const MdpSolution& solution) {
    os << "Elements amount: " << solution.elements_amount_ << "\n";
    os << "Elements:\n";
    std::size_t index{};
    for (const auto& element : solution.elements_set_) {
      std::cout << index++ << ": ";
      for (std::size_t i = 0; i < element.size(); ++i) {
        std::cout << element[i] << (i == element.size() - 1 ? "\n" : ", ");
      }
    }
    os << "Diversity: " << solution.GetDiversity() << "\n";

    return os;
  }

 private:
  float GetDistance(const std::vector<float>& first_element,
                    const std::vector<float>& second_element) const;

  ElementsSet elements_set_;
  std::size_t elements_amount_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_SOLUTION_H_