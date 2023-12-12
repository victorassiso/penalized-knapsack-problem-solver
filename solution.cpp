#include "solution.h"

Solution::Solution(int size)
{
  std::vector<int> items(size, 0);
  
  set_weight(0);
  set_prize(0);
  set_items(items);
};

Solution::~Solution() {};

int Solution::get_prize() const {return prize;};
int Solution::get_weight() const {return weight;};
std::vector<int> Solution::get_items() const {return items;};
int Solution::get_item(const int i) const {return get_items().at(i);}

void Solution::set_prize(const int _prize) {prize = _prize;};
void Solution::set_weight(const int _weight) {weight = _weight;};
void Solution::set_items(const std::vector<int> _items) {items = _items;};

void Solution::include_item(const int i) {items.at(i) = 1;};

void Solution::print()
{
  std::vector<int> items = get_items();

  std::cout<<"Solution: [";
  for (int i=0; i<items.size(); i++)
  {
    std::cout<<items.at(i);
  }
  std::cout<<"]"<<std::endl;
}

int Solution::calculate_prize(const Dataset &dataset) const
{
  int prize = 0;
  for (int i = 0; i < get_items().size(); i++)
  {
    if (get_item(i) == 1)
    {
      prize += dataset.get_prize(i);

      for (int j = 0; j < dataset.get_penalties(i).size(); j++)
      {
        if (get_item(dataset.get_penalty(i, j).first) == 1 && dataset.get_penalty(i, j).first > i)
        {
          prize -= dataset.get_penalty(i, j).second;
        }
      }
    }
  }
  return prize;
};