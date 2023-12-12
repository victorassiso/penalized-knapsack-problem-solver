#include "dataset.h"
#include "solver.h"

int main()
{
  Solver solver("instances/500/kpf_1_sum.txt", "config.json");

  Solution solution = solver.constructive();
  solution.print();
  std::cout<<"Total Prize: "<<solution.get_prize()<<std::endl;

  int calculated_prize = solution.calculate_prize(solver.get_dataset());
  std::cout<<"Calculated Prize: "<<calculated_prize<<std::endl;
}