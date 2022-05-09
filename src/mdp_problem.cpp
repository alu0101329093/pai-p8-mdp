#include "mdp/mdp_problem.h"

namespace daa {

/**
 * @brief Construct a new empty Mdp Problem:: Mdp Problem object
 */
MdpProblem::MdpProblem()
    : elements_set_{}, elements_amount_{}, dimensions_amount_{} {}

/**
 * @brief Construct a new Mdp Problem:: Mdp Problem object
 *
 * @param elements_set
 * @param elements_amount
 * @param dimensions_amount
 */
MdpProblem::MdpProblem(const ElementsSet& elements_set,
                       std::size_t elements_amount,
                       std::size_t dimensions_amount)
    : elements_set_{elements_set},
      elements_amount_{elements_amount},
      dimensions_amount_{dimensions_amount} {}

}  // namespace daa
