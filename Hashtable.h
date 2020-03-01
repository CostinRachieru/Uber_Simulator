// Copyright 2019 Rachieru Costin Tudor <<costinrch46@gmail.com>>

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <list>
#include <iterator>

template <typename Tkey, typename Tvalue> struct info {
  Tkey key;
  Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
 private:
  std::list<struct info<Tkey, Tvalue>> *H;
  int size;
  int capacity;
  int (*hash)(Tkey);

 public:
  // Constructor
  Hashtable(int capacity, int (*h)(Tkey)) {
    this->capacity = capacity;
    this->size = 0;
    H = new std::list<struct info<Tkey, Tvalue>>[capacity];
    this->hash = h;
  }

  // Destructor
  ~Hashtable() {
    delete[] H;
  }

  // Puts element in HashTable.
  void put(Tkey key, Tvalue value) {
    int index = hash(key) % capacity;
    typename std::list<struct info <Tkey, Tvalue>>::iterator iterator;
    for (iterator = H[index].begin(); iterator != H[index].end(); iterator++) {
      if (iterator->key == key) {
        iterator->value = value;
        return;
      }
    }
    struct info<Tkey, Tvalue> aux;
    aux.key = key;
    aux.value = value;
    H[index].push_back(aux);
  }

  // Removes element from HashTable.
  void remove(Tkey key) {
    int index = hash(key) % capacity;
    typename std::list<struct info <Tkey, Tvalue>>::iterator iterator;
    for (iterator = H[index].begin(); iterator != H[index].end(); iterator++) {
      if (iterator->key == key) {
        H[index].erase(iterator);
        return;
      }
    }
  }

  // Gets the value of an element.
  Tvalue get(Tkey key) {
    int index = hash(key) % capacity;
    typename std::list<struct info <Tkey, Tvalue>>::iterator iterator;
    for (iterator = H[index].begin(); iterator != H[index].end(); iterator++) {
      if (iterator->key == key) {
        return iterator->value;
      }
    }
    return Tvalue();
  }

  // Checks if there is an element with this key.
  bool has_key(Tkey key) {
    int index = hash(key) % capacity;
    typename std::list<struct info <Tkey, Tvalue>>::iterator iterator;
    for (iterator = H[index].begin(); iterator != H[index].end(); iterator++) {
      if (iterator->key == key) {
        return true;
      }
    }
    return false;
  }

  std::list<struct info<Tkey, Tvalue>>* getHashtable() {
    return H;
  }

  int get_size() {
    return size;
  }

  int get_capacity() {
    return capacity;
  }
};

#endif  // HASHTABLE_H_
