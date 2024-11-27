#include "sort_bus_lines.h"
#include <string.h>

void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
//uses partition function and quick_sort algorithm in order
//to sort the array
{
  BusLine * prt;
  if (end - start > 1){
    prt = partition(start, end, sort_type);
    quick_sort(start,prt, sort_type);
    quick_sort(prt+1,end,sort_type);
    }
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type){
  //handles sort by distance and sort by duration
  //is an helper function to quick sort
  //returns pivot and sorts parts of array
  if(sort_type == DISTANCE){
    BusLine * i = start;
    i-=1;
    BusLine *j;
    BusLine temp;
    BusLine *last = end-1;////////////////////
    for(j=start;j<(last);j++)
    {
      if ((*j).distance <= (*last).distance)
      {
        i += 1;
        temp = *i;
        *i = (*j);
        (*j) = temp;
      }
    }
    i +=1;
    temp = (*i);
    (*i) = (*last);
    *last = temp;
    return i;
  }
  else{
    BusLine * i = start;
    i-=1;
    BusLine *j;
    BusLine temp;
    BusLine *last = end-1;
    for(j=start;j<(last);j++)
    {
      if ((*j).duration <= (*last).duration)
      {
        i += 1;
        temp = *i;
        *i = (*j);
        (*j) = temp;
      }
    }
    i +=1;
    temp = (*i);
    (*i) = (*last);
    *last = temp;
    return i;
  }
}

void swap(BusLine *big, BusLine *small) {
  //helper function which swaps between two pointers
  BusLine temp = *big;
  *big = *small;
  *small = temp;
}

void bubble_sort (BusLine *start, BusLine *end){
  //sorts array by name using bubble sort algorithm
  int i, j;
  int size = end-start;
  for(i = 0; i < size - 1;i++)
  {
    for(j=0;j< size -1 -i ;j++){
      if(strcmp((*(start+j)).name,(*( start +j+1)).name) > 0){
        swap(start + j,start+j+1);
      }
    }
    }
  }
