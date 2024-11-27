#include "markov_chain.h"
#include "linked_list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // For malloc()
#include <stdbool.h> // for bool

void fail_mall();

int get_random_number(int max_number)
//gets random
{
    return rand() % max_number;
}


Node * get_node_rolled(Node *head, int i){
  //gets rolled node
  Node *current = head; // Initialize current
  int counter = 0;
  while (current != NULL)
  {
    if(counter == i){
      return current;
    }
    counter++;
    current = current->next;
  }
  return NULL;
}

bool rolled_end_word(Node *rallied)
{
  //returns true if not end of sentence word, otherwise false
  if (rallied == NULL)
  {
    return false;
  }
  if (rallied->data->is_end)
  {
    return true;
  }
  return false;
}

MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
  //returns a random chosen MarkovNode
  //number of words in LinkedList
  bool ok = true;
  Node * rallied =NULL;
  LinkedList * list_markov = markov_chain -> database;
  int i = get_random_number(markov_chain->database -> size);
  while(ok){
    rallied = get_node_rolled(list_markov->first,i);
    if(rolled_end_word(rallied))
    {
      i = get_random_number(markov_chain->database->size);
    }
    else{
      ok = false;
    }
  }
  return rallied -> data;
}

MarkovNode* get_next_random_node(MarkovNode *cur_markov_node){
  //return random picked word in frequency list of current node
  MarkovNodeFrequency * freq_lst= cur_markov_node -> frequency_list;
  int count_frequency = cur_markov_node -> count_frequency;
  int r;
  r = get_random_number(count_frequency); //random;
  int size = cur_markov_node -> size;
  int counter =0, i;
  //goes through each word in frequency list
  for(i=0;i<size;i++){
      r = r- (freq_lst[i].frequency);
      if(r<0)//found word
      {
        return freq_lst[i].markov_node;
      }
      counter++;
    }
  return NULL;
}


bool data_in_node(Node * check, char *data_ptr){
  //functions which gets data and a node and checks if data in Node
  if(check == NULL){
    return false;
  }
  if(strcmp(check -> data -> data,  data_ptr)== 0){
    return true;
  }
  return false;
}

Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr){
  //if data_ptr in markov chain return it, other wise return NULL
  //first step - get params of markov chain in order to go through it
  Node * first = markov_chain-> database -> first;
  int size =  markov_chain-> database -> size;
  int index = 0;
  //go over database
  while(index<size){
    if(data_in_node(first, data_ptr)){
      return first;
    }
    index++;
    first = first -> next;
  }
  return NULL;
}

bool is_end_sentence(char * word){
  //checks if a words ends with a period
  if(word ==NULL){
    return false;
  }
  unsigned long len_word = strlen(word);
  if(word[len_word - 1] == '.'){
    return true;
  }
  return false;
}


Node* add_to_database(MarkovChain *markov_chain, char *data_ptr){
  //if data in data base return it, other wise add it
  //checks if data in markov chain
  LinkedList * linked_lst = markov_chain-> database;
  Node * in_markov = get_node_from_database(markov_chain,data_ptr);
  if(in_markov == NULL){
    MarkovNode * new_node = malloc(sizeof(MarkovNode));
    MarkovNodeFrequency *temp = NULL;
    if(new_node == NULL){
        fail_mall();
        free(new_node);
        new_node = NULL;
        return NULL;
      }
    new_node ->is_end = false;
    new_node -> data = data_ptr;
    if(is_end_sentence(data_ptr)){
      new_node->is_end = true;
    }
    new_node -> size = 0;
    new_node -> count_frequency = 0;
    new_node -> frequency_list = temp;
    if(!(add(linked_lst, new_node))){
        return markov_chain-> database -> last;
    }
    fail_mall();
    return NULL;
  }
  free(data_ptr);
  data_ptr = NULL;
  return in_markov;
}

bool check_node_frequency(int size, MarkovNodeFrequency *frequency_lst
    , char *data){
  //checks if node in frequency list, if there updates frequency,
  //other wise returns false;
  int index =0;
  while(index<size){
    if(strcmp(frequency_lst[index].markov_node -> data,data) == 0){
      frequency_lst[index].frequency ++;
      return true;
    }
    index++;
  }
  return false;
}

bool add_node_frequency_arr( MarkovNode *first_node,MarkovNode *second_node){
  //add MarkovNode to frequency list and updates frequency number
  int size = first_node -> size;
  size++;
  MarkovNodeFrequency * frequency_lst = first_node->frequency_list;
  MarkovNodeFrequency *temp =
      realloc(frequency_lst,sizeof(MarkovNodeFrequency)*size);
  if(temp==NULL)
  {
    fail_mall();
    return false;
  }
  frequency_lst = temp;
  //add node
  first_node -> size = size;
  frequency_lst[size-1].markov_node = second_node;
  frequency_lst[size-1].frequency = 1;
  first_node -> frequency_list = frequency_lst;
  return true;
}

int add_node_to_frequency_list(MarkovNode *first_node
    , MarkovNode *second_node){
  //function which updates frequency
  MarkovNodeFrequency * frequency_update = first_node -> frequency_list;
  if(first_node == NULL){
    return 0;
  }
  if(first_node -> is_end){
    return 0; //nothing to add
  }
  int size = first_node->size;
  char * data_add = second_node -> data;
  //checks if node in frequency list
  bool node_in_frequency = check_node_frequency
      (size,frequency_update,data_add);
  if(!(node_in_frequency)){
    if(add_node_frequency_arr(first_node,second_node)){
      first_node -> count_frequency +=1;
      return 0;//true- added successfully
    }
    return 1;//false
  }
  first_node -> count_frequency +=1;
  return 0;//true - added successfully
}

void free_database(MarkovChain ** ptr_chain){
  //frees markov chain
  LinkedList *data = (*ptr_chain) -> database;
  Node * it = data -> first;
  Node *temp = NULL;
  // run through list and delete
  while(it!= NULL){
    free(it -> data ->frequency_list); //free frequency list
    free(it-> data->data); // free word
    temp = it ->next;
    free(it->data);//free MarkovNode
    free(it);//free node
    it = temp;
  }
  free(data);//free linkedlist
  free(*ptr_chain); //free chain
}

void generate_tweet(MarkovNode *first_node, int max_length){
  //generates and prints random sentence out of markov_chain
  if(max_length ==1){
    printf("%s\n", first_node -> data);
  }
  else{
    printf("%s ", first_node -> data);
  }
  int counter = 2;
  char * data;
  MarkovNode *temp;
  while(counter<=max_length){
    temp = get_next_random_node(first_node);
    data = temp -> data;
    if(temp -> is_end || counter ==max_length){
      printf("%s\n", data);
      break;
    }
    printf("%s ", data);
    first_node = temp;
    counter++;
  }
}
