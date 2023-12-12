#ifndef SOLVER_H
#define SOLVER_H

#include "dataset.h"
#include "solution.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Solver
{
  private:
    const Dataset dataset;
    const json config;

  protected:
    static bool compare_by_value_weight_ratio(Item &, Item &);
    json read_config(const std::string);
    
  public:
    Solver(const std::string, const std::string);
    ~Solver();
    
    const Dataset get_dataset() const;
    Solution constructive();

    // Auxiliaries
    int calculate_penalties(const Solution &, const Item &) const;
    int calculate_item_potential(const Solution &, const Item &);
    void log_message(const std::string, const std::string);
    void log_solution(Solution &);
};

#endif