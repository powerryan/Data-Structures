#include "Node.h"

Node::Node(string s) {
  data = s;
}

Node::~Node() {
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  return data;
}

int Node::getColor() {
  return color;
}

void Node::setRank(int r) {
  rank = r;
}

void Node::clear() {
  color = 1;
  discovery_time = -1;
  completion_time = -1;
  rank = -1;
  predecessor = NULL;
}

void Node::setColor(int search_color, int time) {
  if (search_color == 1){
    clear();

  }
  else if (search_color == 2){
      color = search_color;
      discovery_time = time;
  }
  else if (search_color == 3){
      color = search_color;
      completion_time = time;
  }

}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time,
				   int& finish_time, int& bfs_rank) {
  thecolor = color;
  disco_time = discovery_time;
  finish_time = completion_time;
  bfs_rank = rank;
}

bool Node::isAncestor(shared_ptr<Node> other) {
    if (this == other.get()){
          return true;
      }
    Node *curr = this;
    while (curr->predecessor){
      if (curr->predecessor == other){
          return true;
      }
      if (curr->predecessor->predecessor){
      curr->predecessor = curr->predecessor->predecessor;
      }
      else {
          return false;
      }
  }
  return false;
}

void Node::setPredecessor(shared_ptr<Node> other) {
  this->predecessor = other;
}
shared_ptr<Node> Node::getPredecessor() {
  return this->predecessor;
}
int Node::getRank() {
  return this->rank;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  out << node.data;
  return out;
}
