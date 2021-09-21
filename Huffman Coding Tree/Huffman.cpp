#include "Huffman.h"

// constructor
Huffman::Huffman(){
    tree = NULL;
    shared_ptr<tree_queue>n (new tree_queue);
    tree = n;
}

//deconstructor,
Huffman::~Huffman(){
}

shared_ptr<freq_info> Huffman::CreateLeaf(char symbol, int count) {
    shared_ptr<freq_info> node (new freq_info);
    node->symbol = symbol;
    node->count = count;
    node->is_leaf = true;
    node->left = shared_ptr<freq_info>(NULL);
    node->right = shared_ptr<freq_info>(NULL);
    return node;
}

shared_ptr<freq_info> Huffman::CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right) {
    shared_ptr<freq_info> node (new freq_info);
    node->count = left->count + right->count;
    node->is_leaf = false;
    node->left = left;
    node->right = right;
    return node;
}

void Huffman::IncrementLookup(map<char, int>& lookup, char symbol) {
    if (lookup.find(symbol) == lookup.end()){
        lookup[symbol] = 1;
  }
    else{
        lookup[symbol]++;
  }
}

void Huffman::LoadQueue(const map<char, int>& lookup, tree_queue& q) {
    shared_ptr<freq_info>node (new freq_info);
    for (auto &keys : lookup){
        node = CreateLeaf(keys.first, keys.second);
        q.push(node);
    }
}

shared_ptr<freq_info> Huffman::BuildTree(tree_queue& q) {
    shared_ptr<freq_info>one(new freq_info);
    shared_ptr<freq_info>two(new freq_info);
    while (q.size() > 1){
        one = q.top();
        q.pop();
        two = q.top();
        q.pop();
        q.push(CombineNodes(one, two));

    }
    return q.top();
}
void Huffman::Traverse(shared_ptr<freq_info> current, shared_ptr<freq_info> parent, map<char,string>& mymap, string path){
    if (current->is_leaf){
        mymap[current->symbol] = path;
    }
    if (current->left){
        Traverse(current->left, current, mymap, path + LEFT_CHAR);
    }
    if (current->right){
        Traverse(current->right, current, mymap, path + RIGHT_CHAR);
    }

}

map<char, string> Huffman::BuildEncodingTable(shared_ptr<freq_info> root) {
    map<char, string> mymap;
    shared_ptr<freq_info> current = root;
    string path = "";
    Traverse(current, root, mymap, path);
    return mymap;
}

string Huffman::Encode(map<char, string> enc_table, string input) {
    string code = "";
    for(char const &c: input){
        code += enc_table[c];
    }
    return code;
}

string Huffman::Decode(shared_ptr<freq_info> root, string input) {
    shared_ptr<freq_info> current (new freq_info);
    current = root;
    string code = "";
    while (input.size() > 0){
        if (current->is_leaf){
            code += current->symbol;
            current = root;
        }
        if (input.at(0) == '.'){
            input.erase(0,1);
            current = current->left;
        }
        else if (input.at(0) == '^'){
            input.erase(0,1);
            current = current->right;
        }
    }
    if (current->is_leaf){
        code += current->symbol;
        current = root;
    }
    return code;
}
