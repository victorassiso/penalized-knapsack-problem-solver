#ifndef SOLUTION_H
#define SOLUTION_H

#include "dataset.h"

class Solution {
  private:
    std::vector<int> items;
    int prize;
    int weight;

  public:
    Solution(int); // Criate empty solution with size n;
    ~Solution();

    int get_prize() const;
    int get_weight() const;
    std::vector<int> get_items() const;
    int get_item(const int) const;

    void set_prize(const int);
    void set_weight(const int);
    void set_items(const std::vector<int>);
  
    void print();
    void include_item(const int);
    
    int calculate_prize(const Dataset &) const;
};

#endif