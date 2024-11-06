#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cwchar>

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

/// String functions 
template<typename T>
const sizei string_length(const T* str) {
  return strlen(str);
}
/// String functions 

/// String
template<typename T> 
struct String {
  sizei length = 0; 
  T* data      = nullptr;

  String() = default;

  String(const T* str) {
    copy(str);
  }

  String(const T* str, const sizei str_len) {
    copy(str, str_len);
  }

  ~String() {
    length = 0;

    if(data) {
      free(data);
    }
  }
 
  const T& at(const sizei index) const {
    assert(index >= 0 && index < length);
    return data[index]; 
  }

  T& operator[](const sizei index) {
    return at(index); 
  }

  const T& operator[](const sizei index) const {
    return at(index); 
  } 

  void copy(const T* str, const sizei str_len) {
    if(!str) {
      return;
    }

    // The string's new size
    length = str_len; 

    // We don't need the old data
    if(data) {
      free(data);
    }

    // Make a new array
    data = (T*)malloc(sizeof(T) * length);

    // Copy the string over
    memcpy(data, str, sizeof(T) * length);
  }

  void copy(const String<T>& str) {
    copy(str.data, str.length);
  }
  
  void copy(const T* str) {
    copy(str, string_length(str));
  }

  const bool is_empty() {
    return length == 0;
  }

  void append(const String<T>& other) {
    data = (T*)realloc(data, sizeof(T) * (length + other.length));
    memcpy(data + (sizeof(T) * length), other.data, other.length);

    length += other.length;
  }

  void append(const T* other) {
    sizei other_len = string_length(other);

    data = (T*)realloc(data, length + other_len);
    memcpy(data + (sizeof(T) * length), other, other_len);

    length += other_len;
  }

  void append(const T& ch) {
    length += 1;
    data    = (T*)realloc(data, sizeof(T) * length);
    data[length - 1] = ch;
  }

  void append_at(const sizei index, const T& ch) {
    length += 1;
    data    = (T*)realloc(data, sizeof(T) * length);

    // Shift all characters to fit the new given `ch` 
    for(sizei i = length - 1; i > index; i--) {
      data[i] = at(i - 1); 
    }

    // Insert the new given `ch` in the empty slot
    data[index] = ch;
  }

  String<T> slice(const sizei begin, const sizei end) {
    sizei new_data_size = (end - begin) + 1; // Make sure that `end` is _inclusive_
    T* new_data = (T*)malloc(sizeof(T) * new_data_size);

    // Copying over the correct data 
    for(sizei i = begin, j = 0; i < new_data_size || j < new_data_size; i++, j++) {
      new_data[j] = at(i);
    }

    return String(new_data);
  }

  const bool compare(const String<T>& other) {
    // Can't be the same if they are of different sizes
    if(length != other.length) {
      return false; 
    }

    for(sizei i = 0; i < length; i++) {
      // Even if a _single_ character is different then the strings are _not_ the same
      if(at(i) != other[i]) {
        return false;
      }
    }

    return true;
  }

  void reverse() {
    T* reversed_str = (T*)malloc(sizeof(T) * length);

    for(sizei i = length - 1, j = 0; i >= 0 && j < length; i--, j++) {
      reversed_str[j] = at(i); 
    }

    copy(reversed_str);
    free(reversed_str);
  }

  const sizei find(const T& ch, const sizei start = 0) {
    for(sizei i = start; i < length; i++) {
      if(at(i) == ch) {
        return i;
      }
    }

    // Couldn't find the given `ch` in `str`
    return STRING_NPOS;
  }

  const sizei find_last_of(const T& ch) {
    for(sizei i = length - 1; i > 0; i--) {
      if(at(i) == ch) {
        return i;
      }
    } 

    return STRING_NPOS;
  }

  const sizei find_first_of(const T& ch) {
    return find(ch);
  }

  void remove(const sizei begin, const sizei end) {
    sizei new_len = (end - begin) * sizeof(T);
    T* temp_str = (T*)malloc(new_len);

    for(sizei i = begin, j = 0; i < end && j < end; i++, j++) {
      temp_str[j] = at(i); 
    }

    copy(temp_str, new_len);
  }

  void replace_at(const sizei index, const T& ch) {
    data[index] = ch;
  }

  void replace(const T& ch1, const T& ch2) {
    sizei index = 0;

    for(sizei i = 0; i < length; i++) {
      if(at(i) == ch1) {
        index = i;
        break;
      }
    }

    replace_at(index, ch2);
  }

  void replace_all_of(const T& ch1, const T& ch2) {
    for(sizei i = 0; i < length; i++) {
      if(at(i) == ch1) {
        replace_at(i, ch2);
      }
    }
  }

  const bool has(const T& ch) {
    return find(ch) != STRING_NPOS;
  }

  const bool has_at(const sizei index, const T& ch) {
    return data[index] == ch;
  }

  void fill(const sizei len, const T& ch) {
    length = len;
    data = (T*)realloc(data, sizeof(T) * length);

    for(sizei i = 0; i < length; i++) {
      data[i] = ch;
    }
  }
};
/// String

// UTF-8 String (ASCII)
typedef String<i8> String8; 

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

/// HashTable
template<typename K, typename V> 
struct HashTable {
  sizei size     = 0; 
  sizei capacity = 0;
};
/// HashTable 

////////////////////////////////////////////////////////////////////

} // End of ishtar
