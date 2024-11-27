#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h> /* for INT_MIN, INT_MAX */

#define MIN_ARGS 2
#define READ_LEN  61
#define HEX 10
#define MAX_NUM 1000
#define MIN_NUM 10
#define MAX_NUM_DUR 100
#define LEN_ARR 21

bool validate_args(char command[]){
  // checks if command gotten is a valid command
  if (strcmp (command, "by_duration") != 0){
    if (strcmp (command, "by_distance") != 0){
      if (strcmp (command, "by_name") != 0){
        if (strcmp (command, "test") != 0){
          fprintf(stdout, "Usage: command not valid\n");
          return false;
        }
      }
    }
  }
  return true;
}

void run_tests(BusLine*start, BusLine*end)
{
  //function which runs all tests in test_bus_lines
  is_sorted_by_distance (start, end);
  is_sorted_by_duration (start, end);
  is_sorted_by_name (start, end);
}

long get_num_lines(){
  // receives from user num lines and returns
  long num;
  int i;
  bool ok = true, returned_false = true;
  char buffer[sizeof(int)];
  while(ok){
    fprintf(stdout,"Enter number of lines. Then enter\n");
    if (fgets(buffer, READ_LEN, stdin) == NULL){
      fprintf(stdout,"Error: Nothing was put in\n");
    }
    num = strtol(buffer,NULL,HEX);
    //checks if number is valid
    for (i = 0; (buffer[i] != '\0') && (buffer[i] != '\n') ; i++)
    {
      if (!(isdigit(buffer[i])))
      {
        if(returned_false){
          fprintf (stdout, "Error: An invalid value was put in\n");
          memset(buffer, 0, sizeof(int));
        }
        returned_false = false;
      }
    }
    if(buffer[0]=='0'){
      fprintf (stdout, "Error: An invalid value was put in\n");
      returned_false = false;
    }
    if(returned_false){
      ok = false;
    }
    returned_false = true;

    }
  return num;
}

bool check_all_params(char name[], char* distance, char * duration){
  //checks validation of each value of line information
  long size_name = strlen(name);
  long i;
  char * ptr;
  long num, num_duration;
  for(i=0;i<size_name;i++)
  {
    // checks that name of line is valid
    if(!(isdigit(name[i]))){
      if(!((name[i]<='z')&&(name[i]>='a'))){
        fprintf(stdout,"Error: name of line needs to be with integers and "
                       "small letters\n");
        return false;
      }
    }
  }
  num = strtol(distance,&ptr,HEX);
  if ((*ptr != '\0') && (*ptr != '\n')) {
    fprintf(stdout,"Error: distance needs to be integer\n");
    return false;
  }
  //checks that distance is valid:
  if((num<0) || (num > MAX_NUM)){
    fprintf(stdout,"Error: distance needs to be a number between 0 and "
                   "1000\n");
    return false;
  }
  num_duration = strtol(duration,NULL,HEX);
  //checks that duration is valid
  if((num_duration<MIN_NUM) || (num_duration >MAX_NUM_DUR)){
    fprintf(stdout,"Error: duration needs to be a number between 10 and "
                   "100\n");
    return false;
  }
  return true;
}

BusLine * get_line_info(int num_lines){
  //gets line information and returns
  // restart array to the number of lines gotten
  BusLine * line_info = malloc(num_lines * sizeof(BusLine));
  if ((line_info) == NULL){
    return NULL;
  }
  bool ok = true;
  char buffer[READ_LEN];
  char name[LEN_ARR];
  char distance[LEN_ARR];
  char duration[LEN_ARR];
  for(int i = 0;i<num_lines;i++)
  {
    while (ok)
    {
      fprintf(stdout,"Enter line info. Then enter\n");
      if (fgets (buffer, READ_LEN, stdin) == NULL)
      {
        fprintf (stdout, "Nothing was put in\n");
      }
      else
      {
        sscanf (buffer, "%[^,],%[^,],%[^,]", name, distance, duration);
        if (check_all_params (name, distance, duration))
        {
          ok = false;
        }
        }
      }

    ok = true;
    // makes each busline in the array of bus lines
    strncpy(line_info[i].name, name, sizeof(line_info[i].name) - 1);
    int num_dis = strtol(distance,NULL,HEX);
    int num_dur = strtol(duration,NULL,HEX);
    line_info[i].distance = num_dis;
    line_info[i].duration = num_dur;
  }
  return line_info;
}
void print_arr(BusLine * line_info, int size){
  //prints sorted array and frees array started by malloc
  for(int i = 0; i<size;i++){
    fprintf(stdout,"%s,%d,%d\n", (*(line_info + i)).name, (*(line_info + i))
    .distance, (*(line_info + i)).duration);
  }
  free(line_info);
  line_info = NULL;
}

int main (int argc, char *argv[])
{
  if (argc != MIN_ARGS)
  {
    fprintf (stdout, "Usage: User needs to chose between four options.\n");
    return EXIT_FAILURE;
  }
  else
  {
    // validates args given, if not valid prints informative message
    if (validate_args (argv[1]))
    {
      // start program
      long num_lines = get_num_lines ();
      //makes array with line information - this will
      //be the main array
      BusLine *line_info = get_line_info (num_lines);
      if(line_info == NULL){
        return EXIT_FAILURE;
      }
      if ((strcmp (argv[1], "test") == 0))
      {
        //runs tests
        run_tests(line_info,line_info +num_lines);
        return EXIT_SUCCESS;
      }
      else
      {
        if (strcmp (argv[1], "by_name") == 0)
        {
          bubble_sort(line_info, line_info + num_lines);
        }
        else if (strcmp (argv[1], "by_distance") == 0)
        {
          quick_sort(line_info, line_info + num_lines, DISTANCE);
        }
        else
        {
          quick_sort(line_info, line_info + num_lines, DURATION);
        }
      }
      print_arr(line_info, num_lines);
      return EXIT_SUCCESS;
    }
  }

}