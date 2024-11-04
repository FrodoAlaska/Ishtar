#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>

namespace ishtar { // Start of ishtar

////////////////////////////////////////////////////////////////////

/// Typedefs 

// Char 
typedef char   i8; 

// Short
typedef short  i16;

// int
typedef int    i32; 

// long
typedef long   i64; 

// unsigned char
typedef unsigned char  u8;

// unsigned short
typedef unsigned short u16;

// unsigned int
typedef unsigned int   u32;

// unsigned long
typedef unsigned long  u64;

// size_t
typedef u64 sizei;

/// Typedefs 

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// Defines 

// Underflowing a `sizei` type to get a "non position" which can indicate 
// a string error
#define STRING_NPOS ((sizei)-1)

/// Defines 

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// Node 
template<typename T>
class Node {
  public:
    Node() = default;
    Node(const T& val, Node<T>* next = nullptr, Node<T>* previous = nullptr) {
      value          = val; 
      this->next     = next;
      this->previous = previous;
    }

  public:
    typedef void(*ForEachFn)(Node<T>* node);

  public:
    T value; 
    Node<T>* next;
    Node<T>* previous;
};
/// Node

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// LinedList 
template<typename T> 
class LinkedList {
  public:
    LinkedList(Node<T>* head = nullptr) {
      this->head = head; 
      tail       = nullptr;
      count      = head != nullptr ? 1 : 0;
    }
    
    LinkedList(const T& val) {
      head  = new Node<T>(val); 
      tail  = nullptr;
      count = 1;
    }

  public:
    Node<T>* get_at(const sizei index) {
      assert(index >= 0 && index < count);

      Node<T>* node = head;
      for(sizei i = 0; node && i < count; i++) {
        if(i == index) {
          return node;
        }

        node = node->next;
      }

      return nullptr;
    }

    void append(Node<T>* node) {
      // Not a valid node in the first place
      if(!node) {
        return;
      }
     
      // Still need to make sure the head is valid 
      if(!head) {
        prepend(node);
      }
      // Place as tail if there is no tail 
      else if(!tail) {
        node->previous = head; 
        node->next     = nullptr;
        tail           = node; 
        head->next     = tail;
      }
      // Otherwise, it's a normal node and append it to the tail 
      else {
        node->next     = nullptr; 
        node->previous = tail;
        tail->next     = node;

        // The new node is now the tail
        tail = node;
      }

      // New node added so increase the count
      count++;
    }

    void prepend(Node<T>* node) {
      // Not a valid node in the first place
      if(!node) {
        return;
      }

      // The node becomes the new head if no head exists 
      if(!head) {
        head           = node;
        head->next     = tail;
        head->previous = nullptr;
      }
      // Just a plain simple prepend operation
      else {
        node->next     = head;
        node->previous = nullptr;
        head->previous = node; 

        // The node now becomes the new head 
        head = node;
      }
      
      // New node added so increase the count
      count++;
    }
    
    void insert(Node<T>* node, Node<T>* prev, Node<T>* next) {
      // Not a valid node in the first place
      if(!node) {
        return;
      }
      
      // Placing the node in between the `next` and `prev`
      node->previous = prev;
      node->next     = next; 

      // Relinking the nodes
      next->previous = node;
      prev->next     = node;

      // New node added so increase the count
      count++;
    }

    void remove(Node<T>* node) {
      // Not a valid node in the first place or there's just nothing to remove
      if(!node || count == 0) {
        return;
      }
    
      // Relinking the nodes 
      if(node->next) {
        node->next->previous = node->previous;
      }

      if(node->previous) {
        node->previous->next = node->next;
      }

      // Some memory cleanup 
      delete node;
      
      // A node was removed so decrease the count (but don't go below zero)
      count -= count == 0 ? 0 : 1;
    }

