#include "LinkedList.h"
#include <iostream>
#include <string>
using namespace std;

// constructor
LinkedList::LinkedList(){ 
  top_ptr_ = NULL;
}

//deconstructor
LinkedList::~LinkedList(){
}

shared_ptr<node> LinkedList::InitNode(int data){
  shared_ptr<node> ret(new node);
  // Your code here
  ret->data = data;
  ret->next = NULL;
  return ret;
}

string LinkedList::Report(){
  string ret = "";
  shared_ptr<node> currNode(new node);
  currNode = top_ptr_;
  while (currNode){
    ret = ret + to_string(currNode->data) + " ";
    currNode = currNode->next;
  }
  return ret;
}

void LinkedList::AppendData(int data){
  shared_ptr<node> newNode(new node);
  newNode->data = data;
  newNode->next = NULL;
  Append(newNode);
}

void LinkedList::Append(shared_ptr<node> new_node){
  shared_ptr<node> currNode(new node);
  shared_ptr<node> lastNode(new node);
  currNode = top_ptr_;
  if (!currNode){
    top_ptr_ = new_node;
    top_ptr_->next = NULL; 
  }
  else {
    while (currNode){
      lastNode = currNode;
      currNode = currNode->next;
  }
    lastNode->next = new_node;
    new_node->next = NULL;
  }
}

void LinkedList::InsertData(int offset, int data){
  shared_ptr<node> newNode(new node);
  newNode->data = data;
  newNode->next = NULL;
  Insert(offset, newNode);
}

void LinkedList::Insert(int offset, shared_ptr<node> new_node){
  shared_ptr<node> currNode(new node);
  shared_ptr<node> pNode(new node);
  currNode = top_ptr_;
  if (offset == 0){
    new_node->next = top_ptr_;
    top_ptr_ = new_node;
  }
  else if (offset == this->Size()){
    while (currNode){
      pNode = currNode;
      currNode = currNode->next;
  }
    pNode->next = new_node;
    new_node->next = currNode;
  }  
  
  else if (offset < this->Size()){
    int i = 0;
    while (i < offset){
      pNode = currNode;
      currNode = currNode->next;   
      i++;
  }
    pNode->next = new_node;
    new_node->next = currNode;
  }
}

void LinkedList::Remove(int offset){
  int i = 0;
  shared_ptr<node> currNode(new node);
  currNode = top_ptr_;
  shared_ptr<node> pNode(new node);
  if (offset == 0 && currNode){
      top_ptr_ = currNode->next;   
  }
  else if (offset > 0 && offset < this->Size()){
    while(i < offset){   
      pNode = currNode;
      currNode = currNode->next;  
      i++;
    }
      pNode->next = currNode->next;
  }
}

int LinkedList::Size(){
  int ret = 0;
  shared_ptr<node> currNode(new node);
  currNode = top_ptr_;
  while (currNode){
    ret++;
    currNode = currNode->next;
  }
  return ret;
}

bool LinkedList::Contains(int data){
  bool ret = false;
  shared_ptr<node> currNode(new node);
  currNode = top_ptr_;
  while (currNode){
    if (currNode->data == data){
      ret = true;
      break;
    }
    currNode = currNode->next;
  }
  return ret;
}

shared_ptr<node> LinkedList::GetTop(){
  return top_ptr_;
}

void LinkedList::SetTop(shared_ptr<node> top_ptr){
  top_ptr_ = top_ptr;
}
