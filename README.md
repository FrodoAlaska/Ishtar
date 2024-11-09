# What Is *Ishtar*? 
*Ishtar* is a single-file suite of tools for C++. It has the basic data structures like dynamic arrays, stacks, queues, hash tables, strings, and even some useful algorithms. 
*No need to build it*. Just a single header file that can be copy and pasted into any project. 
*No overhead*. A minimal use of the standard library is present sure but nothing else.
*And readable, too*. A library that you can actually look at without vomiting? No way! 

# What Does *Ishtar* Use? 
*Ishtar* only uses the standard library to do basic things like memory managment and asserts. Here's _exactly_ the standard libraries that *Ishtar* uses:
- cstdlib (for `malloc`, `free`, and `realloc`)
- cstring (for `memset`)
- casserts (for `assert`)
- cwchar (for `wcslen`)
 
# What Does *Ishtar* Have?
*Ishtar* supports most of the basic data structures:
- Linked Lists
- Stacks 
- Queues 
- Dynamic Arrays
- Strings 
- Hash tables 

# Upcoming Features
- Memory allocaters
- Searching alogrithms (binary search, binary search tree, breadth-first search, depth-first search)
- Sorting algorithms (quick sort, merge sort, bubble sort)
- Trees (Binary, Quad, etc.)
- Extensive documentation

# How To Build? 

# How To Use?
The following code excerpt illustrates how to use the data structure `DynamicArray` in *Ishtar*. It is a very contrived example but it gets the point across, nonetheless. However, if you do wish to know more about the other data structures in *Ishtar* and how they are used, you can go over to the "examples" folder to see more. Otherwise, you can go through the `ishtar.h` file if you'd like and read the documentation since it is somewhat concise.

```c++
#include "ishtar.h"

#include <cstdtio>

int main() {
    // Creating a `DynamicArray` with an initial reserved capacity of 256
    ishtar::DynamicArray<int> arr(256);

    // Adding a new elements into the array 
    arr.append(0);
    arr.append(1);
    arr.append(2);
    arr.append(4);
    // ...

    // You can also pop from the end of the array 
    int last = arr.pop_back();
    int first = arr.pop_front();

    // You can also use a for each loop and pass it a function pointer
    auto print_element_func = [](int& value) {
       printf("%i\n", value); 
    };
    arr.for_each(print_element_func);

    // You can also cut a piece of the array and return a "slice" of it 
    // @NOTE: The slice is taken from `begin` till `end`. Both `begin` and 
    // `end` are _inclusive_.
    DynamicArray<int> arr_piece = arr.slice(0, 2); 

    // A remove operation can also be done on the array. 
    // @NOTE: This does not resize array. Meaning, there isn't any 
    // allocations or de-allocations that happens. The `size` is just 
    // decremented and the elements are shuffled over
    arr.remove(0);

    // This NEEDS to be called if you want to free the underlaying allocated memory 
    arr.clear();
}
```