    void remove_at(const sizei index) {
      // Must be a valid index
      assert(index >= 0 && index < count);
    
      // Just pop the head
      if(index == 0) {
        Node<T>* popped = pop_front();
        remove(popped);

        return;
      }
      // Just pop the tail 
      else if(index == (count - 1)) {
        Node<T>* popped = pop_back();
        remove(popped);

        return;
      }

      // Otherwise, just remove the node
      Node<T>* node = get_at(index);
      remove(node);
    }

    void emplace_front(const T& val) {
      Node<T>* node = new Node<T>(val);
      prepend(node);
    }

    void emplace_back(const T& val) {
      Node<T>* node = new Node<T>(val);
      append(node);
    }

    void emplace_at(const T& val, const sizei index) {
      // Can't insert past the end 
      assert(index >= 0 && index <= count);
      
      Node<T>* node = new Node<T>(val);

      if(index == 0) {
        prepend(node);
        return;
      }
      else if(index == count) {
        append(node);
        return;
      }

      // Otherwise, find the node at `index` and insert 
      Node<T>* curr = get_at(index);
      insert(node, curr->previous, curr);
    }

    Node<T>* pop_front() {
      // No head exists in the first place
      if(!head) {
        return nullptr;
      }
      
      // A node was removed so decrease the count (but don't go below zero)
      count -= count == 0 ? 0 : 1;

      // Relocating the head
      Node<T>* old_head        = head;
      old_head->next->previous = nullptr;
      head                     = old_head->next;

      return old_head;
    }

    Node<T>* pop_back() {
      // No tail exists in the first place
      if(!tail) {
        return nullptr;
      } 
      
      // A node was removed so decrease the count (but don't go below zero)
      count -= count == 0 ? 0 : 1;

      // Relocating the tail 
      Node<T>* old_tail        = tail; 
      old_tail->previous->next = nullptr; 
      tail                     = old_tail->previous;

      return old_tail;
    }

    const T& peek_at(const sizei index) {
      return get_at(index)->value; 
    }
    
    void clear() {
      Node<T>* node = head;

      // Clearing all the memory of each node 
      while(node != nullptr) {
        // Moving the loop forwards
        Node<T>* old_node  = node; 
        node               = node->next;
        
        // Deleting the node from existence
        delete old_node;

        // One less node to worry about...
        count--;
      }
    }

    void for_each(const Node<T>::ForEachFn& func) {
      for(auto node = head; node != nullptr; node = node->next) {
        func(node);
      }
    }

  public:
    Node<T>* head; 
    Node<T>* tail;
    sizei    count;
};
/// LinedList

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// Queue 
template<typename T>
class Queue {
  public:
    Queue() 
      :count(0), head(nullptr), tail(nullptr)
    {}
  
  public:
    sizei count;
    Node<T>* head;
    Node<T>* tail;

  public:
    typedef void(*ForEachFn)(Node<T>* node);
    
    void push(Node<T>* node) {
      // The given node is invalid 
      if(!node) {
        return;
      }

      // This is possibly the first element in the queue 
      if(!head) {
        head = node;
        head->next = nullptr;
      }
      // Place as tail if there is no tail 
      else if(!tail) {
        node->next     = nullptr;
        tail           = node; 
        head->next     = tail;
      }
      // Otherwise, it's a normal node and push it to the queue 
      else {
        tail->next     = node;
        node->next     = nullptr; 

        // The new node is now the tail
        tail = node;
      }

      // New node added so increase the count
      count++;
    }

    Node<T>* pop() {
      // There's nothing in the queue 
      if(!head) {
        return nullptr;
      }
      
      // Don't go below zero when popping 
      count -= count == 0 ? 0 : 1;
    
      // Relocating the head and popping the old head
      Node<T>* old_head = head; 
      head              = head->next; 

      return old_head;
    }

    void emplace(const T& val) {
      Node<T>* node = new Node<T>(val);
      push(node);
    }

