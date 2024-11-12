#define ISHTAR_IMPL
#include "isthar.h"

#include <cstdio>
#include <string>

int main() {
  ishtar::HashTable<int, std::string> names(12);

  /// Set section
  names.set(32, "Buddy Guy Jones");
  names.set(83, "Abigail Jack JR.");
  names.set(128, "Salem Yunich Euler");
  names.set(256, "Jackson Free Darnell");
  names.set(512, "Ian Long Bundy");
  names.set(1024, "Randall Axel Jones");
  /// Set section
  
  /// Get section
  printf("##### GET #####\n");
  printf("%s\n", names.get(32).data());
  printf("%s\n", names.get(256).data());
  names.get(2002);
  printf("##### GET #####\n\n");
  /// Get section

  /// Has section
  printf("##### HAS #####\n");
  printf("%i\n", names.has(128));
  printf("%i\n", names.has(8192));
  printf("##### HAS #####\n\n");
  /// Has section
  
  /// Re-set section
  names.set(2002, "RESET NAME CANNOT BE HANDLED"); // This will reset entry number '2002' to a new value
  /// Re-set section
  
  /// Remove section
  printf("##### REMOVE #####\n");
  auto print_entry = [](const int& key, std::string& value) {
    printf("%i - %s\n", key, value.data()); 
  };
  names.remove(32);
  names.for_each(print_entry);
  printf("##### REMOVE #####\n\n");
  /// Remove section

  /// Clear section
  names.clear();
  /// Clear section

  /// An extra example where `resources` map a string id to a resource path
  ishtar::HashTable<ishtar::String8, std::string> resources(128);

  resources.set("player_sprite", "assets/sprites/player_sprite.png");
  resources.set("enemy_sprite", "assets/sprites/enemy1.png");
  resources.set("texture_atlas", "assets/sprites/atlas.png");

  resources.set("player_sprite", "assets/textures/player_texture.jpg");

  printf("%s\n", resources.get("player_sprite").c_str());

  resources.remove("enemy_sprite");

  auto print_resource = [](const ishtar::String8& key, std::string& value) {
    printf("%s - %s\n", key.c_str(), value.data()); 
  };
  resources.for_each(print_resource);

  resources.clear();
  /// An extra example where `resources` map a string id to a resource path
}
