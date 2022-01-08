package com.zdhcode;

import java.util.*;

class Trie{

    public static class Node{
        String data;
        Map<Character, Node> edges;
        Node(String data){
            this.data = data;
            this.edges = new HashMap<>();
        }
    }

    private final Node root;

    public Trie(){ root = new Node(null); }

    public void insert(String word){
        Node nav = root;
        String currentWord = "";
        boolean foundLetter;

        for(int i = 0; i < word.length(); i++){
            foundLetter = false;
            currentWord = currentWord.concat(Character.toString(word.charAt(i)));
            for(Map.Entry<Character,Node> e : nav.edges.entrySet()) {
                if(e.getKey().equals(word.charAt(i))){
                    foundLetter = true;
                    nav = e.getValue();
                    break;
                }
            }
            if(!foundLetter){
                nav.edges.put(word.charAt(i), new Node(word));
                return;
            }
        }
    }

    public void suggestions(String word){
        Node curr = root;
        boolean foundLetter;

        for(int i = 0; i < word.length(); i++){
            foundLetter = false;
            for(Map.Entry<Character, Node> e : curr.edges.entrySet()){
                if(e.getKey().equals(word.charAt(i))){
                    foundLetter = true;
                    curr = e.getValue();
                    break;
                }
            }
            if(!foundLetter)
                break;
        }

        List<Node> todo = new LinkedList<>();

        if(word.equals("")){ // print all values
            for(Map.Entry<Character, Node> e : curr.edges.entrySet()){
                Node source = e.getValue();
                todo.add(source);
                while(!todo.isEmpty()){
                    source = todo.get(0);
                    if(!source.data.equals(word))
                        System.out.println(source.data);
                    todo.remove(0);
                    for(Map.Entry<Character,Node> e2 : source.edges.entrySet())
                        todo.add(e2.getValue());
                }
            }
        }else{
//            BFS
            todo.add(curr);
            while(!todo.isEmpty()){
                curr = todo.get(0);
                if(!curr.data.equals(word))
                    System.out.println(curr.data);
                todo.remove(0);
                for(Map.Entry<Character,Node> e : curr.edges.entrySet())
                    todo.add(e.getValue());
            }
        }
    }
}

public class Main {

    public static void main(String[] args) {
        Trie trie = new Trie();

        trie.insert("t");
        trie.insert("A");
        trie.insert("i");
        trie.insert("in");
        trie.insert("inn");
        trie.insert("to");
        trie.insert("te");
        trie.insert("tea");
        trie.insert("ted");
        trie.insert("ten");
        trie.insert("apple");

        trie.suggestions("");
    }
}
