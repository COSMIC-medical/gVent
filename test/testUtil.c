/*
 * testUtil.c
 *
 * contains the functions necessary for the testing framework
 */

void test(void (* func)(), char* func_name){
    func();
}

