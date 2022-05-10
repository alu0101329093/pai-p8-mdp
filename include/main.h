#ifndef P8MDP_MAIN_H_
#define P8MDP_MAIN_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"
#include "mdp/mdp_solver.h"

namespace daa {

MdpProblem ReadInfoFromFile(const std::string& file_name);

}  // namespace daa

int main(int argc, char* argv[]);

#endif  // P8MDP_MAIN_H_