#ifndef BST_H__
#define BST_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

  // bst_node is the binary search tree node structure.
  struct bst_node {
    int data;
    shared_ptr<bst_node> left;
    shared_ptr<bst_node> right;
  };

  // Binary search tree:
class BST {
public:
  // constructor
  BST();

  // deconstructor
  ~BST();

  // init_node initializes a new bst_node from the heap using the given
  // data, and two NULL children, and returns a pointer to it.
  shared_ptr<bst_node> InitNode(int data);

  // insert places the new_node in a proper location in the tree
  // while obeying the invariant. On return, root_ptr_
  // points to the root of the tree.
  void Insert(shared_ptr<bst_node> new_node);

  // insertData creates a new node with the given data value and
  // inserts it similarly to insert().
  void InsertData(int data);

  // remove removes a node from the tree whose data value matches the
  // input. If no node in the tree contains the given data, this function
  // has no effect.
  void Remove(int data);

  // contains returns true if any node in the subtree pointed to by t
  // contains the given data value, false otherwise.
  bool Contains(shared_ptr<bst_node> subt, int data);

  // get_node searches through the subtree pointed to by subt for a node that
  // contains the given data value. If such a node is found, a pointer
  // to it is returned. Otherwise this function returns NULL.
  shared_ptr<bst_node> GetNode(shared_ptr<bst_node> subt, int data);

  // size returns the number of nodes in the subtree pointed to by subt. If
  // the tree is empty (t is NULL), it returns zero.
  int Size(shared_ptr<bst_node> subt);

  int SizeHelper(shared_ptr<bst_node> subt);

  // ToVector fills an integer vector to reflect the contents of the
  // subtree pointed to by subt. order of
  // the array elements are the same that is found during an INORDER
  // traversal of the subtree.
  void ToVector(shared_ptr<bst_node> subt, vector<int>& vec);

  void InOrder(shared_ptr<bst_node> subt, vector<int>& vec);

  // Returns the root pointer
  shared_ptr<bst_node> GetRoot();

  // sets a given pointer as the top pointer
  void SetRoot(shared_ptr<bst_node> root_ptr);

private:
  // this pointer always will point to root of the tree
  shared_ptr<bst_node> root_ptr_;
  shared_ptr<bst_node> curr_parent;
  shared_ptr<bst_node> succ_parent;
  int numberOfNodes;
};

#endif  // BST_H__
