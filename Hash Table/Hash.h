#ifndef HASH_H__
#define HASH_H__

#include <string>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
// hash_node represents the contents of an individual bucket in hash table
struct hash_node {
  // deleted indicates if the node was marked as removed from the hash table
  bool deleted;
  // key is the key the user provides to associate with a value.
  std::string key;
  // hashcode is the hashcode computed by the hash table's hash_func
  unsigned int hashcode;
  std::string value;
};

typedef vector<shared_ptr<hash_node>> htable;

// hash_table is the structure that holds hashed data and
// associated metadata and hash function references.
struct hash_table {
  // capacity current number of addressable buckets in table. kept up-to-date.
  unsigned int capacity;
  // number of actual (not deleted) entries. kept up-to-date.
  unsigned int size;
  // number of non-null buckets. (so all hash_nodes, deleted or
  // otherwise). kept up-to-date.
  unsigned int occupied;
  // table points to dynamic array of hash_node pointers
  shared_ptr<htable> table;
  // hash_func is the currently in-use hash function. it should be
  // initialized to the djb2 hash function
  unsigned int (*hash_func)(std::string);
  // bucket_func is the currently in-use bucket indexing function. it
  // should be initialized to the modulo_bucket_func function.
  unsigned int (*bucket_func)(unsigned int hashcode, unsigned int capacity);
};

// DJB2 is a hash function that hashes strings and gives an unsigned
// integer hash code that could take on any value in the 32-bit
// unsigned integer range.
unsigned int DJB2(std::string key);

// ModuloBucketFunc simply returns hashcode % cap.
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap);


class Hash {
public:
  Hash();

  // deconstructor
  ~Hash();

  // InitTable creates and initializes a hash_table structure and
  // returns a pointer to it.
  shared_ptr<hash_table> InitTable(unsigned int cap);

  // InitNode creates and initializes a hash_node that will occupy a
  // hash table bucket.
  shared_ptr<hash_node> InitNode(std::string key, unsigned int hashcode, std::string val);

  // SetKVP establishes a mapping between the given key and value pair
  // in the provided hash table. if the key (as identified by its hash
  // code) is already in the hash table, its value is potentially
  // updated. otherwise a new key/value pair is added to the hash table.
  bool SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value);

  // Load returns a load factor describing how 'full' the table
  // is.
  float Load(shared_ptr<hash_table> tbl);

  // GetVal returns the value associated with the provded key in the
  // table, or the empty string "" if no such mapping exists (or if
  // there is a mapping but it is deleted).
  std::string GetVal(shared_ptr<hash_table> tbl, std::string key);

  // Contains returns true if the table has a non-deleted node whose
  // hashcode matches the given key's hashcode.
  bool Contains(shared_ptr<hash_table> tbl, std::string key);

  // Remove marks as 'deleted' any existing non-deleted hash_node with
  // the same hashcode as the provided key's hashcode. if it finds such
  // a hash node, it decrements the table's size (but not occupancy) and
  // returns true. it returns false otherwise.
  bool Remove(shared_ptr<hash_table> tbl, std::string key);

  void PrintTable(shared_ptr<hash_table> tbl);

private:
shared_ptr<hash_table> ht;
};

#endif  // HASH_H__
