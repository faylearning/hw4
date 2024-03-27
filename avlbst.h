#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, int8_t diff);
    void rotateLeft(AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key,Value>* n);
    bool isLeaf(AVLNode<Key, Value>* n);


};

template<typename Key, typename Value>
bool AVLTree<Key, Value>:: isLeaf(AVLNode<Key, Value>* n){
    //helper function to check if a node is a leaf or not 
    if ((n != nullptr) && (n->getLeft() == nullptr) && (n->getRight() == nullptr)){
        return true;
    }else{
        return false; 
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* x){
    //take right child, make it the parent
    //make original parent new left child 

    //take left child, make it parent
    //make original parent the new right child 

    if (x == NULL){
        return;
    }

    //right child
    if (x->getRight() == NULL){
        return;
    }
    AVLNode<Key,Value>* y = x->getRight();

    //grand right child
    // if (x->getRight()->getRight() == NULL){
    //     return;
    // }
    // AVLNode<Key,Value>* x = z->getRight()->getRight();

    AVLNode<Key, Value>* b = y->getLeft();
    AVLNode<Key, Value>* xP = x->getParent();
    if (xP != NULL){
        if (xP->getLeft() == x){
            xP->setLeft(y);
        }else{
            xP->setRight(y);
        }
    }else{
        this->root_ = y;
    }

    y->setLeft(x);
    x->setRight(b);

    if (b != NULL){
        b->setParent(x);
    }
    y->setParent(xP);
    x->setParent(y);

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* z){
    //take left child, make it parent
    //make original parent the new right child 

    if (z == NULL){
        return;
    }

    //left child
    if (z->getLeft() == NULL){
        return;
    }
    AVLNode<Key,Value>* y = z->getLeft();

    //grand left child
    // if (z->getLeft()->getLeft() == NULL){
    //     return;
    // }
    // AVLNode<Key,Value>* x = z->getLeft()->getLeft();

    AVLNode<Key, Value>* c = y->getRight();
    AVLNode<Key, Value>* zP = z->getParent();
    if (zP != NULL){
        if (zP->getLeft() == z){
            zP->setLeft(y);
        }else{
            zP->setRight(y);
        }
    }else{
        this->root_ = y;
    }

    y->setRight(z);
    z->setLeft(c);
    if (c != NULL){
        c->setParent(z);
    }
    
    y->setParent(zP);
    z->setParent(y);

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    AVLNode<Key,Value>* g = p->getParent();
    if ((g == NULL) || (p == NULL)){
        return;
    }

    if (g->getLeft() == p){
        //p is left of g
        g->setBalance(g->getBalance() - 1);
        switch (g->getBalance()) {
            case 0:
                return;
            case -1:
                insertFix(g, p);
                break;
            case -2:
                //zigzig left
                if(p->getLeft()==n){
                    rotateRight(g);
                    g->setBalance(0);
                    p->setBalance(0);
                }else{
                    //zigzag left
                    rotateLeft(p);
                    rotateRight(g);
                    switch (n->getBalance()){
                        case -1: 
                            p->setBalance(0);
                            g->setBalance(1);
                            n->setBalance(0);
                            break;
                        case 0:
                            p->setBalance(0);
                            g->setBalance(0);
                            n->setBalance(0);
                            break;
                        case 1:
                            p->setBalance(-1);
                            g->setBalance(0);
                            n->setBalance(0);
                            break;
                    }
                }
                break;
        }
    }else{
        //p is right of g
        g->setBalance(g->getBalance() + 1);
        switch (g->getBalance()) {
            case 0:
                return;
            case 1:
                insertFix(g, p);
                break;
            case 2:
                if(p->getRight()==n){
                    rotateLeft(g);
                    g->setBalance(0);
                    p->setBalance(0);
                }else{
                    rotateRight(p);
                    rotateLeft(g);
                    switch (n->getBalance()){
                        case 1: 
                            p->setBalance(0);
                            g->setBalance(-1);
                            n->setBalance(0);
                            break;
                        case 0:
                            p->setBalance(0);
                            g->setBalance(0);
                            n->setBalance(0);
                            break;
                        case -1:
                            p->setBalance(1);
                            g->setBalance(0);
                            n->setBalance(0);
                            break;
                    }
                }
                break;
        }
    }
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // if tree empty --> new item is root
    // if just root --> just add new item 
    // not root --> add item & then call insert-fix to rotate and balance 

    const Key& keyy = new_item.first;
    const Value& val = new_item.second;
    AVLNode<Key, Value>* n = new AVLNode<Key, Value>(keyy, val, NULL); 
    // ^^^^^^^ VALGRIND????

    //debugging
    // cout << keyy << ", " << val << endl;

    bool isLeft;
    
    if (this->empty()){
        this->root_ = n;
        return;
    }else{ //not empty, walk tree
        AVLNode<Key, Value>* curr = (AVLNode<Key, Value>*)this->root_;
        while (true){
            if (curr->getKey() == keyy){
                curr->setValue(val);
                delete n;
                return;
            }else if (curr->getKey() > keyy){
                if (curr->getLeft() != NULL){
                    curr = curr->getLeft();
                }else{
                    n->setParent(curr);
                    isLeft = true;
                    curr->setLeft(n);
                    n->setBalance(0);
                    break;
                }
            }else{
                if (curr->getRight() != NULL){
                    curr = curr->getRight();
                }else{
                    n->setParent(curr);
                    isLeft = false;
                    curr->setRight(n);
                    n->setBalance(0);
                    break;
                }
            }
        }
    }

    if (n->getParent() == NULL){
        return;
    }

    int b = n->getParent()->getBalance();
    if ((b == -1) || (b == 1)){
        n->getParent()->setBalance(0);
    }else{
        if (isLeft){
            n->getParent()->setBalance(-1);
        }else{
            n->getParent()->setBalance(1);
        }
        insertFix(n->getParent(), n);
    }
    
    return;
}
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int8_t diff){
    int8_t ndiff; 
    AVLNode<Key, Value>* c;
    AVLNode<Key, Value>* g;

    if (n == NULL){
        return;
    }

    AVLNode<Key, Value>* p = n->getParent();

    if (p != NULL){
        if (p -> getLeft() == n){
            ndiff = 1;
        }else{
            ndiff = -1;
        }
    }

    //case 1
    if ((n->getBalance() + diff) == (2 * diff)){
        if(diff == -1){
            c = n->getLeft();
        }else{
            c = n->getRight();
        }

        //case 1a (zig zig)
        if (c->getBalance() == diff){
            if (diff == -1){
                rotateRight(n);
            }else{
                rotateLeft(n);
            }
            n->setBalance(0);
            c->setBalance(0);
            removeFix(p, ndiff);
            return;
        }

        //case 1b (zig zig)
        if (c->getBalance() == 0){
            if (diff == -1){
                rotateRight(n);
            }else{
                rotateLeft(n);
            }
            n->setBalance(diff);
            c->setBalance(-diff);
            return;
        }

        //case 1c (zig zag)
        if (c->getBalance() == -diff){
            if (diff == -1){
                g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
            }else{
                g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
            }

            if (g->getBalance() == -diff){
                n->setBalance(0);
                c->setBalance(diff);
                g->setBalance(0);
            }else if (g->getBalance() == 0){
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }else if (g->getBalance() == diff){
                n->setBalance(-diff);
                c->setBalance(0);
                g->setBalance(0);
            }
           
            removeFix(p, ndiff);
            return;
        }
    }

    //case 2
    if (n->getBalance() + diff == diff) {
        n->setBalance(diff);
        return;
    }

    //case 3
    if (n->getBalance() + diff == 0) {
        n->setBalance(0);
        removeFix(p, ndiff);
    }

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    int8_t diff = 0;
    AVLNode<Key, Value>* n = (AVLNode<Key, Value>*) (this->internalFind(key));
    if (n == NULL){
        return;
    }

    //two children, swap
    if ((n->getLeft() != NULL) && (n->getRight() != NULL)){
        Node<Key, Value>* pred = BinarySearchTree<Key, Value>::predecessor(n);
        nodeSwap(n, (AVLNode<Key, Value>*)pred);
        // nodeSwap(n, pred);
    }

    AVLNode<Key, Value>* p = n->getParent();

    if (p != NULL){
        bool nIsLeft = false;
        if ((p->getLeft())== n){
            nIsLeft = true;
            diff = 1;
        }else{
            diff = -1;
        }

        if (isLeaf(n) == true){
            //leaf node
            if (nIsLeft){
                p->setLeft(NULL);
            }else{
                p->setRight(NULL);
            }
        }else if ((n->getLeft() != NULL) && (n->getRight() == NULL)){
            //1 left child 
            if (nIsLeft){
                p->setLeft(n->getLeft());
                diff = 1;
            }else{
                p->setRight(n->getLeft()); 
                diff = -1;
            }
            n->getLeft()->setParent(p);
        }else if ((n->getLeft() == NULL) && (n->getRight() != NULL)){
            //1 right child
            if (nIsLeft){
                p->setLeft(n->getRight());
                diff = 1;
            }else{
                p->setRight(n->getRight()); 
                diff = -1;
            }
            n->getRight()->setParent(p);
        }
    }else{
        if (n->getLeft() != NULL){
            this->root_ = n->getLeft();
            (this->root_)->setParent(NULL);
        }else if (n->getRight() != NULL){
            this->root_ = n->getRight();
            this->root_->setParent(NULL);
        }else{
            this->root_ = NULL;
        }

        delete n;
        return;
    }

    delete n;
    removeFix(p, diff);
}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
