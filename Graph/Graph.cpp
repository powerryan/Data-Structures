#include "Graph.h"
//#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  directed = false; // graphs are undirected by default
  cleared = false;
}

Graph::~Graph() {
}

vector<shared_ptr<Node>> Graph::getNodes() {
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  return edges;
}

int Graph::getClock() {
  return clock;
}

void Graph::addNode(shared_ptr<Node> n) {
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  edges.push_back(e);
}

void Graph::removeNode(shared_ptr<Node> n) {
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(shared_ptr<Edge> e) {
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
       it != edges.end();
       it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  directed = val;
}

bool Graph::isDirected() {
  return directed;
}

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    shared_ptr<Node> ter = *it;
    ter->clear();
  }
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> ter = *it;
    ter->setType(9);
}
  clock = 0;
}

void Graph::tick(string message) {
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(shared_ptr<Node> start) {
  if (!cleared){
      clear();
      cleared = true;
  }
  start->setColor(2, clock);
  set<shared_ptr<Edge>> ret = getAdjacentEdges(start);
  set<shared_ptr<Edge>>:: iterator it;
  for (it = ret.begin(); it != ret.end(); it++){
      shared_ptr<Edge> ter = *it;
      if (start == ter->getStart() && (ter->getEnd()->getColor() == 2 || ter->getEnd()->getColor() == 3)){
          if (ter->getStart()->isAncestor(ter->getEnd())){
            ter->setType(12);
          }
          else {
              ter->setType(11);
          }
      }
      if (start == ter->getEnd() && (ter->getStart()->getColor() == 2 || ter->getEnd()->getColor() == 3)){
          if (ter->getEnd()->rank > ter->getStart()->rank){
            ter->setType(11);
          }
          else {
              ter->setType(12);
          }
      }
      if (start == ter->getStart() && ter->getEnd()->getColor() == 1){
          ter->setType(10);
          ter->getEnd()->setPredecessor(start);
          clock++;
          dfs(ter->getEnd());
      }
      else if (start == ter->getEnd() && ter->getStart()->getColor() == 1){
          ter->setType(10);
          ter->getStart()->setPredecessor(start);
          clock++;
          dfs(ter->getStart());
      }
  }
  clock++;
  start->setColor(3, clock);
}

void Graph::bfs(shared_ptr<Node> start) {
  clear();
  vector<shared_ptr<Node>> queue;
  shared_ptr<Node> current = start;
  queue.insert(queue.begin() +0, start);
  start->setColor(2, clock);
  start->setRank(0);
  set<shared_ptr<Edge>> ret;
  while (queue.size()>0){
    current = queue.back();
    clock++;
    current->setColor(3, clock);
    if (current->getPredecessor()){
        current->setRank(current->getPredecessor()->getRank() + 1);
    }
    queue.pop_back();
    ret = getAdjacentEdges(current);
    set<shared_ptr<Edge>>:: iterator it;
    for (it = ret.begin(); it != ret.end(); it++){
        shared_ptr<Edge> ter = *it;
        if (current == ter->getStart() && ter->getEnd()->getColor() == 1){
            queue.insert(queue.begin() + 0, ter->getEnd());
            clock++;
            ter->setType(10);
            ter->getEnd()->setColor(2, clock);
            ter->getEnd()->setPredecessor(current);
        }
        else if (current == ter->getEnd() && ter->getStart()->getColor() == 1){
            queue.insert(queue.begin() + 0, ter->getStart());
            clock++;
            ter->setType(10);
            ter->getStart()->setColor(2, clock);
            ter->getStart()->setPredecessor(current);
        }
    }
  }
}


void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> finish) {
  clear();
  vector<shared_ptr<Node>> queue;
  shared_ptr<Node> current = start;
  queue.insert(queue.begin() +0, start);
  start->setColor(2, clock);
  start->setRank(0);
  set<shared_ptr<Edge>> ret;
  while (queue.size()>0){
    current = queue.back();
    clock++;
    current->setColor(3, clock);
    if (current->getPredecessor()){
        current->setRank(current->getPredecessor()->getRank() + 1);
    }
    queue.pop_back();
    if (current == finish){
        return;
    }
    ret = getAdjacentEdges(current);
    set<shared_ptr<Edge>>:: iterator it;
    for (it = ret.begin(); it != ret.end(); it++){
        shared_ptr<Edge> ter = *it;
        if (current == ter->getStart() && ter->getEnd()->getColor() == 1){
            queue.insert(queue.begin() + 0, ter->getEnd());
            clock++;
            ter->getEnd()->setColor(2, clock);
            ter->getEnd()->setPredecessor(current);
        }
        else if (current == ter->getEnd() && ter->getStart()->getColor() == 1){
            queue.insert(queue.begin() + 0, ter->getStart());
            clock++;
            ter->getStart()->setColor(2, clock);
            ter->getStart()->setPredecessor(current);
        }
    }
  }
}

ostream &operator << (ostream& out, Graph graph) {
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

string what(int& v) {
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

string make_dot(Graph* g) {
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }

  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}
