#include "mdp/mdp_branch_bound_options.h"

namespace daa {

/**
 * @brief Construct a new Mdp Grasp Options:: Mdp Grasp Options object
 *
 * @param subset_max_elements
 * @param local_search
 * @param iterations
 * @param random_solutions_amount
 * @param max_unchanged_iterations
 */
MdpBranchBoundOptions::MdpBranchBoundOptions(std::size_t subset_max_elements,
                                             MdpLocalSearch* local_search,
                                             MdpSolver* heuristic_function,
                                             MdpNode::ComparisonType comparison)
    : MdpOptions{subset_max_elements, local_search},
      heuristic_function_{heuristic_function},
      comparison_{comparison} {}

// MdpBranchBoundOptions::~MdpBranchBoundOptions() {}

}  // namespace daa
