#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

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
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
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
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		static Node<Key, Value>* successor(Node<Key, Value>* current); // successor function told to implement
		void kuriaNoTasuke(Node<Key, Value> * root); //clear helper that actually takes in a node and can be used to recurse
		bool baransuNoTasuke(Node<Key, Value> * nood, int&kaunto) const; //balance helper pretty much just like the helper from equal-paths.cpp but changed to check for +-1


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
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
{
    // TODO
		current_ = ptr; // current is storing the node we are currently on
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
		current_ = nullptr; // this makes sure that after the iterator is done the pointer is reset for another iteration
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
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		if(current_ == rhs.current_) { //rhs is an iterator and we compare their stored values
			return true;
		}
		return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		if(current_ == rhs.current_) { // == operator with the return values flipped
			return false;
		}
		return true;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		current_ = BinarySearchTree::successor(current_); // moves the iterator to the next node in the tree(the successor)
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
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
		root_ = nullptr; // intializes an empty tree
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		this->clear(); // clears the tree by calling the clear function
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
void BinarySearchTree<Key, Value>::print() const
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
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
		Node<Key, Value>* pog = new Node<Key, Value>(keyValuePair.first , keyValuePair.second, nullptr); // this is the new node to be inserted
		Node<Key, Value>* temp = root_; // this is a temporary node that stores root but can be changed for iteration
		if(root_==nullptr) { // handles the case where the tree is empty
			root_ = pog;
		}
		else {
			Node<Key, Value>* champ = internalFind(keyValuePair.first);
			if(champ!=nullptr) { // if the node already exist it will replace the node's value
				delete pog;
				champ->setValue(keyValuePair.second);
				return;
			}
			while(temp != nullptr) { // if the node is found it will iterate until it reaches the next free child 
				if(keyValuePair.first < temp->getKey()) { //checks if it should go down left tree
					if(temp->getLeft() == nullptr) {
						pog->setParent(temp);
						temp->setLeft(pog);
						return;
					}
					temp = temp->getLeft();
				}
				if(keyValuePair.first > temp->getKey()) { //checks if it should go down right tree
					if(temp->getRight() == nullptr) {
						pog->setParent(temp);
						temp->setRight(pog);
						return;
					}
					temp = temp->getRight();
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
    // TODO
		Node<Key, Value> * arimasen = this->internalFind(key); // temporary node tracking the node that was searched for
		if(arimasen != nullptr) { //handles the case where the node is in the tree 
			if (arimasen->getLeft() != nullptr && arimasen->getRight()!=nullptr){ // flips the node to be removed with its predecessor when the removed node has two children
				nodeSwap(arimasen, BinarySearchTree<Key,Value>::predecessor(arimasen));
			}
			//the code above is called before the rest because after flipping them it becomes a case that can be handled by one of the cases below
			if (arimasen->getLeft() == nullptr && arimasen->getRight()==nullptr) { // this handles the case where the node has no children
				if(arimasen->getParent()==nullptr) {
					root_=nullptr;
				}
				else if (arimasen == arimasen->getParent()->getLeft()) { // this removes the node from the parent if it is the parents left node
					arimasen->getParent()->setLeft(nullptr) ;
				}
				else if(arimasen == arimasen->getParent()->getRight()) { // this removes the node from the parent if it is the parents right ndoe
					arimasen->getParent()->setRight(nullptr);
				}
				delete arimasen;
			}
			else if (arimasen->getLeft() != nullptr && arimasen->getRight()==nullptr) { // this handles the case where the removed node only has a left child
				if(arimasen->getParent()==nullptr) { // handles the case if the removed node has no parent
					arimasen->getLeft()->setParent(nullptr);
					root_=arimasen->getLeft();
				}
				else if(arimasen == arimasen->getParent()->getLeft()) { // handles the case if the removed node is a left child
					arimasen->getParent()->setLeft(arimasen->getLeft()) ;
					arimasen->getLeft()->setParent(arimasen->getParent());
				}
				else if(arimasen == arimasen->getParent()->getRight()) { // handles the case if the removed node is a right child
					arimasen->getParent()->setRight(arimasen->getLeft());
					arimasen->getLeft()->setParent(arimasen->getParent());
				}
				delete arimasen;
			}
			else if (arimasen->getLeft() == nullptr && arimasen->getRight()!=nullptr) { // this handles the case where the removed node only has a right child
				if(arimasen->getParent()==nullptr) { // handles the case if the removed node has no parent
					arimasen->getRight()->setParent(nullptr);
					root_=arimasen->getRight();
				}
				else if(arimasen == arimasen->getParent()->getLeft()) { // handles the case if the removed node is a left child
					arimasen->getParent()->setLeft(arimasen->getRight());
					arimasen->getRight()->setParent(arimasen->getParent());
				}
				else if(arimasen == arimasen->getParent()->getRight()) { // handles the case if the removed node is a right child
					arimasen->getParent()->setRight(arimasen->getRight());
					arimasen->getRight()->setParent(arimasen->getParent());
				}
				delete arimasen;
			}
		}
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
	Node<Key,Value>* mae; // node that stores the front(mae means forward or in front in japanese)
	if(current->getLeft() != nullptr) { // handles the case where the node has a left child
		mae = current->getLeft(); 
		while(mae->getRight() != nullptr) { // we loop through the right children to find the largest of the left side
			mae = mae->getRight();
		}
		return mae;
	}
	else { // handles the case where the node is a right child
		while(current->getParent() != nullptr) { // loops through the left children to find the smallest of the right side
			if(current->getParent()->getRight() == current) {
				return current->getParent();
			}
			current= current->getParent();
		}
	}
	return nullptr;

}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current) 
{
	Node<Key, Value>* ato;
	if(current->getRight() != nullptr) {
		ato = current->getRight();
		while(ato->getLeft() != nullptr) {
			ato = ato->getLeft();
		}
		return ato;
	}
	else {
		while(current->getParent() != nullptr) {
			if(current->getParent()->getLeft() == current) {
				return current->getParent();
			}
			current= current->getParent();
		}
	}
	return nullptr;

}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
		kuriaNoTasuke(root_); // call to recursive function that clears from the root
		root_ = nullptr;
}

template<typename Key, typename Value> //I created this function because I wanted to just work directly with the root
void BinarySearchTree<Key, Value>::kuriaNoTasuke(Node<Key,Value>* root) {
		if(root==nullptr) {

		}
		else {
			kuriaNoTasuke(root->getLeft());
			kuriaNoTasuke(root->getRight());
			delete root;
		}
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
		if(root_ == nullptr) { // handles the case where the tree is empty
			return nullptr;
		}
		else { // handles the case where the tree has stuff
			Node<Key, Value> * chisaii = root_;
			while(chisaii->getLeft() != nullptr) { // loops through until it reaches the last left node, checks if it is the last left node by checking if it does not have a left child
				chisaii = chisaii->getLeft(); 
			}
			return chisaii;
		}
		return nullptr;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	Node<Key, Value> * kensaku = root_;
		while(kensaku != nullptr) {
			if(kensaku->getKey() == key) {
				return kensaku;
			}
			else if (key < kensaku->getKey()) {
				kensaku = kensaku->getLeft();
			}
			else if (key > kensaku->getKey()){
				kensaku = kensaku->getRight();
			}
		}
	return nullptr;
}


/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
		int kaunto = 0;
		return baransuNoTasuke(root_, kaunto);
}

template<typename Key, typename Value> // I more or less just took this one from my equal paths and adjusted it to also be valid whenever it is within 1 height instead of equal
bool BinarySearchTree<Key, Value>::baransuNoTasuke(Node<Key, Value>* nood, int& kaunto) const {
	if(nood == nullptr) {
        return true;
    }
    int migikaunto=0;
    int hidarikaunto=0;
    bool hidari = baransuNoTasuke(nood->left_, hidarikaunto);
    bool migi = baransuNoTasuke(nood->right_, migikaunto);
    if (hidari && migi) {
        if(migikaunto==hidarikaunto || migikaunto == hidarikaunto-1 || migikaunto == hidarikaunto+1 || hidarikaunto == migikaunto -1  || hidarikaunto == migikaunto  + 1 ) {
            if(hidarikaunto >= migikaunto) {
                kaunto = hidarikaunto + 1;
                return true;
            }
            else {
                kaunto = migikaunto + 1;
                return true;
            }
        }
        else {
            return false;
        }
    } 
    else {
        return false;
    }
    return false;
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
