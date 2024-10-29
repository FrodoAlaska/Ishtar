#include "isthar.h"

#include <cstdio>
#include <string>

int main() {
  ishtar::LinkedList<std::string> list("Hello");

  list.emplace_back("there,");
  list.emplace_back("MR");
  list.emplace_back("Johnson");
  
  list.emplace_front("RICKY -");
  list.emplace_front("SCENE 1, INT:");

  list.emplace_at("[SPACE]", list.head, list.head->next);

  // Printing the list
  for(auto node = list.head; node != nullptr; node = node->next) {
    printf("%s ", node->value.c_str());
  }
  printf("\n");

  list.clear();
}
