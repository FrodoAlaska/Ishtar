#include "isthar.h"

#include <cstdio>

int main() {
  ishtar::LinkedList<int> list;

  list.emplace_back(1);
  list.emplace_back(2);
  list.emplace_back(4);
  list.emplace_back(16);
  list.emplace_back(32);
  list.emplace_at(8, 3); 
  list.emplace_front(0); 

  auto print_node = [](ishtar::Node<int>* node) {
    printf("%i\n", node->value);
  };
  list.for_each(print_node);
 
  printf("\n\n");
  list.remove_at(0);
  list.remove_at(list.count - 1);
  list.remove_at(2);
  list.for_each(print_node);

  printf("\n\n%i\n", list.peek_at(0));

  list.clear();
}
