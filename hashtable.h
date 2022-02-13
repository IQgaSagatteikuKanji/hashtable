#pragma once
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>

class Hashtable{
public:
    size_t  tablesize = 2u,
            filled = 0u;
    std::vector<std::list<std::string>> table;
    size_t hash(const std::string&);
    void resize(size_t);
    bool needs_resize();
    size_t get_next_size();
    bool is_prime(size_t);
    size_t next_prime(size_t);
    void init_vector(std::vector<std::list<std::string>> &);
public:
    Hashtable(){table.resize(tablesize);};
    bool add(const std::string&);
    void remove(const std::string&);
    bool search(const std::string&);
    void clear();
};

void Hashtable::init_vector(std::vector<std::list<std::string>> & vector){
    std::list<std::string> list;
    for(int i = 0; i< tablesize; i++){
        vector[i] = list;
    }
}
bool Hashtable::search(const std::string& str){
    size_t index = hash(str);
    bool found = (std::find(table[index].begin(), table[index].end(), str) != table[index].end());
    return found;
}

bool Hashtable::add(const std::string& str){
    size_t index = hash(str);
    bool found = (std::find(table[index].begin(), table[index].end(), str) != table[index].end());
    if(!found){
        filled++;
        table[index].push_front(str);
        if( needs_resize() ){
            resize(get_next_size());
        }
    }
    return true;
}

void Hashtable::remove(const std::string& str){
    size_t index = hash(str);
    bool found = (std::find(table[index].begin(), table[index].end(), str) != table[index].end());

    if(found){
        filled--;
        table[index].push_front(str);
        //in case someone implements shrinking table to save up it
        if( needs_resize() ){
            resize(get_next_size());
        }
    }
}

void Hashtable::clear(){
    tablesize = 2;
    filled = 0;

    table.clear();
    table.resize(tablesize);
}

size_t Hashtable::get_next_size(){
    return next_prime(2*tablesize);
}

size_t Hashtable::hash(const std::string& str){
    size_t p = 2;

    unsigned long long result =0lu;
    for(int i =0;i<str.size();i++){
        result += ( (int) ( str[i] * pow(2,i) )) % tablesize;
    }
    return result % tablesize;
}

bool Hashtable::needs_resize(){
    return filled >= (tablesize / 2);
}

void Hashtable::resize(size_t new_size){
    std::vector<std::list<std::string>> new_table;
    new_table.resize(new_size);
    tablesize = new_size;
    //init_vector(new_table);
    std::string str;

    for(int i = 0; i<table.size(); i++){
        while(!table[i].empty()){
            str = table[i].front();
            table[i].pop_front();

            new_table[hash(str)].push_front(str);
        }
    }

    table = new_table;
}

bool Hashtable::is_prime(size_t n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;
   
    if (n%2 == 0 || n%3 == 0) return false;
   
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
   
    return true;
}

size_t Hashtable::next_prime(size_t N)
{
 
    if (N <= 1)
        return 2;
 
    int prime = N;
    bool found = false;
 
    while (!found) {
        prime++;
 
        if (is_prime(prime))
            found = true;
    }
 
    return prime;
}