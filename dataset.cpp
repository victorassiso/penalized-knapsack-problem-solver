#include "dataset.h"

// Constructor
Dataset::Dataset(const std::string file_path)
{
  int num_penalties, min_weight, item_with_min_weight;

  // Open the input file
  std::ifstream file(file_path);
  if (!file.is_open())
  {
    // Handle the case where the file cannot be opend
    throw std::runtime_error("Error: Unable to open file " + file_path);
  }

  // Read the first line of the file to get dataset parameters
  if (!(file >> num_items >> num_penalties >> knapsack_capacity))
  {
    // Handle the case where reading failed
    throw std::runtime_error("Error reading dataset parameters from file");
  }

  // Resize items vector to the specified number of items
  items.resize(num_items);

  // Define the items' values and labels
  for (int i = 0; i < num_items; i++)
  {
    file >> items[i].prize;
    items[i].label = i;
  }
  // Define the items' weights
  for (int i = 0; i < num_items; i++)
  {
    file >> items[i].weight;
  }

  // Initialize penalties map for each item
  for (int i = 0; i < num_penalties; i++)
  {
    int temp1, penalty, temp2, item_1, item_2; // temp1 e temp2 são descartados
    file >> temp1 >> penalty >> temp2 >> item_1 >> item_2;
    items[item_1].penalties.push_back(std::make_pair(item_2, penalty));
    items[item_2].penalties.push_back(std::make_pair(item_1, penalty));
  }

  file.close();
}

// Destructor
Dataset::~Dataset() {};

// Getters
int Dataset::get_num_items() const {return this->num_items;};
int Dataset::get_knapsack_capacity() const {return knapsack_capacity;};
std::vector<Item> Dataset::get_items() const {return items;}
Item Dataset::get_item(const int i) const {return get_items().at(i);};
int Dataset::get_label(const int i) const {return get_item(i).label;}
int Dataset::get_prize(const int i) const {return get_item(i).prize;}
int Dataset::get_weight(const int i) const {return get_item(i).weight;}
std::vector<std::pair<int, int>> Dataset::get_penalties(const int i) const {return get_item(i).penalties;}
std::pair<int, int> Dataset::get_penalty(const int item_index, const int penalty_index) const {return get_item(item_index).penalties.at(penalty_index);}

// Auxiliaries
void Dataset::log_dataset() const
{
  const int num_items = this->get_num_items();
  const int knapsack_capacity = this->get_knapsack_capacity();
  const std::vector<Item> items = this->get_items();

  std::cout << "Number of itens: " << num_items << std::endl;
  std::cout << "Knapsack capacity: " << knapsack_capacity << std::endl;

  std::cout << "=================PRIZE=================" << std::endl;
  for (int i = 0; i < num_items; i++)
    std::cout << "[" << i << "] = " << get_prize(i) << std::endl;
  std::cout << "=================WEIGHT=================" << std::endl;
  for (int i = 0; i < num_items; i++)
    std::cout << "[" << i << "] = " << get_weight(i) << std::endl;

  std::cout << "================PENALTIES===============" << std::endl;
  for (int i = 0; i < num_items; i++)
  {
    std::cout << "Penalties for item " << i << " -> [";
    int count = 0;
    for (auto pair : get_penalties(i))
    {
      std::cout << "(" << pair.first << ", " << pair.second << ")";
      count++;
      if (count < get_penalties(i).size())
        std::cout << ", ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "============================================" << std::endl;
};