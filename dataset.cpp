#include "dataset.h"

Dataset::Dataset(const std::string file_path)
{
  // Initialize variables to store information from the input file
  int num_penalties;

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
    file >> items[i].value;
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

Dataset::~Dataset() {
  // If needed, perform cleanup here
}

int Dataset::get_num_items() const
{
  return num_items;
}

int Dataset::get_knapsack_capacity() const
{
  return knapsack_capacity;
}

std::vector<Item> Dataset::get_items_vector() const
{
  return items;
}

void Dataset::log_dataset()
{
  const int num_items = this->get_num_items();
  const int knapsack_capacity = this->get_knapsack_capacity();
  const std::vector<Item> items = this->get_items_vector();

  std::cout << "Number of itens: " << num_items << std::endl;
  std::cout << "Knapsack capacity: " << knapsack_capacity << std::endl;

  std::cout << "=================VALUE=================" << std::endl;
  for (int i = 0; i < num_items; i++)
    std::cout << "[" << i << "] = " << items[i].value << std::endl;
  std::cout << "=================WEIGHT=================" << std::endl;
  for (int i = 0; i < num_items; i++)
    std::cout << "[" << i << "] = " << items[i].weight << std::endl;

  std::cout << "================PENALTIES===============" << std::endl;
  for (int i = 0; i < num_items; i++)
  {
    std::cout << "Penalties for item " << i << " -> [";
    int count = 0;
    for (auto pair : items[i].penalties)
    {
      std::cout << "(" << pair.first << ", " << pair.second << ")";
      count++;
      if (count < items[i].penalties.size())
        std::cout << ", ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "============================================" << std::endl;
};