#include "olivCC.h"

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "Invalid argument for main.");
    return 1;
  }

  // instantiate Vector
  tokenVect = new_vect();
  
  user_input = argv[1];
  tokenizer();
  Node *node = expr(); // parse

  // Debug tokenizer
  /*
  for (i = 0; i < gTokenNum; i++)
    token = (Token *)tokenVect->data[i];
    if (token->ty == TK_NUM)
      fprintf(stderr, "%d\n", token->val);
    else
      fprintf(stderr, "%c\n", token->ty);
  printf("END \n");
  */


  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // Stack machine
  gen(node);

  printf("\tpop rax\n");
  printf("ret\n");
  
  return 0;
}
