#include "Sorting.h"
#include <iostream>
using namespace std;

// constructor
Sorting::Sorting(){
  low = 0;
  high = 0;
}

//deconstructor,
Sorting::~Sorting(){
}

void Sorting::quicksort(vector<int>& data, int low_idx, int high_idx){
  if (low_idx < high_idx){
    int p = quicksort_partition(data, low_idx, high_idx);
    quicksort(data, low_idx, p-1);
    quicksort(data, p+1, high_idx);
  }
  else{
    return;
  }
}

int Sorting::quicksort_partition(vector<int>& data, int low_idx, int high_idx){
  int pivot = data.at(high_idx);
  int i = low_idx;
  int j = low_idx;
  while (j <= high_idx-1){
    if (data.at(j) < pivot){
      int temp = data.at(j);
      data.at(j) = data.at(i);
      data.at(i) = temp;
      i++;
    }
    j++;
  }
  int temp = data.at(high_idx);
  data.at(high_idx) = data.at(i);
  data.at(i) = temp;

  return i;
}

void Sorting::bubblesort(vector<int>& data){
  for (int i = 0; i < data.size(); i++){
    for (int j = 0; j < data.size() - (i+1); j++ ){
        if (data.at(j) > data.at(j+1)){
          int temp = data.at(j);
          data.at(j) = data.at(j+1);
          data.at(j+1) = temp;
        }
    }
  }
  return;
}

void Sorting::mergesort(vector<int>& data){
  mergesorthelper(data, 0, data.size()-1);
}

void Sorting::mergesorthelper(vector<int>& data, int low, int high){

  if (low < high){
    int mid = (low + high)/2;
    mergesorthelper(data, low, mid);
    mergesorthelper(data, mid+1, high);
    vector<int> right;
    vector<int> left;
    vector<int> result;
    for (int i = low; i <= mid; i++){
      left.push_back(data.at(i));
    }
    for (int i = mid+1; i <= high; i++){
      right.push_back(data.at(i));
    }
    merge(left, right, result);
    int l = 0;
    for (int i = low; i <= high; i++){
      if (l < result.size()){
        data.at(i) = result.at(l);
        l++;
      }
    }

  }

}

void Sorting::merge(vector<int>& left, vector<int>& right, vector<int>& result){
  int i = 0;
  int j = 0;



  while (i < left.size() && j < right.size()){
    if (left.at(i) <= right.at(j)){
      result.push_back(left.at(i));
      i++;
    }
    else{
      result.push_back(right.at(j));
      j++;
    }

  }
  while (i < left.size()){
    result.push_back(left.at(i));
    i++;

  }
  while (j < right.size()){
    result.push_back(right.at(j));
    j++;

  }
}

void Sorting::insertion_sort(vector<int>& data){
  //insertion sort
  int index = 0;
  bool inserted = false;
  int temp;
  for (int i = 1; i < data.size(); i++){
    temp = data.at(i);
    for (int j = i-1; j >= 0;j--){
      if (temp < data.at(j)){
        data.at(j+1) = data.at(j);
        inserted = true;
        index = j;
      }
    }
    if (inserted){
      data.at(index) = temp;
      inserted = false;
    }
  }
}
