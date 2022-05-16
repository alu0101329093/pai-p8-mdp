#ifndef P8MDP_MDP_MDP_GRASP_OPTIONS_H_
#define P8MDP_MDP_MDP_GRASP_OPTIONS_H_

#include <cstdlib>

#include "mdp/mdp_options.h"

namespace daa {

class MdpGraspOptions : public MdpOptions {
 public:
  MdpGraspOptions(std::size_t subset_max_elements, MdpLocalSearch* local_search,
                  std::size_t iterations, std::size_t random_solutions_amount,
                  std::size_t max_unchanged_iterations);
  // virtual ~MdpGraspOptions() override;

  inline std::size_t GetIterations() const { return iterations_; }
  inline void SetIterations(std::size_t iterations) {
    iterations_ = iterations;
  }

  inline std::size_t GetRandomSolutionsAmount() const {
    return random_solutions_amount_;
  }
  inline void SetRandomSolutionsAmount(std::size_t random_solutions_amount) {
    random_solutions_amount_ = random_solutions_amount;
  }

  inline std::size_t GetMaxUnchangedIterations() const {
    return max_unchanged_iterations_;
  }
  inline void SetMaxUnchangedIterations(std::size_t max_unchanged_iterations) {
    max_unchanged_iterations_ = max_unchanged_iterations;
  }

 private:
  std::size_t iterations_;
  std::size_t random_solutions_amount_;
  std::size_t max_unchanged_iterations_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_GRASP_OPTIONS_H_