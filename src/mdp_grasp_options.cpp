#include "mdp/mdp_grasp_options.h"

namespace daa {

MdpGraspOptions::MdpGraspOptions(std::size_t subset_max_elements,
                                 MdpLocalSearch* local_search,
                                 std::size_t iterations,
                                 std::size_t random_solutions_amount,
                                 std::size_t max_unchanged_iterations)
    : MdpOptions{subset_max_elements, local_search},
      iterations_{iterations},
      random_solutions_amount_{random_solutions_amount},
      max_unchanged_iterations_{max_unchanged_iterations} {}

MdpGraspOptions::~MdpGraspOptions() {}

}  // namespace daa
