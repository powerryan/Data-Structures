#ifndef SORTING_H__
#define SORTING_H__

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Sorting {
public:
  // constructor
  Sorting();
  // deconstructor
  ~Sorting();
  void quicksort(vector<int>& data, int low_idx, int high_idx);
  int quicksort_partition(vector<int>& data, int low_idx, int high_idx);
  void bubblesort(vector<int>& data);
  void mergesort(vector<int>& data);
  void insertion_sort(vector<int>& data);

private:
  // this pointer always will point to root of the tree
  shared_ptr<int> high;
  shared_ptr<int> low;
  // merge is the helper function for mergesort. It returns a vector
  // containing the merged contents of the two input vectors.
  // defines an empty vector and passes to result, once this
  // function returns, merged content will be in that vector (hence pass by reference).
  void merge(vector<int>& left, vector<int>& right, vector<int>& result);
  void mergesorthelper(vector<int>& data, int low, int high);
};

#endif  // SORTING_H__
