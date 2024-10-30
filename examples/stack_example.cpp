#include "isthar.h"

#include <cstdio>

void print_node(ishtar::Node<int>* node) {
  printf("CODE = %i\n", node->value);
}

int main() {
  ishtar::Stack<int> server; 
  
  server.emplace(101);
  server.emplace(202);
  server.emplace(303);
  server.emplace(404);

  server.for_each(print_node);

  server.pop();
  server.pop();

  printf("\n\n");
  server.for_each(print_node);
}
