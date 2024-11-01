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
      // Not a valid node in the first place.
      // And also, we _need_ the `previous` and `next` nodes 
      // of the given node to be valid. Otherwise, it's just a `append` 
      // or `prepend` operation.
      if(!node || !node->previous || !node->next) {
        return;
      }

      // Relinking the nodes 
      node->next->previous = node->previous;
      node->previous->next = node->next;

      // A node was removed so decrease the count (but don't go below zero)
      count -= count == 0 ? 0 : 1;

      // Some memory cleanup 
      delete node;
    }

    void emplace_front(const T& val) {
      Node<T>* node = new Node<T>(val);
      prepend(node);
    }

    void emplace_back(const T& val) {
      Node<T>* node = new Node<T>(val);
      append(node);
    }

    void emplace_at(const T& val, Node<T>* prev, Node<T>* next) {
      Node<T>* node = new Node<T>(val);
      insert(node, prev, next);
    }

    const Node<T>* pop_front() {
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

    const Node<T>* pop_back() {
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
////////////////////////////////////////////////////////////////////

} // End of ishtar
