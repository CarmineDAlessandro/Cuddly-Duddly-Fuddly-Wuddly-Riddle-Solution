#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef enum {undefined = -1, false = 0, true = 1} state;
typedef state*** array_3D;

//Dynamic programming approach. This matrix stores the partial results of the
//computation in order not to compute again the same analyzed sub-tree
array_3D new_undefined_matrix(int red, int purple, int blue) {
  int i, j, k;
  array_3D weights = (state***) malloc(sizeof(state**) * (red + 2));

  for (i = 0; i < red + 2; i ++) {
    weights[i] = (state**) malloc(sizeof(state*) * (purple + 2));
    for (j = 0; j < purple + 2; j ++) {
      weights[i][j] = (state*) malloc(sizeof(state) * (blue + 2));
      for (k = 0; k < blue + 2; k ++) {
        weights[i][j][k] = undefined;
      }
    }
  }

  return weights;
}

void free_weights_matrix(array_3D weights, int red, int purple, int blue) {
  int i, j;

  for (i = 0; i < red + 2; i ++)
    for (j = 0; j < purple + 2; j ++)
      free(weights[i][j]);
    free(weights[i]);
  free(weights);
}

state recursion (int red, int purple, int blue, array_3D weights) {
  state recursive_state = true;

  //Error
  if (red < 0 || purple < 0 || blue < 0) {
    return false;
  }

  //Base step
  if (red == 1 && purple == 0 && blue == 0) {
    return false;
  }
  if (red == 0 && purple == 1 && blue == 0) {
    return false;
  }
  if (red == 0 && purple == 0 && blue == 1) {
    return true;
  }

  //Recursive step
  if (weights[red][purple][blue] == undefined) {
    if (red <= purple && red <= blue && recursive_state == true)
     recursive_state = recursion (red + 1, purple - 1, blue - 1, weights) && recursive_state;

    if (purple <= red && purple <= blue && recursive_state == true)
     recursive_state = recursion (red - 1, purple + 1, blue - 1, weights) && recursive_state;

    if (blue <= red && blue <= purple && recursive_state == true)
     recursive_state = recursion (red - 1, purple - 1, blue + 1, weights) && recursive_state;

    weights[red][purple][blue] = recursive_state;
  }

  return weights[red][purple][blue];
}

int main (int argc, char* argv[]) {
  int red, purple, blue;
  state result;
  array_3D weights;

  //Setting global costraints of the problem
  if (argc == 4) {
    //The input given by the user
    red = strtoumax(argv[1], NULL, 10);
    purple = strtoumax(argv[2], NULL, 10);
    blue = strtoumax(argv[3], NULL, 10);
  } else {
    //The input given by the problem
    red = 43;
    purple = 33;
    blue = 23;
  }
  
  //Running the actual program
  printf("Running the program for input: %d red, %d purple, %d blue\n", red, purple, blue);

  weights = new_undefined_matrix(red + 1, purple, blue);
  result = recursion (red + 1, purple, blue, weights);
  free_weights_matrix(weights, red + 1, purple, blue);
  printf("Adding a red egg: %s\n", result == true ? "correct" : "incorrect");

  weights = new_undefined_matrix(red, purple + 1, blue);
  result = recursion (red, purple + 1, blue, weights);
  free_weights_matrix(weights, red, purple + 1, blue);
  printf("Adding a purple egg: %s\n", result == true ? "correct" : "incorrect");

  weights = new_undefined_matrix(red, purple, blue + 1);
  result = recursion (red, purple, blue + 1, weights);
  free_weights_matrix(weights, red, purple, blue + 1);
  printf("Adding a blue egg: %s\n", result == true ? "correct" : "incorrect");

  return EXIT_SUCCESS;
}
