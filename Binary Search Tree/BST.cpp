#include "BST.h"
#include <iostream>
using namespace std;

// constructor
BST::BST(){
  root_ptr_ = NULL;
  numberOfNodes = 0;
  curr_parent = NULL;
  succ_parent = NULL;
}

//deconstructor
BST::~BST(){
}

shared_ptr<bst_node> BST::InitNode(int data){
  shared_ptr<bst_node> init(new bst_node);
  init->data = data;
  init->left = NULL;
  init->right = NULL;
  return init;
}


void BST::Insert(shared_ptr<bst_node> new_node){
  shared_ptr<bst_node>curr (new bst_node);
  if (root_ptr_ == NULL){
    root_ptr_ = new_node;
    root_ptr_->left = NULL;
    root_ptr_->right = NULL;
    return;
  }
  curr = root_ptr_;
  while (curr){
    if (new_node->data < curr->data && curr->left){
      curr = curr->left;
    }
    else if (new_node->data < curr->data && !(curr->left)){
      curr->left = new_node;
      curr->left->left = NULL;
      curr->left->right = NULL;
      return;
    }
    if (new_node->data > curr->data && curr->right){
      curr = curr->right;
    }
    else if (new_node->data > curr->data && !(curr->right)){
      new_node->left = NULL;
      new_node->right = NULL;
      curr->right = new_node;

      return;
    }
    if (new_node->data == curr->data && curr->right){
      curr = curr->right;
    }
    else if (new_node->data == curr->data && !(curr->right)){
      curr->right = new_node;
      curr->right->left = NULL;
      curr->right->right = NULL;
      return;
    }
  }
}

void BST::InsertData(int data){
  shared_ptr<bst_node>curr(new bst_node);
  curr->data = data;
  Insert(curr);
  return;
}

void BST::Remove(int data){
  shared_ptr<bst_node>curr (new bst_node);
  shared_ptr<bst_node>successor (new bst_node);
  curr = GetNode(root_ptr_, data);
  //no children
  if (!(curr->left) && !(curr->right)){
    if(curr_parent->left == curr){
      curr_parent->left = NULL;
    }
    else if(curr_parent->right == curr){
      curr_parent->right = NULL;
    }
  }
  //only right child which is leaf
  else if (!(curr->left) && (curr->right)){
    if (!(curr->right->left) && !(curr->right->right)){
      if(curr_parent->left == curr){
        curr_parent->left = curr->right;
     }
      else if(curr_parent->right == curr){
        curr_parent->right = curr->right;
      }
    }
  }
  //only left child which is leaf
  else if ((curr->left) && !(curr->right)){

    if (!(curr->left->left) && !(curr->left->right)){
      if(curr_parent->left == curr){
        curr_parent->left = curr->left;
     }
      else if(curr_parent->right == curr){
        curr_parent->right = curr->left;
      }
    }
  }
  //has children, find in order successor
  else {
    succ_parent= curr;
    successor = curr->right;
    while (successor){
      if (successor->left){
        succ_parent = successor;
        successor = successor->left;
      }
      else{
        break;
      }
    }
    if (succ_parent->left == successor){
      curr->data = successor->data;
      succ_parent->left = successor->right;
    }
    else if (succ_parent->right == successor){
      curr->data = successor->data;
      succ_parent->right = successor->right ;
    }
  }
}

bool BST::Contains(shared_ptr<bst_node> subt, int data){
  shared_ptr<bst_node>curr (new bst_node);
  curr = subt;
  while (curr){
    if (data < curr->data){
      curr = curr->left;
    }
    else if (data > curr->data){
      curr = curr->right;
    }
    else if (data == curr->data){
      return true;
    }
  }
  return false;
}

shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data){
  if (!(subt)){
    return shared_ptr<bst_node>(NULL);
  }
  shared_ptr<bst_node>curr (new bst_node);
  curr = subt;
  if ( !(curr->left) && !(curr->right) && (data != curr->data)){
    return shared_ptr<bst_node>(NULL);
  }
  while (curr){
    if ( !(curr->left) && !(curr->right) && (data != curr->data)){
      return shared_ptr<bst_node>(NULL);
    }
    if (data < curr->data){
      if (!(curr->left)){
        return shared_ptr<bst_node>(NULL);
      }
      curr_parent = curr;
      curr = curr->left;
    }
    else if (data > curr->data){
      if (!(curr->right)){
        return shared_ptr<bst_node>(NULL);
      }
      curr_parent = curr;
      curr = curr->right;
    }
    if (data == curr->data){
      return curr;
    }
  }
  return shared_ptr<bst_node>(NULL);
}

int BST::SizeHelper(shared_ptr<bst_node> subt){
  if (subt == NULL){
    return 0;
  }
  SizeHelper(subt->left);
  numberOfNodes++;
  SizeHelper(subt->right);
  return numberOfNodes;
}

int BST::Size(shared_ptr<bst_node> subt){
  numberOfNodes = 0;
  return SizeHelper(subt);
}

void BST::InOrder(shared_ptr<bst_node> subt, vector<int>& vec){
  if (subt == NULL){
    return;
  }
  if (subt->left){
    InOrder(subt->left, vec);
  }
  vec.push_back(subt->data);
  if (subt->right){
    InOrder(subt->right, vec);
  }
  if (!(subt->left) && !(subt->right)){
    return;
  }
}

void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
  InOrder(subt, vec);
}

shared_ptr<bst_node> BST::GetRoot(){
  return root_ptr_;
}

void BST::SetRoot(shared_ptr<bst_node> root_ptr){
  root_ptr_ = root_ptr;
}
