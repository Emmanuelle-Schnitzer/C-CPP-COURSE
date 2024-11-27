#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define DEX 10
#define NUM_OF_TRANSITIONS 20

#define NUM_ARGS_ERROR "Usage: invalid number of arguments"

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in case
    // there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in
    // case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
int handle_error_snakes(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_markov_chain(database);
    }
    return EXIT_FAILURE;
}


int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error_snakes(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int fill_database_snakes(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain,
                                             cells[index_to])->data;
            add_node_to_frequency_list(from_node, to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain,
                                                 cells[index_to])->data;
                int  res = add_node_to_frequency_list(from_node, to_node,
                                                      markov_chain);
                if(res==EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

int compare_cells(const void* cell1,const void * cell2){
  //a generic function which compares two cells
    return (((Cell *)cell1) -> number - ((Cell *)cell2) -> number);
}


void free_cell(void * cell){
  // a pointer to a function that gets a pointer of generic data type and
  // frees it.
  free((Cell *)cell);
}

void print_data_cell(const void * cell){
  //a function which receives a string and prints it
  if(((Cell *)cell) -> number == BOARD_SIZE){
    printf("%s%d%s", "[",((Cell *)cell) -> number, "]");
  }
  else{
    if(((Cell *)cell) -> ladder_to == EMPTY && ((Cell *)cell) -> snake_to ==
    EMPTY){
      printf ("%s%d%s", "[", ((Cell *) cell)->number, "] ->");
    }
    else if(((Cell *)cell) -> ladder_to != EMPTY){
      printf ("%s%d%s", "[", ((Cell *) cell)->number, "] -ladder to->");
    }
    else{
      printf ("%s%d%s", "[", ((Cell *) cell)->number, "] -snake to->");
    }
  }
}

void * copy_cell(const void * cell){
  // a pointer to a function that  gets a pointer of generic
  // data type and returns a newly allocated copy of it
  // returns a generic pointer.
  if(!cell){
    return NULL;
  }
  Cell * new_cell = (Cell *)malloc(sizeof(Cell));
  if(!new_cell){
    printf(ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  new_cell -> number = ((Cell *)cell) -> number;
  new_cell -> ladder_to = ((Cell *)cell) -> ladder_to;
  new_cell -> snake_to = ((Cell *)cell) -> snake_to;
  return new_cell;
}

bool last_cell(const void * cell){
  //  a pointer to function that gets a pointer of generic data type and
  //  returns
  // true if last word, false otherwise
  if(((Cell *)cell) -> number == BOARD_SIZE){
    return true;
  }
  return false;
}


bool fill_param_chain(MarkovChain * markov_chain)
{
  //fills parameters in struct markov_chain

  markov_chain->print_func = print_data_cell;
  markov_chain->comp_func = compare_cells;
  markov_chain->free_data = free_cell;
  markov_chain->copy_func = copy_cell;
  markov_chain->is_last = last_cell;
  markov_chain->database = NULL;
  if (fill_database_snakes (markov_chain))
  {
    return false;
  }
  return true;
}

bool run_game(int num_sentences){
  MarkovChain * markov_chain = NULL;
  MarkovChain * temp = malloc(sizeof(MarkovChain));
  if(!temp){
    printf(ALLOCATION_ERROR_MASSAGE);
    return false;
  }
  markov_chain = temp;
  fill_param_chain(markov_chain);
  int counter =1;
  while(counter<=num_sentences){
    printf("%s %d%s ", "Random Walk",counter, ":");//for each tweet
    generate_random_sequence(markov_chain,markov_chain -> database ->
    first -> data,MAX_GENERATION_LENGTH);
    counter++;
  }
  free_markov_chain (&markov_chain);
  return true;
}
/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf(NUM_ARGS_ERROR);
    return EXIT_FAILURE;
  }
  unsigned int seed = strtol(argv[1], NULL, DEX);
  srand(seed);
  int num_sentences;
  num_sentences = strtol(argv[2], NULL, DEX);
  if(!(run_game(num_sentences))){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
