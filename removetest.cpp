
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

#include "bst.h"


template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair){
    //walk the tree try to find same number
    //go left if value less than node, right if value greater than node
    //until find empty location, then insert new val
        //hit null pointer, insert 

    const Key& keyy = keyValuePair.first;
    const Value& val = keyValuePair.second;

    if (empty()){
        root_ = new Node<Key, Value>(keyy, val, NULL);
        return;
    }else{ //not empty, walk tree
        Node<Key, Value>* curr = root_;
        while (true){
            if (curr->getKey() == keyy){
                curr->setValue(val);
                return;
            }else if (curr->getKey() > keyy){
                if (curr->getLeft() != NULL){
                    curr = curr->getLeft();
                }else{
                    curr->setLeft(new Node<Key, Value>(keyy, val, curr));
                    return;
                }
            }else{
                if (curr->getRight() != NULL){
                    curr = curr->getRight();
                }else{
                    curr->setRight(new Node<Key, Value>(keyy, val, curr));
                    return;
                }
            }
        }

    }
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    //walk tree to find node (INTERNALFIND)
    // if 0 children, it's a leaf node so simply remove node and set parent pointer to null
    // if 1 child, promote the child into the node's location
    // if 2 children, swap value w/ its predecessor and remove from new location

    if (root_ == NULL){
        return;
    }
    Node<Key, Value>* n = internalFind(key);
    if (n == NULL){
        return;
    }
    Node<Key, Value>* nParent = n->getParent();
    if (nParent == NULL){
        return;
    }

    bool nIsLeft = false;
    if ((nParent->getLeft())== n){
        nIsLeft = true;
    }

    if (isLeaf(n) == true){
        //leaf node
        if (nIsLeft){
            nParent->setLeft(NULL);
        }else{
            nParent->setRight(NULL);
        }
        delete n;
        return;
    }else if ((n->getLeft() != NULL) && (n->getRight() == NULL)){
        //1 left child 
        if (nIsLeft){
            nParent->setLeft(n->getLeft());
        }else{
            nParent->setRight(n->getLeft()); 
        }
        n->getLeft()->setParent(nParent);
        delete n;
        return;
    }else if ((n->getLeft() == NULL) && (n->getRight() != NULL)){
        //1 right child
        if (nIsLeft){
            nParent->setLeft(n->getRight());
        }else{
            nParent->setRight(n->getRight()); 
        }
        n->getRight()->setParent(nParent);
        delete n;
        return;
    }else{
        //2 children
        nodeSwap(n, predecessor(n));
        remove(n->getKey());
        return;
    }

}

