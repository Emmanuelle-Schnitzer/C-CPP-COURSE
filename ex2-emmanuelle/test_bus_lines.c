#include "test_bus_lines.h"
#include "sort_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//implements functions in test_bus_lines.h. Sorts arrays and called
// from main

int is_sorted_by_distance (const BusLine *start, const BusLine *end){
  //checks is two arrays are sorted by distance.
  //returns true if sorted and false otherwise
  int size = end-start;
  int i;
  bool ok = true, test2= true;
  BusLine * line_info = malloc(size * sizeof(BusLine));
  // checks if malloc succeeded
  if ((line_info) == NULL){
    return EXIT_FAILURE;
  }
  // copying array
  memcpy(line_info, start, size);
  for(i=0;i<size-1;i++){
    if((line_info[i].distance) > (line_info[i+1].distance)){
      fprintf(stdout, "TEST 1 FAILED: array isn't sorted by distance\n");
      ok = false;
      break;
    }
  }
  if(ok){
    fprintf(stdout, "TEST 1 PASSED: array is sorted\n");
  }
  if(!(is_equal(line_info,line_info+size,start, end))){
    fprintf(stdout, "TEST 2 FAILED: arrays dont have same parameters\n");
    test2 = false;
  }
  if(test2){
    fprintf(stdout, "TEST 2 PASSED: arrays have same parameters\n");
  }
  free(line_info);
  line_info = NULL;
  if(ok){
    return 1; //true
  }
  return 0;
}
int is_sorted_by_duration (const BusLine *start, const BusLine *end){
  //checks is two arrays are sorted by duration.
  //returns true if sorted and false otherwise
  int size = end-start;
  int i;
  bool ok = true, test2= true;
  BusLine * line_info = malloc(size * sizeof(BusLine));
  if ((line_info) == NULL){
    return EXIT_FAILURE;
  }
  // copying array
  memcpy(line_info, start, size);
  for(i=0;i<size-1;i++){
    if((line_info[i].duration) > (line_info[i+1].duration)){
      fprintf(stdout, "TEST 3 FAILED: array isn't sorted by duration\n");
      ok = false;
      break;
    }
  }
  if(ok){
    fprintf(stdout, "TEST 3 PASSED: array is sorted\n");
  }
  if(!(is_equal(line_info,line_info+size,start, end))){
    fprintf(stdout, "TEST 4 FAILED: arrays dont have same parameters\n");
    test2 = false;
  }
  if(test2){
    fprintf(stdout, "TEST 4 PASSED: arrays have same parameters\n");
  }
  free(line_info);
  line_info = NULL;
  if(ok){
    return 1; //true
  }
  return 0;
}
int is_sorted_by_name (const BusLine *start, const BusLine *end)
{
  //checks is two arrays are sorted by name.
  //returns true if sorted and false otherwise
  int size = end - start;
  int i;
  bool ok = true, test2 = true;
  BusLine *line_info = malloc (size * sizeof (BusLine));
  if ((line_info) == NULL)
  {
    return EXIT_FAILURE;
  }
  // copying array
  memcpy(line_info, start, size);
  for (i = 0; i < size - 1; i++)
  {
    if((line_info+i)->name > (line_info+i+1) ->name)
    {
      fprintf (stdout, "TEST 5 FAILED: array isn't sorted by name\n");
      ok = false;
      break;
    }
  }
  if (ok)
  {
    fprintf (stdout, "TEST 5 PASSED: array is sorted\n");
  }
  if (!(is_equal (line_info, line_info + size, start, end)))
  {
    fprintf (stdout, "TEST 6 FAILED: arrays dont have same parameters\n");
    test2 = false;
  }
  if (test2)
  {
    fprintf (stdout, "TEST 6 PASSED: arrays have same parameters\n");
  }
  free (line_info);
  line_info = NULL;
  if (ok)
  {
    return 1; //true
  }
  return 0;
}

int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original)
              {
  //checks is two arrays have same parameters-
  //if they hold the same names, and their sizes are the same
  if((end_sorted-start_sorted)!=(end_original-start_original)){
    return 0;
  }
  int size = start_original-end_original;
  int j;
  bool ok = false;
  for(long long i =0;i<size;i++){
    for(j=0;j<size;j++)
    {
      if (strcmp((*(start_sorted + i)).name, (*(start_original + j)).name)
          == 0)
      {
        ok = true;
      }
    }
      if (!ok){
        return 0;
      }
  }
  return 1;
}