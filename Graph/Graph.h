#ifndef GRAPH_H__
#define GRAPH_H__

#include <vector>
#include <set>
#include <string>
#include <memory>
#include <queue>
#include "Edge.h"
//#include "Node.h"

using namespace std;

class Graph {
public:
  bool cleared;
  bool directed;
  vector<shared_ptr<Node>> nodes;
  vector<shared_ptr<Edge>> edges;
  vector<shared_ptr<Edge>> search_edges;
  vector<shared_ptr<Node>> search_nodes;
  int clock;
  Graph();
  ~Graph();
  vector<shared_ptr<Node>> getNodes();
  vector<shared_ptr<Edge>> getEdges();
  int getClock();
  void addNode(shared_ptr<Node> n);
  void addEdge(shared_ptr<Edge> e);
  void removeNode(shared_ptr<Node> n);
  void removeEdge(shared_ptr<Edge> e);
  bool isDirected();
  void setDirected(bool val);
  set<shared_ptr<Edge>> getAdjacentEdges(shared_ptr<Node> n);
  friend std::ostream &operator << (std::ostream& out, Graph graph);

  // clear resets all nodes to have WHITE color, with -1 discovery and
  // finish times and rank. Resets all edges to type
  // UNDISCOVERED_EDGE. It resets the graph clock to 0.
  void clear();

  void tick(string message);

  // dfs(start) runs a depth-first search from the indicated start
  // node, and explores all reachable nodes. This ignores unreachable
  // nodes. When this function returns, all explored nodes are colored
  // BLACK, all unreachable nodes are WHITE. All explored nodes have
  // correct discovery/exit time information. All edges have correct
  // edge types (unfollowed edges should remain UNDISCOVERED).
  void dfs(shared_ptr<Node> start);


  // bfs(start) runs a breadth-first search starting from the given
  // node. It sets the 'rank' value on all nodes to something
  // appropriate: -1 for unreachable nodes, 0 for the start node, 1
  // for nodes that are one edge from the start node, and so forth.
  void bfs(shared_ptr<Node> start);

  // bfs(start, target) has the same requirements as the other version
  // of `bfs`, except this one stops after the target node is
  // reached. If found, the target node should be marked BLACK, and
  // its rank should be correctly set on exit. If it is not found, the
  // target node should remain WHITE with a rank of -1.
  void bfs(shared_ptr<Node> start, shared_ptr<Node> target);

private:

};

#endif  // GRAPH_H__
