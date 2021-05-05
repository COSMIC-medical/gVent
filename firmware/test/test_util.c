/*
 * test_util.c
 *
 * contains the functions necessary for the testing framework
 */

#include "test_util.h"

static int nb_test = 0;
static int nb_pass = 0;

void test(int (* func)(), char* func_name) {
  if(func()){
    nb_pass ++;
  }
  nb_test ++;
}

int print_result() {
  printf("----------------------------------------------\n");
  printf("%d out of %d tests PASSED\n", nb_pass, nb_test);
  printf("----------------------------------------------\n");

  return nb_pass == nb_test;
}

