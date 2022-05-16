#include "mdp/mdp_options.h"

namespace daa {

/**
 * @brief Construct a new Mdp Options:: Mdp Options object
 * 
 * @param subset_max_elements 
 * @param local_search 
 */
MdpOptions::MdpOptions(std::size_t subset_max_elements,
                       MdpLocalSearch* local_search)
    : subset_max_elements_{subset_max_elements}, local_search_{local_search} {}

}  // namespace daa
