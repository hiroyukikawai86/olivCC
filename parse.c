#include "olivCC.h"

int pos;
Vect *tokenVect;
int gTokenNum;

void tokenizer() {
  char *p = user_input;
  int i = 0;

  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }

    if (*p == '+' || *p == '-' || *p == '*' || *p == '/' ||  *p == '(' || *p == ')') {
      vect_push(tokenVect, addToken(&p, 0));
      i++;
      p++;
      continue;
    }

    if (isdigit(*p)) {
      vect_push( tokenVect, addToken(&p, 1));
      i++;
      continue;
    }
    error_at(p, "Cannot execute tokenizer.");
  }

  gTokenNum = i;
  vect_push(tokenVect, addToken(&p, 2));
}

Token *addToken(char **p, int isNum)
{
  Token *token = malloc(sizeof(Token));

  token->input = *p;
  if (isNum == 1) {
    token->val = strtol(*p, &(*p), 10);
    token->ty = TK_NUM;
  } else if (isNum == 0) {
    token->ty = **p;
  } else {
    token->ty = TK_EOF;
    token->input = *p;
  }
  
  return token;
}

// Node related function
Node *new_node(int ty, Node *lhs, Node *rhs) {
  Node *node = malloc(sizeof(Node));
  node->ty = ty;
  node->lhs = lhs;
  node->rhs = rhs;

  return node;
}

Node *new_node_num(int val) {
  Node *node = malloc(sizeof(Node));
  node->ty = ND_NUM;
  node->val = val;

  return node;
}

int consume(int ty) {
  Token *token = (Token *)tokenVect->data[pos];

  if (token->ty != ty)
    return 0;
  pos++;
  return 1;
}

Node *expr() {
  Node *node = mul();

  for (;;) {
    if (consume('+'))
      node = new_node('+', node, mul());
    else if (consume('-'))
      node = new_node('-', node, mul());
    else
      return node;
  }
}

Node *mul() {
  Node *node = unary();

  for (;;) {
    if (consume('*'))
      node = new_node('*', node, unary());
    else if (consume('/'))
      node = new_node('/', node, unary());
    else
      return node;
  }
}

Node *unary() {
  if (consume('+'))
    return term();
  if (consume('-'))
    return new_node('-', new_node_num(0), term());
  return term();
}


Node *term() {
  Token *token;
  
  if (consume('(')) {
    Node *node = expr();
    if (!consume(')')) {
      token = (Token *)tokenVect->data[pos];
      error_at(token->input,
	       "A corresponding right brace is required....");
    }
      return node;
  }

  token = (Token *)tokenVect->data[pos];
  // otherwise number is coming later on
  if (token->ty == TK_NUM) {
    pos++;
    return new_node_num(token->val);
  }
  error_at(token->input, "Erorr : Neither number nor brace.");
}

