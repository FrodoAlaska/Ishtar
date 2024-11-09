#include "isthar.h"

#include <cstdio>

int main() {
  /// Create section
  printf("### CREATE ###\n");
  ishtar::String8 str1 = "hello";
  ishtar::String8 str2 = ", world";
  printf("%s %s\n", str1.data, str2.data);
  printf("### CREATE ###\n\n");
  /// Create section
  
  /// Copy section
  printf("### COPY ###\n");
  ishtar::String8 copy_str; 
  copy_str.copy(str2);
  printf("%s\n", copy_str.data);
  printf("### COPY ###\n\n");
  /// Copy section

  /// Append section
  printf("### APPEND ###\n");
  str1.append(str2);
  str1.append(" - test ");
  str1.append('K');
  str1.append_at(5, 'O');
  printf("%s, %zu\n", str1.data, str1.length);
  printf("### APPEND ###\n\n");
  /// Append section

  /// Slice section
  printf("### SLICE ###\n");
  ishtar::String8 hello_str = str1.slice(0, ishtar::String8("hello").length - 1);
  printf("%s\n", hello_str.data);
  printf("### SLICE ###\n\n");
  /// Slice section

  /// Compare section
  printf("### COMPARE ###\n");
  printf("%i\n", ishtar::String8("same").compare(ishtar::String8("same")));
  printf("%i\n", ishtar::String8("same").compare(ishtar::String8("NOT THE SAME")));
  printf("%i\n", ishtar::String8("123").compare(ishtar::String8("123")));
  printf("### COMPARE ###\n\n");
  /// Compare section

  /// Reverse section
  printf("### REVERSE ###\n");
  ishtar::String8 palindrome = "racecar :emordnilap";
  palindrome.reverse();
  printf("%s\n", palindrome.data);
  printf("### REVERSE ###\n\n");
  /// Reverse section

  /// Remove section
  printf("### REMOVE ###\n");
  ishtar::String8 incomplete_str = "None of this will be on here... except here";
  incomplete_str.remove(ishtar::String8("None of this will be on here... ").length, incomplete_str.length);
  printf("%s\n", incomplete_str.data);
  printf("### REMOVE ###\n\n");
  /// Remove section

  /// Find section
  printf("### FIND ###\n");
  ishtar::String8 shader = "#type vertex";
  printf("#       = %zu\n", shader.find('#'));
  printf("SPACE   = %zu\n", shader.find(' '));

  ishtar::String8 path = "assets/textures/sprite_player.png";
  printf("PARENT  = %s\n", path.slice(0, path.find_first_of('/')).data);
  printf("FILE    = %s\n", path.slice(path.find_last_of('/') + 1, path.find_last_of('.') - 1).data);
  printf("EXT     = %s\n", path.slice(path.find_last_of('.') + 1, path.length - 1).data);
  printf("NAN     = %zu\n", path.find_first_of('*'));
  printf("### FIND ###\n\n");
  /// Find section

  /// Replace section
  printf("### REPLACE ###\n");
  ishtar::String8 wrong_str = "FUCK";
  wrong_str.replace_at(1, '*');
  wrong_str.replace('K', '*');
  wrong_str.replace_all_of('*', '|');

  printf("CENSOR = %s\n", wrong_str.data);
  printf("### REPLACE ###\n\n");
  /// Replace section

  /// Has section
  printf("### HAS ###\n");
  ishtar::String8 lorem = "Lorem ipsum something something smart$";

  if(lorem.has(' ')) {
    lorem.replace_all_of(' ', 'C');
  }

  if(lorem.has_at(lorem.length - 1, '$')) {
    lorem.reverse();
  }

  printf("%s\n", lorem.data);
  printf("### HAS ###\n\n");
  /// Has section

  /// Fill section
  printf("### FILL ###\n");
  ishtar::String8 all_s;
  all_s.fill(10, 'S');

  printf("%s\n", all_s.data);
  printf("### FILL ###\n");
  /// Fill section

  /// Destroy section
  /// All of the strings have destructors so they should be destroyed after this point
  /// Destroy section
}
