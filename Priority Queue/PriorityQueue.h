#ifndef PRIORITYQUEUE_H__
#define PRIORITYQUEUE_H__

#include <memory>
#include <string>
#include <vector>

using namespace std;

struct member {
    float priority;
    string key;
};

struct pq {
    vector<member> data;
};

class PriorityQueue {
public:
    PriorityQueue();

    ~PriorityQueue();

    // allocates memory for a pq structure
    shared_ptr<pq> InitPriorityQueue();

    // insert adds the given text to the queue using the specified
    // priority. If there is a tie, the given string will be placed at
    // the back of the group that it ties with. All other strings with
    // this priority will be removed first.
    void Insert(shared_ptr<pq> queue, string text, float priority);

    // remove will access the highest priority element in the queue,
    // remove it from the queue, and return it. if the queue is empty it
    // should return the empty string.
    string Remove(shared_ptr<pq> queue);

    // peek will access the highest priority element in the queue and
    // return it without modifying the queue. if the queue is empty, returns
    // the empty string.
    string Peek(shared_ptr<pq> queue);

    string Print(shared_ptr<pq> queue);

private:
    shared_ptr<pq> q;
    int size;
};

#endif  // PRIORITYQUEUE_H__
