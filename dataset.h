#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Item
{
  int label;
  int value;
  int weight;
  std::vector<std::pair<int, int>> penalties; // (label, penalty)
};

class Dataset
{
  private:
    int num_items;
    int knapsack_capacity;
    std::vector<Item> items;
    
  public:
    Dataset(const std::string);
    ~Dataset();
    
    // Getters
    int get_num_items() const;
    int get_knapsack_capacity() const;
    std::vector<Item> get_items_vector() const;

    // Auxiliaries
    void log_dataset();
};

#endif
