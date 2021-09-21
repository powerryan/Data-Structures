#include "Edge.h"
//#include "Node.h"

Edge::Edge(shared_ptr<Node> n1, shared_ptr<Node> n2) {
    this->a = n1;
    this->b = n2;
}

Edge::~Edge() {
}


shared_ptr<Node> Edge::getStart() {
    return a;
}

shared_ptr<Node> Edge::getEnd() {
    return b;
}

int Edge::getType() {
    return type;
}

void Edge::setType(int edge_type) {
    this->type = edge_type;
}


// overloading operator << lets you put an Edge object into an output
// stream.
ostream &operator << (std::ostream& out, Edge edge) {
    out << *edge.a << " -- " << *edge.b;
    return out;
}
