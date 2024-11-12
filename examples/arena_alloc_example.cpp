#include "isthar.h"

#include <cstdio>

struct Texture {
  float width, height; 
  int format;
  void* data;
};

int main() {
  ishtar::ArenaAllocater<Texture> texture_allocater(100, sizeof(Texture));
 
  Texture* player_texture = texture_allocater.alloc();
  texture_allocater.free(player_texture);
  printf("%p\n", player_texture);

  printf("ALLOCS = %zu, FREES = %zu\n", texture_allocater.get_alloc_count(), texture_allocater.get_free_count());

  texture_allocater.clear();
}
