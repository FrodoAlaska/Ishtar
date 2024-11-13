#define ISHTAR_IMPL
#include "ishtar.h"

#include <cstdio>

struct Texture {
  float width, height; 
  int format;
  void* data;
};

int main() {
  ishtar::ArenaAllocator<Texture> texture_allocater(100, sizeof(Texture));

  /// Alloc section 
  Texture* player_texture = texture_allocater.alloc();
  printf("%p\n", player_texture);
  /// Alloc section 

  /// Free section 
  texture_allocater.free(player_texture);
  /// Free section 
  
  /// Get free/alloc count section 
  printf("ALLOCS = %zu, FREES = %zu\n", texture_allocater.get_alloc_count(), texture_allocater.get_free_count());
  /// Get free/alloc count section 

  /// Clear section 
  texture_allocater.clear();
  /// Clear section 
}
