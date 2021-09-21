#include "Hash.h"
#include <string>
using namespace std;

unsigned int DJB2(std::string key){
    unsigned int hash = 5381;
    for (size_t i=0; i < key.length(); i++) {
        char c = key[i];
        hash = ((hash << 5) + hash) + c;
  }
    return hash;
}

unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap){
    unsigned int b = hashcode % cap;
    return b;
}

// constructor
Hash::Hash(){
    ht = NULL;
    shared_ptr<hash_table>h (new hash_table);
    ht = h;
    }

//deconstructor,
Hash::~Hash(){
}

shared_ptr<hash_table> Hash::InitTable(unsigned int cap){
    shared_ptr<hash_table> ret(new hash_table);
    ret->capacity = cap;
    ret->size = 0;
    ret->occupied = 0;
    ret->table = shared_ptr<htable>(new htable(16));
    for (int i = 0; i < cap; i++){
        ret->table->push_back(shared_ptr<hash_node>(NULL));
    }
    ret->hash_func = DJB2;
    ret->bucket_func = ModuloBucketFunc;
    return ret;
}

shared_ptr<hash_node> Hash::InitNode(std::string key, unsigned int hashcode, std::string val){
    shared_ptr<hash_node> ret(new hash_node);
    ret->deleted = false;
    ret->key = key;
    ret->hashcode = hashcode;
    ret->value= val;
    return ret;
}

bool Hash::SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value){
    if (tbl->size == tbl->capacity){
        return false;
    }
    unsigned int hash = tbl->hash_func(key);
    unsigned int cap = tbl->capacity;
    shared_ptr<hash_node> ret = InitNode(key, hash, value);
    unsigned int index = tbl->bucket_func(hash, cap);
    if (!(tbl->table->at(index))){
        tbl->table->at(index) = ret;
        tbl->size++;
        tbl->occupied++;
        return true;
    }
    if (tbl->table->at(index)->hashcode == hash){
        tbl->table->at(index)->value = value;
        tbl->table->at(index)->deleted = false;
        return true;
    }
    else{
        for (int i = 0; i < tbl->capacity; i++){
            if (!(tbl->table->at((index + i) % tbl->capacity)) || (tbl->table->at((index + i) % tbl->capacity))->deleted == true){
                tbl->table->at((index + i) % tbl->capacity) = ret;
                tbl->size++;
                tbl->occupied++;
                return true;
                }
            }
        }
    return false;
}


float Hash::Load(shared_ptr<hash_table> tbl){
  if (tbl->capacity == 0){
      return 0;
  }
  return float(tbl->size)/tbl->capacity;
}

std::string Hash::GetVal(shared_ptr<hash_table> tbl, std::string key){
    unsigned int hash = tbl->hash_func(key);
    unsigned int cap = tbl->capacity;
    unsigned int index = tbl->bucket_func(hash, cap);
    if (!tbl->table->at(index)){
        return "";
    }
    for (int i = 0; i < tbl->capacity; i++){
        if (!tbl->table->at((index + i) % tbl->capacity)){
            return "";
        }
        if (tbl->table->at((index + i) % tbl->capacity)->key == key &&
            !tbl->table->at((index + i) % tbl->capacity)->deleted){
            return tbl->table->at((index + i) % tbl->capacity)->value;
            }


        if (tbl->table->at((index + i) % tbl->capacity)->key == key &&
            tbl->table->at((index + i) % tbl->capacity)->deleted){
            return "";
            }
    }
    return "";
}

bool Hash::Contains(shared_ptr<hash_table> tbl, std::string key){
    unsigned int hash = tbl->hash_func(key);
    unsigned int cap = tbl->capacity;
    unsigned int index = tbl->bucket_func(hash, cap);
    if (!tbl->table->at(index)){
        return false;
    }
    for (int i = 0; i < tbl->capacity; i++){
        if (!tbl->table->at((index + i) % tbl->capacity)){
            return false;
        }
        if (tbl->table->at((index + i) % tbl->capacity)->key == key &&
            !tbl->table->at((index + i) % tbl->capacity)->deleted){
            return true;
            }
        if (tbl->table->at((index + i) % tbl->capacity)->key == key &&
            tbl->table->at((index + i) % tbl->capacity)->deleted){
            cout << "here3";
            return false;
            }
    }
    return false;
}

bool Hash::Remove(shared_ptr<hash_table> tbl, std::string key){
    if (!Contains(tbl, key)){
        return false;
    }
    else {
        unsigned int hash = tbl->hash_func(key);
        unsigned int cap = tbl->capacity;
        unsigned int index = tbl->bucket_func(hash, cap);
        for (int i = 0; i < tbl->capacity; i++){
            if (tbl->table->at((index + i) % tbl->capacity)->key == key &&
                !tbl->table->at((index + i) % tbl->capacity)->deleted){
                tbl->size--;
                tbl->table->at((index + i) % tbl->capacity)->deleted = true;
                return true;
            }
        }
    }
    return false;
}

void Hash::PrintTable(shared_ptr<hash_table> tbl){
    cout << "Hashtable:" << endl;
    cout << "  capacity: " << tbl->capacity << endl;
    cout << "  size:     " << tbl->size << endl;
    cout << "  occupied: " << tbl->occupied << endl;
    cout << "  load:     " << Load(tbl) << endl;
    if (tbl->capacity < 130) {
        for (unsigned int i=0; i < tbl->capacity; i++) {
            cout << "[" << i << "]    ";
            if (!tbl->table->at(i)) {
                cout << "<empty>" << endl;
            } else if (tbl->table->at(i)->deleted) {
                cout << "<deleted>" << endl;
            } else {
                cout << "\"" << tbl->table->at(i)->key << "\" = \"" << tbl->table->at(i)->value << "\"" << endl;
            }
        }
    } else {
        cout << "<hashtable too big to print out>" << endl;
    }
}
