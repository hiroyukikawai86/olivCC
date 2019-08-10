#include "olivCC.h"

char *user_input;

// Vector implementation
Vect *new_vect() {
  Vect *vec = malloc(sizeof(Vect));
  vec->data = malloc(sizeof(void *) * 16);
  vec->capacity = 16;
  vec->length = 0;
  return vec;
}

void vect_push(Vect *vec, void *elem) {
  if (vec->capacity == vec->length) {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, sizeof(void *) * vec->capacity);
  }
  vec->data [vec->length++] = elem;
}

// @Error reporting function
void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

void error_at(char *loc, char *msg) {
  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, "");
  fprintf(stderr, "^ %s\n", msg);
  exit(1);
}

// Unit test code
int expect(int line, int expected, int actual) {
  if (expected == actual)
    return 0;
  fprintf(stderr, "%d: %d expected, but got %d\n", line, expected, actual);
  exit(1);
}

void runtest() {
  Vect *vec = new_vect();
  expect(__LINE__, 0, vec->length);

  for (int i = 0; i < 100; i++)
    vect_push(vec, (void *)(intptr_t)i);

  expect(__LINE__, 0, (long)vec->data[0]);
  expect(__LINE__, 0, (long)vec->data[50]);
  expect(__LINE__, 0, (long)vec->data[99]);
  
  printf("OK\n");
}

