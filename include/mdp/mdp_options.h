#ifndef P8MDP_MDP_MDP_OPTIONS_H_
#define P8MDP_MDP_MDP_OPTIONS_H_

#include <cstdlib>
#include <memory>

#include "mdp/mdp_local_search.h"

namespace daa {

class MdpOptions {
 public:
  MdpOptions(std::size_t subset_max_elements, MdpLocalSearch* local_search);
  // virtual ~MdpOptions() = 0;

  inline std::size_t GetSubsetMaxElements() const {
    return subset_max_elements_;
  }
  inline void SetSubsetMaxElements(std::size_t subset_max_elements) {
    subset_max_elements_ = subset_max_elements;
  }

  inline const std::unique_ptr<MdpLocalSearch>& GetLocalSearch() const {
    return local_search_;
  }
  inline void SetLocalSearch(MdpLocalSearch* local_search) {
    local_search_.reset(local_search);
  }

 private:
  std::size_t subset_max_elements_;
  std::unique_ptr<MdpLocalSearch> local_search_;
};

}  // namespace daa

#endif  // P8MDP_MDP_MDP_OPTIONS_H_