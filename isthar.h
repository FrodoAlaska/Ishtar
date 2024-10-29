#pragma once

#include <cstddef>
#include <cstdio>

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
typedef size_t sizei;

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

      // Place as tail if there is no head 
      if(!tail) {
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
      // of the given node to be valid. Otherwise, it's just a `pop_front` 
      // or `pop_back` operation.
      if(!node || !node->previous || !node->next) {
        return;
      }

      // Relinking the nodes 
      node->next->previous = node->previous;
      node->previous->next = node->next;

      // A node was removed so decrease the count 
      count--;

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

    const Node<T>* pop_head() {
      // No head exists in the first place
      if(!head) {
        return nullptr;
      }
      
      // A node was removed so decrease the count 
      count--;

      // Relocating the head
      Node<T>* old_head        = head;
      old_head->next->previous = nullptr;
      head                     = old_head->next;

      return old_head;
    }

    const Node<T>* pop_tail() {
      // No tail exists in the first place
      if(!tail) {
        return nullptr;
      } 
      
      // A node was removed so decrease the count 
      count--;

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

  public:
    Node<T>* head; 
    Node<T>* tail;
    sizei    count;
};

////////////////////////////////////////////////////////////////////

} // End of ishtar
