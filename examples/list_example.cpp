#include "isthar.h"

#include <cstdio>
#include <string>

void print_node(ishtar::Node<std::string>* node) {
  printf("%s ", node->value.c_str());
}

int main() {
  ishtar::LinkedList<std::string> list("Hello");

  list.emplace_back("there,");
  list.emplace_back("MR");
  list.emplace_back("Johnson");
  
  list.emplace_front("RICKY -");
  list.emplace_front("SCENE 1, INT:");

  list.emplace_at("[SPACE]", list.head, list.head->next);

  // Printing the list
  list.for_each(print_node); 
  printf("\n");

  list.clear();
}
