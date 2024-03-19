#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

//DELETE !!
using namespace std;
/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); 
    virtual ~BinarySearchTree(); 
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); 
    virtual void remove(const Key& key); 
    void clear(); 
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; 
    Node<Key, Value> *getSmallestNode() const;  
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); 
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    bool isLeaf(Node<Key, Value>* n);
    void clearHelper(Node<Key, Value>* root);
    int balHelper(Node<Key, Value>* curr, bool &bal) const;
    static Node<Key, Value>* successor(Node<Key, Value>* current); 



protected:
    Node<Key, Value>* root_;
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
    : current_(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
    : current_(NULL)
{

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value as 'rhs'
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::
    operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const{
        if (this->current_ == rhs.current_){
            return true;
        }else{
            return false; 
        }
}

/**
* Checks if 'this' iterator's internals have a different value as 'rhs'
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const{
        if (this->current_ == rhs.current_){
            return false;
        }else{
            return true; 
        }

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++(){
    current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(NULL){
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree(){
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>:: print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
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


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // walk tree to find node (INTERNALFIND)
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
    if((n->getLeft() != NULL) && (n->getRight() != NULL)){
            //cout << "two childen" << endl;
            Node<Key, Value>* pred = predecessor(n);
            nodeSwap(n, pred);
            //root_ = pred;
            //nodeSwap(n, predecessor(n));
    }
    Node<Key, Value>* nParent = n->getParent();
    if (nParent == NULL){
        //this means n is the root
        if ((n->getLeft() == NULL) && (n->getRight() == NULL)){
            //cout << "no children" << endl;
            delete n;
            root_ = NULL;

        }else if ((n->getLeft() != NULL) && (n->getRight() == NULL)){
            //cout << "has left child" << endl;
            root_ = n->getLeft();
            n->getLeft()->setParent(NULL);
            delete n;

        }else if ((n->getLeft() == NULL) && (n->getRight() != NULL)){
            //cout << "has right child" << endl;
            root_ = n->getRight();
            n->getRight()->setParent(NULL);
            delete n;

        // }else{
        //     nodeSwap(n, predecessor(n));
        //     n = internalFind(key);
        //     remove(n->getKey());
        }
        return;
    }

    bool nIsLeft = false;
    if ((nParent->getLeft())== n){
        nIsLeft = true;
    }
    if((n->getLeft() != NULL) && (n->getRight() != NULL))
    {
       // cout << "two children" << endl;
        Node<Key, Value>* pred = predecessor(n);
        nodeSwap(n, pred);
            
    }
    if (isLeaf(n) == true){
        //cout << "no children" << endl;
        //leaf node
        if (nIsLeft){
            nParent->setLeft(NULL);
        }else{
            nParent->setRight(NULL);
        }
        delete n;
        return;
    }else if ((n->getLeft() != NULL) && (n->getRight() == NULL)){
       // cout << "left child" << endl;
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
        //cout << "right child" << endl;
        //1 right child
        if (nIsLeft){
            nParent->setLeft(n->getRight());
        }else{
            nParent->setRight(n->getRight()); 
        }
        n->getRight()->setParent(nParent);
        delete n;
        return;
    // }else{
    //     //2 children
    //     nodeSwap(n, predecessor(n));
    //     remove(n->getKey());
    //     return;
    }

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    //pred = next smallest val in tree 
    //left once & right as far 
    //if left child exists, pred is right most node of left tree
    //else walk up ancestor until traverse first right child pointer, its parent is pred
    //if get to root w/o finding node who is right child, no pred 

    //find the first node who is a right child of his 25 parent...that parent is the predecessor

    if (current == NULL){
        return NULL;
    }

    Node<Key, Value>* currLeft = current->getLeft();
    if (currLeft != NULL){
        Node<Key, Value>* currRight = currLeft->getRight();
        if (currRight != NULL){
            Node<Key, Value>* lastRight;
            while (currRight != NULL){
                lastRight = currRight;
                currRight = currRight->getRight();
            }
            return lastRight;
        }else{
            return currLeft;
        }
    }else{
        Node <Key, Value>* par = current->getParent();
        // Node <Key, Value>* grandPar = current->getParent()->getParent();
        if (par == NULL){
            return NULL;
        }
        while (par->getLeft() == current){
            current = par;
            par = par->getParent();
            if (par == NULL){
                return NULL;
            }
        }
        return par;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    //succ = next biggest val in tree 
    //right once & left as far 
    //if right child exists, pred is left most node of right tree
    //else walk up ancestor until traverse first left child pointer, its parent is pred
    //if get to root w/o finding node who is left child, no pred 
    //find the first node who is a left child of his 25 parent...that parent is the predecessor

    if (current == NULL){
        return NULL;
    }

    Node<Key, Value>* currRight = current->getRight();
    if (currRight != NULL){
        Node<Key, Value>* currLeft = currRight->getLeft();
        if (currLeft != NULL){
            Node<Key, Value>* lastLeft;
            while (currLeft != NULL){
                lastLeft = currLeft;
                currLeft = currLeft->getLeft();
            }
            return lastLeft;
        }else{
            return currRight;
        }
    }else{
        Node <Key, Value>* par = current->getParent();
        // Node <Key, Value>* grandPar = current->getParent()->getParent();
        if (par == NULL){
            return NULL;
        }
        while (par->getRight() == current){
            current = par;
            par = par->getParent();
            if (par == NULL){
                return NULL;
            }
        }
        return par;
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* root){
    Node<Key, Value>* curr = root;
    if (curr == NULL){
        return;
    }
    if ((curr->getRight()) != NULL){
        clearHelper(curr->getRight());
    }

    if ((curr->getLeft()) != NULL){
        clearHelper(curr->getLeft());
    }

    delete root;
}

/**
Deletes all nodes inside the tree, resetting it to the empty tree. 
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    clearHelper(root_);
    root_ = NULL;
}




/**
* Returns a pointer to the node with the smallest key.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    if (empty()){
        return NULL;
    }

    Node<Key, Value>* currSmall = root_;
    Node<Key, Value>* L = currSmall->getLeft();

    while(L != NULL){
        currSmall = L;
        L = L->getLeft();
    }

    return currSmall;

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    //less, go left
    //greater, go right 

    Node<Key, Value>* n = root_;
    while (n != nullptr){
        if (n->getKey() == key){
            return n;
        }else if (n->getKey() > key){
            n = n->getLeft();

        }else{
            n = n->getRight();
        }
    }

    //didn't find it
    return nullptr;

}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::balHelper(Node<Key, Value>* curr, bool &bal) const{

    if(curr == NULL){
        bal = true;
        return 0;
    }
    int lheight = balHelper(curr->getLeft(), bal);
    int rheight = balHelper(curr->getRight(), bal);

    if (abs(lheight - rheight) > 1){
        bal = false;
    }
    return max(lheight, rheight) + 1;

}

// template<typename Key, typename Value>
// void BinarySearchTree<Key, Value>::balHelper2(Node<Key, Value>* root, bool &bal, int &height) const{
//     if (root == NULL){
//         return;
//     }
//     Node<Key, Value>* LL = root->getLeft();
//     Node<Key, Value>* RR = root->getRight();
//     int LHeight;
//     int RHeight;

//     if (LL != NULL){
//         balHelper(LL->getLeft(), bal, LHeight);
//         if (bal == false){
//             return;
//         }
//     } else{
//         LHeight = 0;
//     }

//     if (RR != NULL){
//         balHelper(RR->getRight(), bal, RHeight);
//         if (bal == false){
//             return;
//         }
//     }else{
//         RHeight = 0;
//     }

//     if (abs(LHeight - RHeight) < 2){
//         if (LHeight > RHeight){
//             height = LHeight + 1;
//         }else{
//             height = RHeight + 1;
//         }
//         //bal is always true when it reaches here 
//         return;
//     }else{
//         bal = false;
//         return;
//     }
// }

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    //height of left is within 1 of height of its right 

    Node<Key, Value>* currRoot = root_;

    if (currRoot == NULL){
        return true;
    }


    bool ret = true;
    // int height;
    balHelper(root_, ret);
    // cout << ret << endl;
    //balHelper(currRoot, ret, height);

    return ret;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>:: isLeaf(Node<Key, Value>* n){
    //helper function to check if a node is a leaf or not 
    if ((n != nullptr) && (n->getLeft() == nullptr) && (n->getRight() == nullptr)){
        return true;
    }else{
        return false; 
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
