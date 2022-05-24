#include "mdp/mdp_branch_bound.h"

namespace daa {

MdpSolution MdpBranchBound::Solve(const MdpProblem& problem,
                                  const std::unique_ptr<MdpOptions>& options) {
  MdpBranchBoundOptions* parsed_options =
      reinterpret_cast<MdpBranchBoundOptions*>(options.get());
  MdpAlgorithm* heuristic_function{parsed_options->GetHeuristicFuntion().get()};
  std::size_t subset_max_element{parsed_options->GetSubsetMaxElements()};
  ElementsSet elements_set{problem.GetElementsSet()};
  MdpNode::ComparisonType comparison{parsed_options->GetComparison()};

  MdpSolution best_solution{heuristic_function->Solve(
      problem, std::make_unique<daa::MdpGraspOptions>(subset_max_element,
                                                      nullptr, 100, 5, 10))};
  float lower_bound{best_solution.GetDiversity()};
  std::priority_queue<MdpNode, std::vector<MdpNode>, std::greater<MdpNode>>
      active_nodes{};
  for (const auto& element : GetChilds({}, elements_set)) {
    active_nodes.push(MdpNode{{},
                              element,
                              comparison,
                              GetChilds({element}, elements_set),
                              elements_set.size()});
  }
  while (active_nodes.size() != 0) {
    MdpNode node{active_nodes.top()};
    active_nodes.pop();
    if (node.GetBranch().size() == elements_set.size()) {
      if (node.GetDiversity() > lower_bound) {
        best_solution = MdpSolution{node.GetBranch(), node.GetBranch().size()};
        lower_bound = node.GetDiversity();
      }
      active_nodes.pop();
    } else {
      for (const auto& child : GetChilds(node.GetBranch(), elements_set)) {
        auto unselected_elements{node.GetBranch()};
        unselected_elements.erase(child);
        MdpNode child_node{node.GetBranch(), child, comparison,
                           unselected_elements, elements_set.size()};
        if (lower_bound <= child_node.GetUpperBound())
          active_nodes.push(child_node);
      }
    }
  }

  return best_solution;
}

ElementsSet MdpBranchBound::GetChilds(const ElementsSet& branch,
                                      const ElementsSet& elements_set) const {
  ElementsSet childs{elements_set};
  for (const auto& element : branch) {
    childs.erase(element);
  }
  return childs;
}

}  // namespace daa
