#include "Treap.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string>
using namespace std;

Treap::Treap(){
  root_ptr_ = NULL;
  numberOfNodes = 0;
}

Treap::~Treap(){
}

shared_ptr<treap_node> Treap::InitNode(product p){
  shared_ptr<treap_node> init(new treap_node);
  init->data = p.productID;
  if (!p.quantity){
      p.quantity = 0;
  }
  init->left = NULL;
  init->right = NULL;
  init->parent = NULL;
  init->item = p;
  srand(time(0));
  init->heapnumber = rand() % 100;
  return init;
}

void Treap::Rotate(shared_ptr<treap_node> new_node){
    if (new_node == root_ptr_ || new_node->heapnumber >= new_node->parent->heapnumber){
        return;
    }
    else
    {
        if (new_node->parent->left == new_node)
        {
            shared_ptr<treap_node>newParent (new treap_node);
            newParent = new_node->parent;
            if (newParent->parent){
                new_node->parent = newParent->parent;
            }
            if (new_node->parent->left == newParent){
                new_node->parent->left = new_node;
            }
            else {
                new_node->parent->right = new_node;
            }
            if (new_node->right){
                newParent->left = new_node->right;
                newParent->left->parent = newParent;
            }
            else{
                newParent->left = NULL;
            }
            newParent->parent = new_node;
            new_node->right = newParent;
            if (newParent == root_ptr_){
                root_ptr_ = new_node;
                root_ptr_->parent = NULL;
                return;
            }
            else {
                Rotate(new_node->parent);
            }
        }
        else if (new_node->parent->right == new_node){
            shared_ptr<treap_node>newParent (new treap_node);
            newParent = new_node->parent;
            if (newParent->parent){
                new_node->parent = newParent->parent;
            }
            if (new_node->parent->left == newParent){
                new_node->parent->left = new_node;
            }
            else {
                new_node->parent->right = new_node;
            }
            if (new_node->left){
                newParent->right = new_node->left;
                newParent->right->parent = newParent;
            }
            else{
                newParent->right = NULL;
            }
            newParent->parent = new_node;
            new_node->left = newParent;
            if (newParent == root_ptr_){
                root_ptr_ = new_node;
                root_ptr_->parent = NULL;
                return;
            }
            else {
                Rotate(new_node->parent);
            }
        }
    }
}

void Treap::Insert(shared_ptr<treap_node> new_node){
  numberOfNodes++;
  shared_ptr<treap_node>curr (new treap_node);
  if (root_ptr_ == NULL){
    root_ptr_ = new_node;
    root_ptr_->left = NULL;
    root_ptr_->right = NULL;
    root_ptr_->parent = NULL;
    return;
  }
  curr = root_ptr_;
  while (curr){
    if (new_node->data < curr->data && curr->left){
      curr = curr->left;
    }
    else if (new_node->data < curr->data && !(curr->left)){
      curr->left = new_node;
      new_node->parent = curr;
      new_node->left = NULL;
      new_node->right = NULL;
      Rotate(new_node);
      return;
    }
    if (new_node->data >  curr->data && curr->right){
      curr = curr->right;
    }
    else if (new_node->data > curr->data && !(curr->right)){
      curr->right = new_node;
      new_node->left = NULL;
      new_node->right = NULL;
      new_node->parent = curr;
      Rotate(new_node);
      return;
    }
    if (new_node->data == curr->data && curr->right){
      curr = curr->right;
    }
    else if (new_node->data == curr->data && !(curr->right)){
      curr->right = new_node;
      curr->right->left = NULL;
      curr->right->right = NULL;
      curr->right->parent = curr;
      Rotate(new_node);
      return;
    }
  }
}

void Treap::RotateLeft(shared_ptr<treap_node> new_node){
    if (new_node->heapnumber > new_node->parent->heapnumber){
        return;
    }
    else
    {
        shared_ptr<treap_node>newParent (new treap_node);
        newParent = new_node->parent;
        if (newParent->parent){
            new_node->parent = newParent->parent;
            if (new_node->parent->left == newParent){
                new_node->parent->left = new_node;
            }
            else {
                new_node->parent->right = new_node;
            }
        }
        else{
            new_node->parent = NULL;
        }
        if (new_node->left){
            newParent->right = new_node->left;
            newParent->right->parent = newParent;
        }
        else{
            newParent->right = NULL;
        }
        newParent->parent = new_node;
        new_node->left = newParent;
        if (newParent == root_ptr_){
            root_ptr_ = new_node;
            root_ptr_->parent = NULL;
            return;
        }
    }
}

void Treap::RotateRight(shared_ptr<treap_node> new_node){
    if (new_node->heapnumber > new_node->parent->heapnumber){
        return;
    }
    else
    {
        shared_ptr<treap_node>newParent (new treap_node);
        newParent = new_node->parent;
        if (newParent->parent){
            new_node->parent = newParent->parent;
            if (new_node->parent->left == newParent){
                new_node->parent->left = new_node;
            }
            else {
                new_node->parent->right = new_node;
            }
        }
        else{
            new_node->parent = NULL;
        }
        if (new_node->right){
            newParent->left = new_node->right;
            newParent->left->parent = newParent;
        }
        else{
            newParent->left = NULL;
        }
        newParent->parent = new_node;
        new_node->right = newParent;
        if (newParent == root_ptr_){
            root_ptr_ = new_node;
            root_ptr_->parent = NULL;
            return;
            }
    }
}

