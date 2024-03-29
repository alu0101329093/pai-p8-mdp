#ifndef P8MDP_MAIN_H_
#define P8MDP_MAIN_H_

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "mdp/mdp_branch_bound.h"
#include "mdp/mdp_branch_bound_options.h"
#include "mdp/mdp_exchange.h"
#include "mdp/mdp_grasp_options.h"
#include "mdp/mdp_node.h"
#include "mdp/mdp_options.h"
#include "mdp/mdp_problem.h"
#include "mdp/mdp_solution.h"
#include "mdp/mdp_solver.h"

namespace daa {

MdpProblem ReadInfoFromFile(const std::string& file_name);

void ShowGreedyOutput(const std::string& path);
void ShowGreedyExchangeOutput(const std::string& path);
void ShowGraspOutput(const std::string& path);
void ShowBBLessGreedyOutput(const std::string& path);
void ShowBBLessGraspOutput(const std::string& path);
void ShowBBDeepGreedyOutput(const std::string& path);
void ShowBBDeepGraspOutput(const std::string& path);

}  // namespace daa

int main(int argc, char* argv[]);

#endif  // P8MDP_MAIN_H_