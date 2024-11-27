#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1024 // Define the maximum size of the array
#define ARGS_ERR "The program receives 1 or 4 arguments only.\n"
#define TEST_ERR "Usage: cipher test\n"
#define COMMMAND_ERR "The given command is invalid.\n"
#define SHIFT_ERR "The given shift value is invalid.\n"
#define FILE_ERR "The given file is invalid.\n"
#define CIPHER "cipher"
#define DECIPHER "decipher"
#define HEX 10
#define MAX_ARGS 5
#define MIN_ARGS 2

// Function to read text into array
char* change_to_arr(const char *filename) {
  FILE *file;
  char *content;
  int i = 0;
  char ch;
  // Allocate memory for the array
  content = (char*)malloc(MAX_SIZE * sizeof(char));
  file = fopen(filename, "r");
  // Read the contents of the file and store them in the array
  while ((ch = fgetc(file)) != EOF && i < MAX_SIZE - 1) {
    content[i++] = ch;
  }
  content[i] = '\0'; // Null-terminate the array
  // Close the file
  fclose(file);
  return content;
}

bool check_file_text(const char *filename){
  FILE *file;
  // Open the file for reading
  file = fopen(filename, "w");
  if (file == NULL) {
    fclose(file);
    fprintf(stderr, FILE_ERR);
    return false;
  }
  fclose(file);
  return true;
}

bool check_file_change(const char *filename){
  FILE *file;
  // Open the file for reading
  file = fopen(filename, "r");
  if (file == NULL) {
    fclose(file);
    fprintf(stderr, FILE_ERR);
    return false;
  }
  fclose(file);
  return true;
}

//writes the contents of an array to a text file
void write_to_file(const char *filename, const char *array_content) {
  FILE *file;
  // Open the file for writing
  file = fopen(filename, "w");
  // Write the contents of the array to the file
  fputs(array_content, file);
  // Close the file
  fclose(file);
}

bool validate(const char *filename_open, const char *filename_change, char
k[], char command[])
{
  char *ptr;
  if(strcmp (command, CIPHER) != 0)
  {
    if (strcmp (command, DECIPHER) != 0)
    {
      fprintf (stderr, COMMMAND_ERR);
      return false;
    }
  }
  if(strcmp (k, "0") != 0)
  {
    long ret = strtol (k, &ptr, HEX);
    if (ret == 0)
    {
      fprintf (stderr, SHIFT_ERR);
      return false;
    }
    if (strcmp (ptr, "") != 0)
    {
      fprintf (stderr, SHIFT_ERR);
      return false;
    }
  }
  if (!(check_file_change(filename_change))){
    return false;
  }
  if (!(check_file_text(filename_open))){
    return false;
  }

  return true;
}

void do_all(const char *filename_open, const char *filename_change,char
command[], char k[])
{
  char arr_main[MAX_SIZE];
  strcpy(arr_main, change_to_arr(filename_change));
  long ret = strtol(k, NULL, HEX);
  if (strcmp (command, CIPHER) == 0){
    cipher (arr_main, ret);
  }
  else{
    decipher(arr_main, ret);
  }
  write_to_file(filename_open, arr_main);
}

bool run_tests(){
  if (test_cipher_non_cyclic_lower_case_positive_k ()){
    return false;
  }
  if (!(test_cipher_cyclic_lower_case_special_char_positive_k ())){
    return false;
  }
  if (test_cipher_non_cyclic_lower_case_special_char_negative_k ()){
    return false;
  }
  if(!(test_cipher_cyclic_lower_case_negative_k ())){
    return false;
  }
  if (!(test_cipher_cyclic_upper_case_positive_k ())){
    return false;
  }
  if (test_decipher_non_cyclic_lower_case_positive_k ()){
    return false;
  }
  if (!(test_decipher_cyclic_lower_case_special_char_positive_k ())){
    return false;
  }
  if (test_decipher_non_cyclic_lower_case_special_char_negative_k ()){
    return false;
  }
  if (!(test_decipher_cyclic_lower_case_negative_k ())){
    return false;
  }
  if (!(test_decipher_cyclic_upper_case_positive_k ())){
    return false;
  }
  return true;
}
int main (int argc, char *argv[])
{
  if(argc == MIN_ARGS)
  {
    if(strcmp (argv[1], "test") != 0)
    {
      fprintf (stderr, TEST_ERR);
      return EXIT_FAILURE;
    }
    else
    {
      if(run_tests())
      {

        return EXIT_SUCCESS;
      }
      return EXIT_FAILURE;
    }
  }
  else if (argc == MAX_ARGS)
  {
    if (!validate (argv[4], argv[3], argv[2], argv[1]))
    {
      return EXIT_FAILURE;
    }
    do_all(argv[4], argv[3], argv[1], argv[2]);
    return EXIT_SUCCESS;
  }
  else
  {
    fprintf(stderr, ARGS_ERR);
    return EXIT_FAILURE;
  }
}