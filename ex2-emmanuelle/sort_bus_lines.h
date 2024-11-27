#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H

#include <string.h>
#define NAME_LEN 21
/**
 *typedef of BusLine enum of SortType
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
  * functions which sort array
 * Quick sort is used to sort arrays by distance and
 * by duration and Bubble sort is used to sort
 * arrays by name
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * uses bubble sort algorithm in order to sort
 * array according to name of lines
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * uses quick_sort algorithm in order to sort
 * array according to duration and distance of lines
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
/**
 *helper to function quick_sort, returns pivot and sorts array
 */
#endif //EX2_REPO_SORTBUSLINES_H
