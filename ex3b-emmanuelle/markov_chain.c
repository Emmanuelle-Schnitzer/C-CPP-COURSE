#include "markov_chain.h"
#include "linked_list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // For malloc()
#include <stdbool.h> // for bool


/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
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
    if(markov_chain -> is_last(rallied ->data->data))
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


bool data_in_node(MarkovChain * markov_chain,Node * check, char *data_ptr){
  //functions which gets data and a node and checks if data in Node
  if(!check){
    return false;
  }
  if(markov_chain->comp_func(check -> data -> data,  data_ptr) ==0)
  {
    return true;
  }
  return false;
}

Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr){
  //if data_ptr in markov chain return it, other wise return NULL
  //first step - get params of markov chain in order to go through it
  Node * first = markov_chain-> database -> first;
  int size =  markov_chain-> database -> size;
  int index = 0;
  //go over database
  while(index<size){
    if(data_in_node(markov_chain, first, data_ptr)){
      return first;
    }
    index++;
    first = first -> next;
  }
  return NULL;
}

Node* add_to_database(MarkovChain *markov_chain, void *data_ptr){
  //if data in data base return it, other wise add it
  //checks if data in markov chain
  LinkedList * linked_lst = markov_chain-> database;
  Node * in_markov = NULL;
  if(linked_lst != NULL){
    in_markov = get_node_from_database(markov_chain,data_ptr);
  }
  else{
    linked_lst = malloc(sizeof(LinkedList));
    if(!linked_lst){
      printf(ALLOCATION_ERROR_MASSAGE);
      return NULL;
    }
    linked_lst ->first = NULL;
    linked_lst->last = NULL;
    linked_lst->size = 0;
    markov_chain-> database = linked_lst;
    }
  if(!in_markov){
    void * seperated_word = markov_chain -> copy_func(data_ptr);
    if (!seperated_word) {
      return NULL;
    }
    MarkovNode * new_node = malloc(sizeof(MarkovNode));
    if(!new_node){
      printf(ALLOCATION_ERROR_MASSAGE);
      return NULL;
    }
    MarkovNodeFrequency *temp = NULL;
    new_node -> data = seperated_word;
    new_node -> size = 0;
    new_node -> count_frequency = 0;
    new_node -> frequency_list = temp;
    if(!(add(linked_lst, new_node))){
      return markov_chain-> database -> last;
    }
    free(seperated_word);
    free(new_node);
    printf(ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  data_ptr = NULL;
  return in_markov;
}

bool check_node_frequency(MarkovChain * markov_chain,int size,
                          MarkovNodeFrequency *frequency_lst
    , void *data){
  //checks if node in frequency list, if there updates frequency,
  //other wise returns false;
  int index =0;
  while(index<size){
    if(markov_chain -> comp_func(frequency_lst[index].markov_node
    -> data,data) ==0){
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
  if(!temp)
  {
    printf(ALLOCATION_ERROR_MASSAGE);
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

int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain){
  //function which updates frequency
  MarkovNodeFrequency * frequency_update = first_node -> frequency_list;
  if(markov_chain->is_last(first_node->data)){
    return 0; //nothing to add
  }
  int size = first_node->size;
  void * data_add = second_node -> data;
  //checks if node in frequency list
  bool node_in_frequency = check_node_frequency
      (markov_chain, size,frequency_update,data_add);
  if(!(node_in_frequency)){
    if(add_node_frequency_arr(first_node,second_node)){
      first_node -> count_frequency +=1;
      return 0;//true- added successfully
    }
    free_markov_chain (&markov_chain);
    markov_chain = NULL;
    return 1;//false
  }
  first_node -> count_frequency +=1;
  return 0;//true - added successfully
}

void free_markov_chain(MarkovChain ** ptr_chain){
  //frees markov chain
  LinkedList *data = (*ptr_chain) -> database;
  Node * it = data -> first;
  Node *temp = NULL;
  // run through list and delete
  while(it!= NULL){
    temp = it ->next;
    free(it -> data ->frequency_list);//free frequency list
    it -> data ->frequency_list = NULL;
    (*ptr_chain) -> free_data(it-> data->data);// free word
    it-> data->data = NULL;
    free(it->data);//free MarkovNode
    it->data = NULL;
    free(it);//free node
    it = NULL;
    it = temp;
  }
  free(data);//free linkedlist
  free(*ptr_chain); //free chain
}

void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length){
  //generates and prints random sentence out of markov_chain
  markov_chain -> print_func(first_node -> data);
  if(max_length ==1){
    printf("\n");
  }
  else{
    printf(" ");
  }
  int counter = 2;
  char * data;
  MarkovNode *temp;
  while(counter<=max_length){
    temp = get_next_random_node(first_node);
    data = temp -> data;
    if(markov_chain ->is_last(temp->data) || counter ==max_length){
      markov_chain -> print_func(data);
      printf("\n");
      fflush(stdout);
      break;
    }
    markov_chain -> print_func(data);
    printf(" ");
    first_node = temp;
    counter++;
  }
}
