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
        for(std::map<char, Node*>::iterator it = n->children.begin(); it != n->children.end(); ++it)
            deleteAll(it->second);
        delete n;
    }

    void insert(std::string word_){
        Node *curr = _root;
        for(int i = 0; i < word_.length(); i++){
            if(curr->children.find(word_[i]) == curr->children.end())
                curr->children[word_[i]] = new Node(word_);
            curr = curr->children[word_[i]];
        }
    }

    void suggestions(std::string word_){
        Node *curr = _root;
        for(int i = 0; i < word_.length(); i++){
            if(curr->children.find(word_[i]) == curr->children.end())
                return;
            curr = curr->children[word_[i]];
        }
        std::queue<Node*> q;
        q.push(curr);
        while(!q.empty()){
            curr = q.front();
            q.pop();
            if(curr->children.size() == 0)
                std::cout << curr->data << std::endl;
            for(std::map<char, Node*>::iterator it = curr->children.begin(); it != curr->children.end(); ++it)
                q.push(it->second);
        } 
    }
};