    void for_each(const ForEachFn& func) {
      for(auto node = head; node != nullptr; node = node->next) {
        func(node);
      }
    }
};
/// Queue

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// Stack 
template<typename T>
class Stack {
  public:
    Stack() 
      :count(0), head(nullptr)
    {}
  
  public:
    sizei count;
    Node<T>* head;

  public:
    typedef void(*ForEachFn)(Node<T>* node);
    
    void push(Node<T>* node) {
      if(!node) {
        return;
      }

      // This is possibly the first element in the stack 
      if(!head) {
        head       = node;
        head->next = nullptr;
      }
      // Otherwise, it's a normal node and push it to the stack 
      else {
        node->next = head;
        head       = node;
      }

      // New node added so increase the count
      count++;
    }

    Node<T>* pop() {
      // There's nothing in the stack 
      if(count == 0) {
        return nullptr;
      }

      // Don't go below zero when popping 
      count -= count == 0 ? 0 : 1;
    
      // Relocating the head and popping the old head
      Node<T>* old_head = head; 
      head              = head->next;
      old_head->next    = nullptr;

      return old_head;
    }

    void emplace(const T& val) {
      Node<T>* node = new Node<T>(val);
      push(node);
    }

    void for_each(const ForEachFn& func) {
      for(auto node = head; node != nullptr; node = node->next) {
        func(node);
      }
    }
};
/// Stack

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// DynamicArray 
template<typename T> 
class DynamicArray {
  public:
    DynamicArray() {
      capacity = 5; 
      size     = 0;
      data     = (T*)malloc(sizeof(T) * capacity);
    }

    DynamicArray(const sizei initial_capacity) {
      capacity = initial_capacity; 
      size     = 0;
      data     = (T*)malloc(sizeof(T) * capacity);
    }
    
    DynamicArray(T* dat, const sizei dat_size) {
      size     = dat_size; 
      capacity = size + (size / 2);
      data     = dat;
    }

  public:
    T* data;
    sizei capacity, size;

  public: 
    typedef void(*ForEachFN)(T& value);

  public:
    void reserve(const sizei new_capacity) {
      // There's nothing to be done when the given `new_capacity` is 
      // the _same_ as the current `capacity`
      if(new_capacity == capacity) {
        return;
      }

      /* 
       * @NOTE: Keep in mind that if the given `new_capacity` is _smaller_ than
       * the current `capacity`, the array will _shrink_ in size. Naturally.
       * However, if the opposite is true, than the array will _bloat_ is size.
      */

      capacity = new_capacity;
      data = (T*)realloc(data, sizeof(T) * capacity); 
    
      // Assert just in case the system runs out of memory 
      assert(data != nullptr);
    }

    void resize(const sizei new_size) {
      sizei old_size = size;
      size += new_size;

      // Grow the array by half the new size if need be
      if(size >= capacity) {
        reserve(capacity + (size / 2));
      }

      // We set _only_ the new elements in the array to a default value. 
      // This way, we won't need to touch the already-existing values.
      data = memset(data + (sizeof(T) * old_size), 0, sizeof(T) * new_size);
    }

    void append(const T& val) {
      size++;

      // Grow the array if need be
      if(size >= capacity) {
        reserve(capacity + (size / 2));
      }

      // Add the new value to the array
      data[size - 1] = val;
    }

    T& pop_back() {
      // There's nothing in the array in the first place 
      if(size == 0) {
        return data[size];
      }

      // We pop the element from the back and ignore it for now
      T& element = data[size - 1];
      size--;

      return element;
    }

    T& pop_front() {
      T& element = data[0];

      // Reshuffle the entire array 
      for(sizei i = 1; i < size; i++) {
        data[i - 1] = data[i];
      }

      size--;
      return element;
    }

    const T& peek_front() {
      return data[0];
    }
    
    const T& peek_back() {
      return data[size - 1];
    }

    void remove(const sizei index) {
      for(sizei i = index; i < size; i++) {
        data[i] = data[i + 1]; 
      } 

      size--;
    }

