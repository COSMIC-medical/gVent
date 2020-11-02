/*
 * testUtil.c
 *
 * contains the functions necessary for the testing framework
 */

#include "testUtil.h"

static int nb_test = 0;
static int nb_pass = 0;

void test(int (* func)(), char* func_name) {
  if(func()){
    nb_pass ++;
  }
  nb_test ++;
}

int printResult() {
  printf("----------------------------------------------\n");
  printf("%d out of %d tests PASSED\n", nb_pass, nb_test);
  printf("----------------------------------------------\n");

  return nb_pass == nb_test;
}

