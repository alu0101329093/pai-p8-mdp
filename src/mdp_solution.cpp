#include "mdp/mdp_solution.h"

namespace daa {

/**
 * @brief Construct a new Mdp Problem:: Mdp Problem object
 *
 * @param elements_set
 * @param elements_amount
 */
MdpSolution::MdpSolution(const ElementsSet& elements_set,
                         std::size_t elements_amount)
    : elements_set_{elements_set}, elements_amount_{elements_amount} {}

}  // namespace daa