    DynamicArray<T> slice(const sizei begin, const sizei end) {
      sizei new_data_size = (end - begin) + 1; // Make sure that `end` is _inclusive_
      T* new_data = (T*)malloc(sizeof(T) * new_data_size);

      // Copying over the correct data 
      for(sizei i = begin, j = 0; i < new_data_size || j < new_data_size; i++, j++) {
        new_data[j] = at(i);
      }

      return DynamicArray<T>(new_data, new_data_size);
    }

    void fill(const sizei count, const T& value) {
      for(sizei i = 0; i < count; i++) {
        append(value); 
      }
    }

    void clear() {
      // @NOTE: This might be dangerous
      free(data);

      size     = 0; 
      capacity = 0;
    }
    
    const T& at(const sizei index) {
      // Index out of bounds
      assert((index >= 0 && index < size));

      // Otherwise, just return the value 
      return data[index];
    }

    void for_each(const ForEachFN& fn) {
      for(sizei i = 0; i < size; i++) {
        fn(data[i]);
      }
    }

    // Operator overloading for []
    const T& operator[](const sizei index) {
      return at(index);
    }

    const T& operator[](const sizei index) const {
      return at(index);
    }
};
/// DynamicArray

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////    

/// String
template<typename T> 
struct String {
  sizei length = 0; 
  T* data      = nullptr;

  T& operator[](const sizei index) {
    assert(index >= 0 && index < length);
    return data[index]; 
  } 

