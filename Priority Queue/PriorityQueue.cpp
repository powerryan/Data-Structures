#include "PriorityQueue.h"
#include <iostream>
using namespace std;


PriorityQueue::PriorityQueue(){
    q = NULL;
    shared_ptr<pq>curr (new pq);
    q = curr;
    size = 0;
}

PriorityQueue::~PriorityQueue(){
}

shared_ptr<pq> PriorityQueue::InitPriorityQueue(){
    member m;
    m.key = "";
    m.priority = 0;
    q->data.push_back(m);
    return q;
}

void PriorityQueue::Insert(shared_ptr<pq> queue, string text, float priority){
    if (q->data.at(0).key == ""){
        size++;
        Remove(q);
    }
    member m;
    m.priority = priority;
    m.key = text;
    q = queue;
    q->data.push_back(m);
    size++;
    int parent = int(size/2) - 1;
    int child = size - 1;
    member temp;
    while (parent >= 0){
        if (q->data.at(parent).priority < q->data.at(child).priority){
            temp = q->data.at(parent);
            q->data.at(parent) = q->data.at(child);
            q->data.at(child) = temp;
            child = parent;
            parent = int(child + 1)/2 - 1;
        }
        else{
            parent = -1;
            break;
        }
    }
}

string PriorityQueue::Remove(shared_ptr<pq> queue){
    q = queue;
    string result = q->data.at(0).key;
    q->data.at(0) = q->data.at(size-1);
    q->data.erase(q->data.begin() + (size - 1));
    size--;
    int parent = 0;
    int l = 2*(parent+1) - 1;
    int r = 2*(parent+1);
    member temp;
    int max = parent;
    while (l < size){
        if (l < size && r < size){
            if (q->data.at(l).priority > q->data.at(r).priority
            && q->data.at(l).priority > q->data.at(parent).priority){
                max = l;
            }
            else if (q->data.at(r).priority > q->data.at(parent).priority){
                max = r;
            }
        }
        else if (l < size && q->data.at(l).priority > q->data.at(parent).priority){
            max = l;
        }
        if (max > parent){
            temp = q->data.at(parent);
            q->data.at(parent) = q->data.at(max);
            q->data.at(max) = temp;
            parent = max;
            l = 2*(parent+1) - 1;
            r = 2*(parent+1);
        }
        else {
            l = size+1;
            break;
        }
    }
    return result;
}

string PriorityQueue::Peek(shared_ptr<pq> queue){
    return queue->data.at(0).key;
}
string PriorityQueue::Print(shared_ptr<pq> queue){
    string result = "";
    cout << "Array:" << endl;
    for (int i = 0; i < size; i++){
        cout << queue->data.at(i).key << endl;
        result = result + " " + queue->data.at(i).key;
    }
    cout << endl << endl;
    return queue->data.at(0).key;
}
