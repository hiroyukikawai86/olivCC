#define _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>

// token representation
enum {
  TK_NUM = 256,
  TK_EQ,        // ==
  TK_NE,        // !=
  TK_LE,        // <=
  TK_GE,        // >=
  TK_EOF,       //
};

typedef struct {
  int ty;
  int val;
  char *input;
} Token;

typedef struct {
  void **data;
  int capacity;
  int length;
} Vect;

// Global variables
extern char *user_input;
extern Vect *tokenVect;
extern int pos;
extern int gTokenNum;


// for tree construction
enum {
  ND_NUM = 256,
};

typedef struct Node {
  int ty;
  struct Node *lhs;
  struct Node *rhs;
  int val;
} Node;

Node *expr();
Node *mul();
Node *unary();
Node *term();
Node *new_node(int, Node*, Node*);
void error_at(char*, char *);
//Token *addToken(char *, int);
Token *addToken(char **, int);
void gen(Node *);
void tokenizer();
Token *addToken(char **, int);
Node *new_node(int, Node *, Node *);
Node *new_node_num(int);
int consume(int);

void gen(Node *);

Vect *new_vect();
void vect_push(Vect *vec, void *elem);
void error(char *, ...);
void error_at(char *loc, char *msg);
int expect(int line, int expected, int actual);
void runtest();