  const T& operator[](const sizei index) const {
    assert(index >= 0 && index < length);
    return data[index]; 
  } 
};
/// String

/// String functions 
template<typename T>
const sizei string_length(const T* str) {
  return strlen(str); 
}

template<typename T>
const bool string_is_empty(String<T>& str) {
  return str.length == 0;
}

template<typename T> 
void string_copy(String<T>& str1, const T* str2, const sizei str2_len) {
  if(!str2) {
    return;
  }
 
  // The string's new size
  str1.length = str2_len; 

  // We don't need the old data
  if(str1.data) {
    free(str1.data);
  }
 
  // Make a new array
  str1.data = (T*)malloc(sizeof(T) * str1.length);

  // Copy the string over
  memcpy(str1.data, str2, sizeof(T) * str1.length);
}

template<typename T> 
void string_copy(String<T>& str1, const String<T>& str2) {
  string_copy(str1, str2.data, str2.length);
}

template<typename T> 
void string_copy(String<T>& str1, const T* str2) {
  string_copy(str1, str2, string_length(str2));
}

template<typename T>
String<T> string_create(const T* str) {
  String<T> istr;
  string_copy(istr, str);

  return istr;
}

template<typename T> 
void string_destroy(String<T>& str) {
  str.length = 0;
  
  if(!str.data) {
    return;
  }

  free(str.data);
}

template<typename T>
void string_append(String<T>& str1, const String<T>& str2) {
  str1.data = (T*)realloc(str1.data, sizeof(T) * (str1.length + str2.length));
  memcpy(str1.data + (sizeof(T) * str1.length), str2.data, str2.length);

  str1.length += str2.length;
}

template<typename T>
void string_append(String<T>& str1, const T* str2) {
  sizei str2_len = string_length(str2);

  str1.data = (T*)realloc(str1.data, str1.length + str2_len);
  memcpy(str1.data + (sizeof(T) * str1.length), str2, str2_len);

  str1.length += str2_len;
}

template<typename T>
void string_append(String<T>& str, const T& ch) {
  str.length += 1;
  str.data    = (T*)realloc(str.data, sizeof(T) * str.length);
  str[str.length - 1] = ch;
}

template<typename T>
void string_append_at(String<T>& str, const sizei index, const T& ch) {
  str.length += 1;
  str.data    = (T*)realloc(str.data, sizeof(T) * str.length);

  // Shift all characters to fit the new given `ch` 
  for(sizei i = str.length - 1; i > index; i--) {
    str[i] = str[i - 1]; 
  }

  // Insert the new given `ch` in the empty slot
  str[index] = ch;
}

template<typename T>
String<T> string_slice(String<T>& str, const sizei begin, const sizei end) {
  sizei new_data_size = (end - begin) + 1; // Make sure that `end` is _inclusive_
  T* new_data = (T*)malloc(sizeof(T) * new_data_size);

  // Copying over the correct data 
  for(sizei i = begin, j = 0; i < new_data_size || j < new_data_size; i++, j++) {
    new_data[j] = str[i];
  }

  return string_create(new_data);
}

template<typename T>
const bool string_compare(const String<T>& str1, const String<T>& str2) {
  // Can't be the same if they are of different sizes
  if(str1.length != str2.length) {
    return false; 
  }

  for(sizei i = 0; i < str1.length; i++) {
    // Even if a _single_ character is different then the strings are _not_ the same
    if(str1[i] != str2[i]) {
      return false;
    }
  }

  return true;
}

template<typename T>
void string_reverse(String<T>& str) {
  T reversed_str[str.length - 1] = {};

  for(sizei i = str.length - 1, j = 0; i >= 0 && j < str.length; i--, j++) {
    reversed_str[j] = str[i]; 
  }

  string_copy(str, reversed_str);
}

template<typename T>
const sizei string_find(String<T>& str, const T& ch, const sizei start = 0) {
  for(sizei i = start; i < str.length; i++) {
    if(str[i] == ch) {
      return i;
    }
  }

  // Couldn't find the given `ch` in `str`
  return STRING_NPOS;
}

template<typename T>
const sizei string_find_first_of(String<T>& str, const T& ch) {
  return string_find(str, ch);
}

template<typename T>
const sizei string_find_last_of(String<T>& str, const T& ch) {
  for(sizei i = str.length - 1; i > 0; i--) {
    if(str[i] == ch) {
      return i;
    }
  } 

  return -1;
}

template<typename T>
void string_remove(String<T>& str, const sizei begin = 0, sizei end = STRING_NPOS) {
  if(end == STRING_NPOS) {
    end = str.length;
  } 

  sizei new_len = (end - begin + 1) * sizeof(T);
  T* temp_str = (T*)malloc(new_len);

  for(sizei i = begin, j = 0; i < end && j < end; i++, j++) {
    temp_str[j] = str[i]; 
  }

  string_copy(str, temp_str, new_len);
}

template<typename T>
void string_replace_at(String<T>& str, const sizei index, const T& ch) {
  str[index] = ch;
}

template<typename T>
void string_replace(String<T>& str, const T& ch1, const T& ch2) {
  sizei index = 0;

  for(sizei i = 0; i < str.length; i++) {
    if(str[i] == ch1) {
      index = i;
      break;
    }
  }

  string_replace_at(str, index, ch2);
}

template<typename T>
void string_replace_all_of(String<T>& str, const T& ch1, const T& ch2) {
  for(sizei i = 0; i < str.length; i++) {
    if(str[i] == ch1) {
      string_replace_at(str, i, ch2);
    }
  }
}

template<typename T>
const bool string_has(String<T>& str, const T& ch) {
  return string_find(str, ch) != STRING_NPOS;
}

template<typename T>
const bool string_has_at(String<T>& str, const sizei index, const T& ch) {
  return str[index] == ch;
}

template<typename T>
void string_fill(String<T>& str, const sizei length, const T& ch) {
  str.length = length;
  str.data = (T*)realloc(str.data, sizeof(T) * length);

  for(sizei i = 0; i < str.length; i++) {
    str[i] = ch;
  }
}
/// String functions 

// UTF-8 String (ASCII)
typedef String<i8> String8; 

////////////////////////////////////////////////////////////////////

} // End of ishtar
