#include<iostream>
#include<map>
#include<queue>

class Trie{

    struct Node{
        std::string data;
        std::map<char, Node*> children;
        Node(std::string d) : data(d) { }
    };

private:
    Node *_root;

public:
    Trie() : _root(new Node("")) { }

    ~Trie(){ deleteAll(_root); }

    void deleteAll(Node *n){
        if(n == nullptr) return;
        for(auto child : n->children)
            deleteAll(child.second);
        delete n;
    }

    void insert(std::string word_){
        Node *curr = _root;
        for(char c : word_){
            if(curr->children.find(c) == curr->children.end())
                curr->children[c] = new Node(word_);
            curr = curr->children[c];
        }
    }

    void suggestions(std::string word_){
        Node *curr = _root;
        for(char c : word_){
            if(curr->children.find(c) == curr->children.end())
                return;
            curr = curr->children[c];
        }
        std::queue<Node*> q;
        q.push(curr);
        while(!q.empty()){
            curr = q.front();
            q.pop();
            if(curr->children.size() == 0)
                std::cout << curr->data << std::endl;
            for(auto it : curr->children)
                q.push(it.second);
        } 
    }
};
