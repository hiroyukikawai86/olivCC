#include "olivCC.h"

// @Stack machine implementation
void gen(Node *node) {
  if (node->ty == ND_NUM) {
    printf("\tpush %d\n", node->val);
    return;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("\tpop rdi\n");
  printf("\tpop rax\n");

  switch (node->ty) {
  case '+':
    printf("\tadd rax, rdi\n");
    break;
  case '-':
    printf("\tsub rax, rdi\n");
    break;
  case '*':
    printf("\timul rdi\n");
    break;
  case '/':
    printf("\tcqo\n");
    printf("\tidiv rdi\n");
  }

  printf("\tpush rax\n");
}
