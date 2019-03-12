#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int WORLD_SIZE = 100;
const int NUM_RULES = 8;

const int RULES_LEN = 8;

const int NUM_ARGS = 2;

const int BLACK = 0;
const int WHITE = 1;

const char BLACK_CHAR = '_';
const char WHITE_CHAR = '*';


// Models -----------------------------------------

int world[WORLD_SIZE];
int rules[NUM_RULES];
char userInputtedRules[RULES_LEN];


// Models (end) -----------------------------------



// Rules ------------------------------------------


int createRules (int argc, char* argv[]) {

  if (argc != 2) {
    printf ("Incorrect number of arguments entered.\n\n");
    return -1;
  }
  memcpy (userInputtedRules, argv[1], strlen (argv[1]));
  printf("Rules are: %s\n", userInputtedRules);
  int i;
  size_t len;
  len = strlen (userInputtedRules);
  printf("Length is: %zu\n", len);
  /* Condition to check if userInputtedRules is valid */
  if (len != RULES_LEN) {
    return -1;
  }
  
  int currRule;
  currRule = atoi (userInputtedRules);
  printf ("currRule is : %d\n", currRule);
  int digit;
  for (i = 0; i < len; i++) {
    digit = currRule % 10;
    printf("digit is: %d\n", digit);
    currRule /= 10;
    if (digit != BLACK && digit != WHITE) {
      return -1;
    }
    rules[i] = digit;
  }
  printf("\n");

  return 0;
}

void initializeWorld () {
  
  int i;
  for (i = 0; i < WORLD_SIZE; i++) {
    world[i] = 0;
  }
  world[95] = 1;

}

/*  Updates the current world by applying the rules to
 *  all cells, using a neighborhood of size 3, and where
 *  the left and right edges wrap around.
 *
 *  @IMPROVE: consider the problem of having to work
 *            with two worlds, so that the current
 *            changes do not overwrite until all cells
 *            are changed - what is the most efficient
 *            way to deal with this?
 */
void updateWorld () {
  
  int rulesIndex;
  int i;

  /* First create copy of world */
  int worldCopy[WORLD_SIZE];
  for (i = 0; i < WORLD_SIZE; i++) {
    worldCopy[i] = world[i];
  }

  /* Left edge cell */
  rulesIndex = (4 * worldCopy[WORLD_SIZE-1]) + (2 * worldCopy[0]) + worldCopy[1];
  world[0] = rules[rulesIndex];

  /* Inner cells */
  for (i = 1; i < WORLD_SIZE-1; i++) {
    rulesIndex = (4 * worldCopy[i-1]) + (2 * worldCopy[i]) + worldCopy[i+1];
    world[i] = rules[rulesIndex];
  }

  /* Right edge cell */
  rulesIndex = (4 * worldCopy[WORLD_SIZE-2]) + (2 * worldCopy[WORLD_SIZE-1]) + worldCopy[0];
  world[WORLD_SIZE-1] = rules[rulesIndex];
}

// Rules (end) -----------------------------------

// I/O ---- --------------------------------------


/*  Print out appropriate symbol depending on whether
 *  this is a BLACK_CHAR or a WHITE_CHAR.
 *  
 * @IMPROVE: Consider more efficient ways to print out
 *           chars, such as using a buffer.
 */
void printCell (int c) {
  if (c == BLACK) {
    printf ("%c", BLACK_CHAR);
  }
  else {
    printf ("%c", WHITE_CHAR);
  }
}



/*  Print out the current, full line of cells (the
 *  CA "world").
 *
 *  @IMPROVE: As above, consider more efficient ways
 *            to print out all chars.
 */
void printWorld () {
  int i;
  for (i = 0; i < WORLD_SIZE; i++) {
    printCell (world[i]);
  }
  printf("\n");
}


// I/O (end) -------------------------------------


int main(int argc, char *argv[]) {

  createRules (argc, argv);
  int i;
  for (i = 0; i < 8; i++) {
    printf("%d ", rules[i]);
  }
  printf("\n");
  initializeWorld ();
  printWorld ();

  for (i = 0; i < 100; i++) {
    updateWorld ();
    (void)usleep (5000);
    printWorld ();
  }

  return 0;

}
