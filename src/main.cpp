#include "isthar.h"

#include <cstdio>

int main() {
  /// Create section
  printf("### CREATE ###\n");
  ishtar::String8 str1 = ishtar::string_create("hello");
  ishtar::String8 str2 = ishtar::string_create(", world");
  printf("%s %s\n", str1.data, str2.data);
  printf("### CREATE ###\n\n");
  /// Create section
  
  /// Copy section
  printf("### COPY ###\n");
  ishtar::String8 copy_str; 
  ishtar::string_copy(copy_str, str2);
  printf("%s\n", copy_str.data);
  printf("### COPY ###\n\n");
  /// Copy section

  /// Append section
  printf("### APPEND ###\n");
  ishtar::string_append(str1, str2);
  ishtar::string_append(str1, " - test ");
  ishtar::string_append(str1, 'K');
  ishtar::string_append_at(str1, 5, 'O');
  printf("%s, %zu\n", str1.data, str1.length);
  printf("### APPEND ###\n\n");
  /// Append section
  
  /// Slice section
  printf("### SLICE ###\n");
  ishtar::String8 hello_str = ishtar::string_slice(str1, 0, ishtar::string_length("hello") - 1);
  printf("%s\n", hello_str.data);
  printf("### SLICE ###\n\n");
  /// Slice section
  
  /// Compare section
  printf("### COMPARE ###\n");
  printf("%i\n", ishtar::string_compare(ishtar::string_create("same"), ishtar::string_create("same")));
  printf("%i\n", ishtar::string_compare(ishtar::string_create("not the same"), ishtar::string_create("NOT THE SAME")));
  printf("%i\n", ishtar::string_compare(ishtar::string_create("123"), ishtar::string_create("123")));
  printf("### COMPARE ###\n\n");
  /// Compare section
  
  /// Reverse section
  printf("### REVERSE ###\n");
  ishtar::String8 palindrome = ishtar::string_create("racecar :emordnilap");
  ishtar::string_reverse(palindrome);
  printf("%s\n", palindrome.data);
  printf("### REVERSE ###\n\n");
  /// Reverse section
  
  /// Remove section
  printf("### REMOVE ###\n");
  ishtar::String8 incomplete_str = ishtar::string_create("None of this will be on here... except here");
  ishtar::string_remove(incomplete_str, ishtar::string_length("None of this will be on here... "));
  printf("%s\n", incomplete_str.data);
  printf("### REMOVE ###\n\n");
  /// Remove section
  
  /// Find section
  printf("### FIND ###\n");
  ishtar::String8 shader = ishtar::string_create("#type vertex");
  printf("#       = %zu\n", ishtar::string_find(shader, '#'));
  printf("SPACE   = %zu\n", ishtar::string_find(shader, ' '));

  ishtar::String8 path = ishtar::string_create("assets/textures/sprite_player.png");
  printf("PARENT  = %s\n", ishtar::string_slice(path, 0, ishtar::string_find_first_of(path, '/')).data);
  printf("FILE    = %s\n", ishtar::string_slice(path, ishtar::string_find_last_of(path, '/') + 1, ishtar::string_find_last_of(path, '.') - 1).data);
  printf("EXT     = %s\n", ishtar::string_slice(path, ishtar::string_find_last_of(path, '.') + 1, path.length - 1).data);
  printf("NAN     = %zu\n", ishtar::string_find_first_of(path, '*'));
  printf("### FIND ###\n\n");
  /// Find section
  
  /// Replace section
  printf("### REPLACE ###\n");
  ishtar::String8 wrong_str = ishtar::string_create("FUCK");
  ishtar::string_replace_at(wrong_str, 1, '*');
  ishtar::string_replace(wrong_str, 'K', '*');
  ishtar::string_replace_all_of(wrong_str, '*', '|');

  printf("CENSOR = %s\n", wrong_str.data);
  printf("### REPLACE ###\n\n");
  /// Replace section
  
  /// Has section
  printf("### HAS ###\n");
  ishtar::String8 lorem = ishtar::string_create("Lorem ipsum something something smart$");

  if(ishtar::string_has(lorem, ' ')) {
    ishtar::string_replace_all_of(lorem, ' ', 'C');
  }
  
  if(ishtar::string_has_at(lorem, lorem.length - 1, '$')) {
    ishtar::string_reverse(lorem);
  }

  printf("%s\n", lorem.data);
  printf("### HAS ###\n\n");
  /// Has section
  
  /// Fill section
  printf("### FILL ###\n");
  ishtar::String8 all_s;
  ishtar::string_fill(all_s, 10, 'S');

  printf("%s\n", all_s.data);
  printf("### FILL ###\n");
  /// Fill section
  
  /// Destroy section
  ishtar::string_destroy(hello_str);
  ishtar::string_destroy(str1);
  ishtar::string_destroy(str2);
  /// Destroy section
}
