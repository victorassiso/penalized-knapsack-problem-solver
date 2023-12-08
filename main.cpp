#include "dataset.h"

int main()
{
  Dataset dataset("instances/500/kpf_1_sum.txt");

  dataset.log_dataset();
}