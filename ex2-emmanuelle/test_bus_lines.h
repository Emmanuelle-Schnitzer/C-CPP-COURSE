#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H

#include "sort_bus_lines.h"

/**
 * a file which tests if arrays is sorted
 * start - pointer to the beginning of array
 * end - pointer to the end of the array
 */
int is_sorted_by_distance (const BusLine *start, const BusLine *end);

/**
 * checks if an array is sorted by distance values
 * returns 1 if array is sorted, 0 other wise
 */
int is_sorted_by_duration (const BusLine *start, const BusLine *end);

/**
 * checks if an array is sorted by duration values
 * returns 1 if array is sorted, 0 other wise
 */
int is_sorted_by_name (const BusLine *start, const BusLine *end);

/**
 * checks if an array is sorted by name values
 * returns 1 if array is sorted, 0 other wise
 */
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original);
/**
 * checks if two arrays gotten (original and sorted)
 * have the same values
 * returns 1 if have same values, 0 other wise
 */

#endif //EX2_REPO_TESTBUSLINES_H
