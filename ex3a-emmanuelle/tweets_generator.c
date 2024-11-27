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
  if (file == NULL) {
    printf(FILE_PATH_ERROR);
    return false;
    }
    fclose(file);
    return true;
  }

void fail_mall(){
  printf(ALLOCATION_ERROR_MASSAGE);
}


Node * add_node(MarkovChain * main_chain, char* word)
{
  //add word to database
  Node * new_node;
  char *seperated_word = (char *)malloc(strlen(word) + 1);
  if (seperated_word == NULL) {
    // Memory allocation failed
    fail_mall();
    return NULL;
  }
  strcpy(seperated_word, word);
  new_node = add_to_database(main_chain, seperated_word);
  if(new_node == NULL){
    free(seperated_word);
    seperated_word = NULL;
    return NULL;//unsuccessfully added
  }
  return new_node;
}

MarkovChain * make_new_chain(int words_to_read)
{
  //make a new LinkedList
  if(words_to_read==-1){
    words_to_read = WORDS_READ;
  }
  MarkovChain * main_chain = malloc(sizeof(MarkovChain));
  if(main_chain ==NULL){
    fail_mall();
    free_database(&main_chain);
    return NULL;
  }
  LinkedList *list = malloc(sizeof(LinkedList));
  if (list == NULL) {
    fail_mall();
    free_database(&main_chain);
    return NULL;
  }
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  main_chain -> database = list;
  return main_chain;
}

bool update_frequency(Node * new_node,Node * last_node)
{
  //function which updates frequency of word, and adds new word
  //to frequency list
  if(last_node == NULL){
    return true;//first round dont go in
  }
  if(!(add_node_to_frequency_list(last_node -> data,new_node -> data))){
    return true;
  }
  return false;
}

void free_all_data(MarkovChain **markov_chain){
  //couldn't fill database
  free_database (markov_chain);
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
        if (new_node == NULL){
          free_all_data(&markov_chain);
          return 1;
        }
        if (!(update_frequency (new_node, last_node))){
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
    free_database (&main_chain);
    return false;
  }
  fclose(fp);
  while(counter<=num_tzi){
    MarkovNode *first_word = get_first_random_node(main_chain);
    printf("%s %d%s ", "Tweet",counter, ":");//for each tweet
    generate_tweet(first_word,MAX_NUM_WORDS);
    counter++;
  }
  free_database (&main_chain);
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
