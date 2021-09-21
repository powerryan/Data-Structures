#ifndef Treap_H__
#define Treap_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

  // product represents the goods in inventory.
  struct product {
    int productID;
    int quantity;
    string name;
    string description;
  };
  // treap_node is the treap node structure.
  struct treap_node {
    int data;
    int heapnumber;
    product item;
    shared_ptr<treap_node> parent;
    shared_ptr<treap_node> left;
    shared_ptr<treap_node> right;
  };

  // Treap:
  //
  // From any subtree node t, the left subtree's data values must be
  // less than t's data value. The right subtree's data values must be
  // greater than or equal to t's data value. It also follows the min-heap
  // structure in which each parent key or randomly generated heapnumber
  // is greater than its children's.

class Treap {
public:

  Treap();

  ~Treap();

  // init_node initializes a new treap_node from the heap using the given
  // product and returns a pointer to it.
  shared_ptr<treap_node> InitNode(product p);

  // insert places the new_node in a proper location in the tree
  // while obeying the invariants. On return, root_ptr_
  // points to the root of the tree.
  void Insert(shared_ptr<treap_node> new_node);

  // Helper method for Insert. Performs as many left and right rotations as needed while inserting
  // a new node in order to keep the min-heap invariant.
  void Rotate(shared_ptr<treap_node> new_node);

  // Rotates left while removing a node to maintain invariants.
  void RotateLeft(shared_ptr<treap_node> new_node);

  // Rotates right while removing a node to maintain invariants.
  void RotateRight(shared_ptr<treap_node> new_node);

  // remove removes a node from the tree whose data value matches the
  // input. If no node in the tree contains the given data, this function
  // has no effect.
  void Remove(int data);

  // This method traverses the treap and prints every product and its available
  // quantity in order of the data value (product number).
  string PrintProducts(int data, bool all);

  // helper method for PrintProducts. Uses in order traversal to find each node
  // and its product in order.
  void InOrder(shared_ptr<treap_node> curr, int data, bool all, string& s);

  // contains returns true if any node in the treap
  // contains the given data value, false otherwise.
  bool Contains(int ID);

  // UpdateInventory updates the product quantity by adding input to current
  // quantity. Can be increased or decreased but cannot go below 0.
  bool UpdateInventory(int ID, int quantity);

  // get_node searches through the treap for a node that
  // contains the given data value. If such a node is found, a pointer
  // to it is returned. Otherwise this function returns NULL.
  shared_ptr<treap_node> GetNode(int data);

  // returns inventory count for product whose ID/ node data matches the input.
  int GetInventory(int data);

  // size returns the number of nodes in the treap. If
  // the tree is empty (it is NULL), it returns zero.
  int Size();

  // ToVector fills a vector of integer vectors to reflect the contents of the
  // subtree pointed to by subt. Size of the array will be the same as the
  // subtree's size, and the order of the array elements are the same that is
  // found during an INORDER traversal of the subtree.
  void ToVector(shared_ptr<treap_node> subt, vector<vector<int>>& vec);

  // ToVector helper method to traverse treap in order.
  void Traverse(shared_ptr<treap_node> subt, vector<vector<int>>& vec);

  // Returns the root pointer
  shared_ptr<treap_node> GetRoot();

  // sets a given pointer as the top pointer
  void SetRoot(shared_ptr<treap_node> root_ptr);

private:
  // this pointer always points to root of the tree
  shared_ptr<treap_node> root_ptr_;
  shared_ptr<treap_node> curr_parent;
  int numberOfNodes;
};

#endif  // Treap_H__
