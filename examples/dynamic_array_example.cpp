#define ISHTAR_IMPL
#include "isthar.h"

#include <cstdio>

int main() {
  ishtar::DynamicArray<int> arr;
  arr.reserve(50); // Reserves 50 elements in the array

  /// Append section
  /////////////////////////////////////////
  printf("APPEND SECTION\n");
  arr.append(0);
  arr.append(1);
  arr.append(2);
  arr.append(4);
  arr.append(8);
  arr.append(16);
  arr.append(32);
  arr.append(64);
  arr.append(128);
  arr.append(256);

  auto lam = [](int& value, const ishtar::sizei index) {
    printf("%i\n", value); 
  };
  arr.for_each(lam);
  printf("APPEND SECTION\n\n");
  /////////////////////////////////////////

  /// Size/capacity section
  /////////////////////////////////////////
  printf("SIZE/CAPACITY SECTION\n");
  printf("SIZE = %zu\n", arr.size);
  printf("CAP  = %zu\n", arr.capacity);
  printf("SIZE/CAPACITY SECTION\n\n");
  /////////////////////////////////////////
 
  /// Index section
  /////////////////////////////////////////
  printf("INDEX SECTION\n");
  int a10 = arr[9];
  // int a50 = arr[50]; // <- index out of bounds error
  printf("10th = %i\n", a10);
  printf("INDEX SECTION\n\n");
  /////////////////////////////////////////
  
  /// Slice section
  /////////////////////////////////////////
  printf("SLICE SECTION\n");
  ishtar::DynamicArray<int> copy_arr = arr.slice(5, 9);
  copy_arr.for_each(lam); 

  printf("SLICE SECTION\n\n");
  /////////////////////////////////////////
 
  /// Pop section
  /////////////////////////////////////////
  printf("POP SECTION\n");
  arr.pop_back();
  arr.pop_back();

  arr.pop_front();
  arr.pop_front();
  arr.pop_front();

  arr.for_each(lam);
  printf("SIZE = %zu\n", arr.size);
  printf("POP SECTION\n\n");
  /////////////////////////////////////////
 
  /// Peek section
  /////////////////////////////////////////
  printf("PEEK SECTION\n");
  printf("FRONT = %i\n", arr.peek_front());
  printf("BACK = %i\n", arr.peek_back());
  printf("PEEK SECTION\n\n");
  /////////////////////////////////////////
  
  // Remove section
  /////////////////////////////////////////
  printf("Remove SECTION\n");
  arr.remove(2);
  arr.remove(1);
  arr.for_each(lam);
  printf("Remove SECTION\n\n");
  /////////////////////////////////////////
  
  /// Fill section
  /////////////////////////////////////////
  printf("FILL SECTION\n");
  ishtar::DynamicArray<int> int_arr;
  int_arr.fill(10, 32);
  int_arr.for_each(lam);
  printf("FILL SECTION\n\n");
  /////////////////////////////////////////

  /// Clear section
  /////////////////////////////////////////
  printf("CLEAR SECTION\n");
  arr.clear();
  
  // Status after clearing the array
  printf("SIZE = %zu\n", arr.size);
  printf("CAP  = %zu\n", arr.capacity);
  
  printf("CLEAR SECTION\n\n");
  /////////////////////////////////////////
}
