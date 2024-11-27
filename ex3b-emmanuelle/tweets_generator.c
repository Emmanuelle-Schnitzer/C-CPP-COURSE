#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "markov_chain.h"
#include <linked_list.h>
#include <string.h>

#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"

#define DELIMITERS " \n\t\r"
# define MIN_ARGS 4
#define MAX_ARGS 5
#define DEX 10
#define MAX_LINE_LEN 1000
#define MAX_NUM_WORDS 20
#define WORDS_READ 20
#define MAX_ARGS 5


bool validate_file(const char *filename){
  //validates file gotten
  FILE *file;
  // Open the file for reading
  file = fopen(filename, "r");
  if (!file) {
    printf(FILE_PATH_ERROR);
    return false;
  }
  fclose(file);
  return true;
}


Node * add_node(MarkovChain * main_chain, char* word)
{
  //add word to database
  return add_to_database(main_chain, word);
}

int compare_word(const void* word1,const void * word2){
  //a generic function which compares two words
  const char * str1 = (char *)(word1);
  const char * str2 = (char *)(word2);
  return strcmp(str1,str2);
}

void free_word(void * word){
  // a pointer to a function that gets a pointer of
  // generic data type and frees it.
  free((char *)word);
}

void print_word(const void * str){
  //a function which receives a string and prints it
  printf("%s", (char *)(str));
}

void * copy_word(const void * word){
  // a pointer to a function that  gets a pointer of generic data type
  // and returns a newly allocated copy of it
  // returns a generic pointer.
  if(!word){
    return NULL;
  }
  const char * str = (char *) word;
  size_t str_len = strlen(word);
  char * new_word = (char *) malloc(str_len+1);
  if(new_word == NULL){
    printf(ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  strcpy(new_word,str);
  return new_word;
}

bool last_word(const void * str){
  //  a pointer to function that gets a pointer of generic data type and
  // returns true if last word, false otherwise
  if(!str){
    return false;
  }
  const char * word = (char*)str;
  if(word[strlen(word) - 1] == '.'){
    return true;
  }
  return false;
}

MarkovChain * make_new_chain(int words_to_read)
{
  //make a new LinkedList
  if(words_to_read==-1){
    words_to_read = WORDS_READ;
  }
  MarkovChain * main_chain = malloc(sizeof(MarkovChain));
  if(!main_chain){
    printf(ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  main_chain -> print_func = print_word;
  main_chain -> comp_func = compare_word;
  main_chain -> free_data = free_word;
  main_chain -> copy_func = copy_word;
  main_chain -> is_last = last_word;
  main_chain -> database = NULL;
  return main_chain;
}

bool update_frequency(MarkovChain * markov_chain, Node * new_node,Node *
last_node)
{
  //function which updates frequency of word, and adds new word
  //to frequency list
  if(!last_node){
    return true;//first round dont go in
  }
  if(!(add_node_to_frequency_list(last_node -> data,new_node ->
  data, markov_chain))){
    return true;
  }
  return false;
}

void free_all_data(MarkovChain **markov_chain){
  //couldn't fill database
  free_markov_chain (markov_chain);
  markov_chain = NULL;
}

int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain){
  char line[MAX_LINE_LEN];
  int word_count = 0;
  bool ok = false;///read all file
  if(words_to_read == -1){
    ok = true;
    words_to_read = 1;
  }
  Node * new_node;
  Node * last_node = NULL;
  char * seperated_word;
  //read file
  while ((fgets (line, MAX_LINE_LEN, fp) != NULL) && word_count<words_to_read){
    char *temp = strtok(line, DELIMITERS);
    seperated_word = temp;//separates words from
    // unwanted chars
    while (seperated_word != NULL && word_count < words_to_read){
      new_node = add_node (markov_chain, seperated_word);
      if (!new_node){
        free_all_data(&markov_chain);
        return 1;
      }
      if (!(update_frequency (markov_chain, new_node, last_node))){
        free_all_data(&markov_chain);
        return 1;
      }
      if (ok){
        words_to_read++;//insures word_count is always smaller
      }
      word_count++;
      last_node = new_node;
      seperated_word = strtok (NULL, DELIMITERS);
      // Get the next word
    }
  }
  return 0;//filled database successfully
}
bool run_function(int num_tzi,const char * path,
                  int num_words){
  int counter = 1;
  MarkovChain * main_chain = make_new_chain(num_words);
  FILE *fp = fopen(path, "r");//already checked that valid
  if(fill_database(fp, num_words, main_chain)){
    free_markov_chain (&main_chain);
    return false;
  }
  fclose(fp);
  while(counter<=num_tzi){
    MarkovNode *first_word = get_first_random_node(main_chain);
    printf("%s %d%s ", "Tweet",counter, ":");//for each tweet
    generate_random_sequence(main_chain,first_word,MAX_NUM_WORDS);
    counter++;
  }
  free_markov_chain (&main_chain);
  return true;
}

int main (int argc, char *argv[])
{
  if (argc < MIN_ARGS || argc > MAX_ARGS)
  {
    printf(NUM_ARGS_ERROR);
    return EXIT_FAILURE;
  }
  int num_words = -1;
  unsigned int seed = strtol(argv[1], NULL, DEX);
  srand(seed);
  int num_tzi = strtol(argv[2], NULL, DEX);
  const char * path = argv[3];
  if(!(validate_file(path)))
  {
    return EXIT_FAILURE;
  }
  if(argc == MAX_ARGS){
    num_words = strtol(argv[4], NULL, DEX);
  }
  if(!(run_function(num_tzi,path,num_words))){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

}
