#include "solver.h"

Solver::Solver(const std::string data_path, const std::string config_path) : dataset(data_path), config(read_config(config_path)){};

Solver::~Solver() {}

const Dataset Solver::get_dataset() const
{
  return this->dataset;
};

Solution Solver::constructive()
{
  log_message("constructive", "======================= CONSTRUCTIVE =======================");
  
  // Initialize variables
  const Dataset dataset = get_dataset(); // Copy of the dataset
  Solution solution(dataset.get_num_items());
  std::vector<Item> items_out = dataset.get_items(); // Items left out of the partial solution
  int current_knapsack_capacity = dataset.get_knapsack_capacity(); // The space in weight yet available in the partial solution

  int current_item = 0;
  int best_item = 0; 

  int current_potential = 0;
  int best_potential = 0;

  int total_prize = 0;
  
  std::sort(items_out.begin(), items_out.end(), compare_by_value_weight_ratio);

  solution.include_item(items_out.at(0).label);
  total_prize += items_out.at(0).prize;
  current_knapsack_capacity -= items_out.at(0).weight;
  items_out.erase(items_out.begin());

  // Do
  do
  {
    best_item = 0;
    best_potential = 0;
    // For each item left out of the solution
    log_message("constructive", "Size: " + std::to_string(items_out.size()));
    for (int i = 0; i < items_out.size(); i++)
    {
      // Calculate it's prize minus it's penalties within the solution
      current_potential = items_out.at(i).prize - calculate_penalties(solution, items_out.at(i));
      // Save the item with the highest potential
      if (current_potential > best_potential)
      {
        best_potential = current_potential;
        best_item = i;
      }
    }
    log_message("constructive", "Best Item: " + std::to_string(items_out.at(best_item).label));
    log_message("constructive", "Best Potential: " + std::to_string(best_potential));
    
    // After selecting the best item for the current partial solution,
    // Check if it fits in the knapsack
    if (items_out.at(best_item).weight <= current_knapsack_capacity)
    {
      log_message("constructive", "    Inserted: TRUE");
      solution.include_item(items_out.at(best_item).label);
      current_knapsack_capacity -= items_out.at(best_item).weight;
      total_prize += best_potential;
    }
    else
    {
      log_message("constructive", "Inserted: FALSE");
    }

    items_out.erase(items_out.begin()+best_item);
  }
  while (items_out.size() > 0 && best_potential > 0);
  
  solution.set_prize(total_prize);
  return solution;
};

bool Solver::compare_by_value_weight_ratio(Item &a, Item &b)
{
  float ratio_a = static_cast<float>(a.prize)/a.weight;
  float ratio_b = static_cast<float>(b.prize)/b.weight;

  return ratio_a > ratio_b;
}

void Solver::log_message(const std::string method, const std::string message)
{
  if (config.find("log_methods") != config.end() && config["log_methods"].is_array())
  {
    auto permitted_methods = config["log_methods"].get<std::vector<std::string>>();
    bool found = std::find(permitted_methods.begin(), permitted_methods.end(), method) != permitted_methods.end();

    if (found)
      std::cout << message << std::endl;
  }
}

json Solver::read_config(const std::string file_path) {
  std::ifstream arquivo(file_path);

  if (!arquivo.is_open()) {
    // Handle the case where the file cannot be opend
    throw std::runtime_error("Error: Unable to open file " + file_path);
    return json();
  }

  json dadosJSON;
  arquivo >> dadosJSON;

  arquivo.close();

  return dadosJSON;
}

void Solver::log_solution(Solution &solution)
{
  std::cout << "    Solution = [";
  for (int i = 0; i < solution.get_items().size(); i++)
    std::cout << solution.get_items().at(i);
  std::cout << "]" << std::endl;
}

int Solver::calculate_penalties(const Solution &solution, const Item &item) const
{
  int sum = 0;
  for (int i = 0; i < item.penalties.size(); i++)
  {
    if (solution.get_item(item.penalties.at(i).first) == 1)
    {
      sum += item.penalties.at(i).second;
    }
  }
  return sum;
}

int Solver::calculate_item_potential(const Solution &solution, const Item &item)
{
  log_message("calculate_item_potential", "===================== POTENTIAL =====================");
  // Initialize variables
  int penalties_sum = 0;
  
  // If the item has no pairs with penalties
  if (item.penalties.size() == 0)
  {
    log_message("calculate_item_potential", "        Item " + std::to_string(item.label) + " doesn't have penalty pairs."); 
    return 0;
  }
  
  // For each item penalty O(p)
  for (int i = 0; i < item.penalties.size(); i++)
  {
    // If the pair is in the solution
    log_message("calculate_item_potential", std::to_string(item.penalties.at(i).first));
    if (solution.get_item(item.penalties.at(i).first) == 1)
    {
      // Sum penalty
      log_message("calculate_item_potential", "        Item " + std::to_string(item.penalties.at(i).first) + " is in the solution and it's total penalty with item " + std::to_string(item.label) + " is: " + std::to_string(item.penalties.at(i).second));
      penalties_sum += item.penalties.at(i).second;
    }
    else
    {
      // Do nothing
      log_message("calculate_item_potential", "        Item " + std::to_string(item.penalties.at(i).first) + " is NOT in the solution.");
    }
  }
  
  // Calculate the item potential
  int total_potential = item.prize - penalties_sum;

  return total_potential;
};