void Treap::Remove(int data){
  shared_ptr<treap_node>curr (new treap_node);
  shared_ptr<treap_node>successor (new treap_node);
  curr = GetNode(data);
  if (!curr){
    return;
  }
  numberOfNodes--;
  curr->heapnumber = 1000000;
  if (curr == root_ptr_ && !(curr->left) && !(curr->right)){
      root_ptr_ = NULL;
      return;
  }
  if (!(curr->left) && !(curr->right) && curr->parent){
    if(curr_parent->left == curr){
      curr_parent->left = NULL;
      return;
    }
    else if(curr_parent->right == curr){
      curr_parent->right = NULL;
      return;
    }
  }
  while(curr->left || curr->right){
      if (!curr->left){
          RotateLeft(curr->right);
      }
      else if (!curr->right){
          RotateRight(curr->left);
      }
      else if (curr->left->heapnumber > curr->right->heapnumber){
          RotateLeft(curr->right);
      }
      else{
          RotateRight(curr->left);
      }
  }
  if (curr->parent->left == curr){
      curr->parent->left = NULL;
  }
  else if (curr->parent->right == curr){
      curr->parent->right = NULL;
  }
}

bool Treap::Contains(int ID){
  shared_ptr<treap_node>curr (new treap_node);
  curr = root_ptr_;
  while (curr){
    if (ID < curr->data){
      curr = curr->left;
    }
    else if (ID > curr->data){
      curr = curr->right;
    }
    else if (ID == curr->data){
      return true;
    }
  }
  return false;
}

bool Treap::UpdateInventory(int ID, int quantity){
    shared_ptr<treap_node> curr = GetNode(ID);
    if (curr){
        if (curr->item.quantity + quantity < 0){
            return false;
        }
        curr->item.quantity = curr->item.quantity + quantity;
        return true;
    }
    return false;
}

string Treap::PrintProducts(int data, bool all){
    string s = "";
    InOrder(root_ptr_, data, all, s);
    return s;
}

void Treap::InOrder(shared_ptr<treap_node> curr, int data, bool all, string& s){
    if (curr == NULL){
        return;
    }
    if (curr->left){
        InOrder(curr->left, data, all, s);
    }
    if (all){
        s += "Product: " + curr->item.name + "\n";
        s += "Description: " + curr->item.description + "\n";
        s += "Product ID: " + to_string(curr->item.productID) + "\n";
        s += "Quantity: " + to_string(curr->item.quantity) + "\n\n";
    }
    else if (to_string(curr->data).find(to_string(data)) == 0){
        s += "Product: " + curr->item.name + "\n";
        s += "Description: " + curr->item.description + "\n";
        s += "Product ID: " + to_string(curr->item.productID) + "\n";
        s += "Quantity: " + to_string(curr->item.quantity) + "\n\n";
    }
    if (curr->right){
        InOrder(curr->right, data, all, s);
    }
    if (!(curr->left) && !(curr->right)){
        return;
    }
    return;
}

shared_ptr<treap_node> Treap::GetNode(int data){
  if (!(root_ptr_)){
    return shared_ptr<treap_node>(NULL);
  }
  shared_ptr<treap_node>curr (new treap_node);
  curr = root_ptr_;
  if ( !(curr->left) && !(curr->right) && (data != curr->data)){

    return shared_ptr<treap_node>(NULL);
  }
  while (curr){
    if ( !(curr->left) && !(curr->right) && (data != curr->data)){
      return shared_ptr<treap_node>(NULL);
    }
    if (data < curr->data){
      if (!(curr->left)){
        return shared_ptr<treap_node>(NULL);
      }
      curr_parent = curr;
      curr = curr->left;
    }
    else if (data > curr->data){
      if (!(curr->right)){
        return shared_ptr<treap_node>(NULL);
      }
      curr_parent = curr;
      curr = curr->right;
    }
    if (data == curr->data){
      return curr;
    }
  }
  return shared_ptr<treap_node>(NULL);
}

int Treap::GetInventory(int data){
  shared_ptr<treap_node> curr (new treap_node);
  curr = GetNode(data);
  if (curr){
    return curr->item.quantity;
  }
  else{
    return -1;
  }
}

int Treap::Size(){
  return numberOfNodes;
}

void Treap::ToVector(shared_ptr<treap_node> subt, vector<vector<int>>& vec){
  Traverse(subt, vec);
}

void Treap::Traverse(shared_ptr<treap_node> subt, vector<vector<int>>& vec){
  if (subt == NULL){
    return;
  }

  if (subt->left){
    Traverse(subt->left, vec);
  }
  vec.push_back({subt->data, subt->item.quantity});

  if (subt->right){
    Traverse(subt->right, vec);
  }
  if (!(subt->left) && !(subt->right)){
    return;
  }
}

shared_ptr<treap_node> Treap::GetRoot(){
  return root_ptr_;
}

void Treap::SetRoot(shared_ptr<treap_node> root_ptr){
  root_ptr_ = root_ptr;
}
