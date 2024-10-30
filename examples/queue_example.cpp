#include "isthar.h"

#include <cstdio>

enum EventType {
  EVENT_KEY_PRESSED    = 8,
  EVENT_KEY_RELEASED   = 16,
  EVENT_APP_QUIT       = 32,
  EVENT_WINDOW_RESIZED = 64,
};

void print_node(ishtar::Node<EventType>* node) {
  printf("EVENT = %i\n", node->value);
}

int main() {
  ishtar::Queue<EventType> event_queue;

  event_queue.emplace(EVENT_KEY_PRESSED);
  event_queue.emplace(EVENT_KEY_RELEASED);
  event_queue.emplace(EVENT_APP_QUIT);
  event_queue.emplace(EVENT_WINDOW_RESIZED);

  event_queue.for_each(print_node);

  event_queue.pop();
  event_queue.pop();
 
  printf("\n\n");
  event_queue.for_each(print_node);
}
