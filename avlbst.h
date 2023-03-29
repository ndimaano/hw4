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
    void insertFix(AVLNode<Key,Value>* oya, AVLNode<Key,Value>* kodomo); //helper function to rebalance after insert
		void removeFix(AVLNode<Key, Value>* nood, int nenDiff); //helper function to rebalance after removal
		void rotateLeft(AVLNode<Key,Value>* kore); //helper function for rotating left
		void rotateRight(AVLNode<Key,Value>* kore); //helper function for rotating right


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
		/*
		more or less literally just copied my implementation of the bst insert function
		and just made some changes to make this work for an AVL tree
		*/
    AVLNode<Key, Value>* pog = new AVLNode<Key, Value>(new_item.first , new_item.second, nullptr); // no need to set balance because the function call automatically makes it 0 if not specified
		AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
		if(this->root_==nullptr) {
			this->root_ = pog;
		}
		else {
			AVLNode<Key, Value>* champ = static_cast<AVLNode<Key,Value>*>(this->internalFind(new_item.first));
			if(champ!=nullptr) {
				delete pog;
				champ->setValue(new_item.second);
				return;
			}
			while(temp != nullptr) {
				if(new_item.first < temp->getKey()) { //handles the case where insert into left subtree
					if(temp->getLeft() == nullptr) {
						pog->setParent(temp);
						temp->setLeft(pog);
						if(pog->getParent()->getBalance()==-1 || pog->getParent()->getBalance()==1) { 
							pog->getParent()->setBalance(0); // changes the balance to 0 to take into account the new node 
						}
						else if(pog->getParent()->getBalance()==0) {
							if(pog==pog->getParent()->getLeft()) {
								pog->getParent()->setBalance(-1); //if the child is added to the left subtree the balance is -1 
							}
							else {
								pog->getParent()->setBalance(1); //if the child is added to the right subtree the balance is 1
							}
							insertFix(pog->getParent(), pog); //call to fix after insertion
						}
						return;
					}
					temp = temp->getLeft();
				}
				if(new_item.first > temp->getKey()) { // handles the case where insert into right subtree
					if(temp->getRight() == nullptr) {
						pog->setParent(temp);
						temp->setRight(pog);
						if(pog->getParent()->getBalance()==-1 || pog->getParent()->getBalance()==1) { 
							pog->getParent()->setBalance(0); // changes the balance if the parent already has another node that isn't the inserted one
						}
						else if(pog->getParent()->getBalance()==0) {
							if(pog==pog->getParent()->getLeft()) {
								pog->getParent()->setBalance(-1);
							}
							else {
								pog->getParent()->setBalance(1);
							}
							insertFix(pog->getParent(), pog);
						}
						return;
					}
					temp = temp->getRight();
				}
			} 
		}
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value> * arimasen = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
		if(arimasen != nullptr) {
			if (arimasen->getLeft() != nullptr && arimasen->getRight()!=nullptr){
				nodeSwap(arimasen, static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(arimasen)));
			}
			int diff= 0;
			AVLNode<Key, Value>* poppy = arimasen->getParent();
			if(arimasen->getParent() != nullptr) {
				if(arimasen->getParent()->getLeft()==arimasen) {
					diff = 1;
				}
				else if (arimasen->getParent()->getRight()==arimasen) {
					diff = -1;
				}
			}
			if (arimasen->getLeft() == nullptr && arimasen->getRight()==nullptr) {
				if(arimasen->getParent()==nullptr) {
					this->root_=nullptr;
				}
				else if (arimasen == arimasen->getParent()->getLeft()) {
					arimasen->getParent()->setLeft(nullptr) ;
				}
				else if(arimasen == arimasen->getParent()->getRight()) {
					arimasen->getParent()->setRight(nullptr);
				}
				delete arimasen;
			}
			else if (arimasen->getLeft() != nullptr && arimasen->getRight()==nullptr) {
				if(arimasen->getParent()==nullptr) {
					arimasen->getLeft()->setParent(nullptr);
					this->root_=arimasen->getLeft();
				}
				else if(arimasen == arimasen->getParent()->getLeft()) {
					arimasen->getParent()->setLeft(arimasen->getLeft()) ;
					arimasen->getLeft()->setParent(arimasen->getParent());
				}
				else if(arimasen == arimasen->getParent()->getRight()) {
					arimasen->getParent()->setRight(arimasen->getLeft());
					arimasen->getLeft()->setParent(arimasen->getParent());
				}
				delete arimasen;
			}
			else if (arimasen->getLeft() == nullptr && arimasen->getRight()!=nullptr) {
				if(arimasen->getParent()==nullptr) {
					arimasen->getRight()->setParent(nullptr);
					this->root_=arimasen->getRight();
				}
				else if(arimasen == arimasen->getParent()->getLeft()) {
					arimasen->getParent()->setLeft(arimasen->getRight());
					arimasen->getRight()->setParent(arimasen->getParent());
				}
				else if(arimasen == arimasen->getParent()->getRight()) {
					arimasen->getParent()->setRight(arimasen->getRight());
					arimasen->getRight()->setParent(arimasen->getParent());
				}
				delete arimasen;
			}
			removeFix(poppy, diff); 
		}
}

// template<class Key, class Value>
// bool AVLTree<Key,Value>::hasChildren(AVLNode<Key,Value>* kore) {
// 	if(kore->getRight() != nullptr || kore->getLeft()!=nullptr){
// 		return true;
// 	}
// 	return false
// }

template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* z) {
	// AVLNode<Key,Value>* Parent = kore->getParent();
	// AVLNode<Key,Value>* leftChild = kore->getLeft();

	// kore->setLeft(leftChild->getRight());

	// if(leftChild->getRight() != nullptr) {
	// 	leftChild->getRight()->setParent(kore);
	// }

	// leftChild->setRight(kore);
	// kore->setParent(leftChild);
	// leftChild->setParent(Parent);

	// if(Parent != nullptr) {
	// 	if(kore == Parent->getLeft()) {
	// 		Parent->setLeft(leftChild);
	// 	}
	// 	if(kore == Parent->getRight()) {
	// 		Parent->setRight(leftChild);
	// 	}
	// }

	if(z->getParent()!=nullptr) {
		if(z==z->getParent()->getLeft()) {
			z->getParent()->setLeft(z->getLeft());
		}
		else if(z==z->getParent()->getRight()) {
			z->getParent()->setRight(z->getLeft());
		}
		if (z->getLeft()!=nullptr) {
			z->getLeft()->setParent(z->getParent());
		}
		z->setParent(z->getLeft());



		if(z->getParent()!=nullptr) {
			z->setLeft(z->getParent()->getRight());
		}
		else {
			z->setLeft(nullptr);
		}

		/*
		After I set a node I have to check if it is a nullptr or not before
		I change its parent pointer or else it will segfault and I did it in both left and right rotate 
		but am noting it here because there is space and I am tired
		*/




		if(z->getLeft()!= nullptr) {
			z->getLeft()->setParent(z);
		}
		if(z->getRight()!=nullptr) {
			z->getRight()->setParent(z);
		}




		if(z->getParent()!=nullptr) {
			z->getParent()->setRight(z);
		}




		return;
	}
	if (z->getLeft()!=nullptr) {
		z->getLeft()->setParent(z->getParent());
	}
	z->setParent(z->getLeft());
	if(z->getParent()!=nullptr) {
		z->setLeft(z->getParent()->getRight());
	}
	else {
		z->setLeft(nullptr);
	}
	if(z->getLeft()!= nullptr) {
		z->getLeft()->setParent(z);
	}
	if(z->getRight()!=nullptr) {
		z->getRight()->setParent(z);
	}
	if(z->getParent()!=nullptr) {
			z->getParent()->setRight(z);
	}
	this->root_ = z->getParent();
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* z) {
	// if(z->getParent()!=nullptr) {
		// 	if(z==z->getParent()->getLeft()) {
		// 		z->getParent()->setLeft(z->getRight());
		// 	}
		// 	else if(z==z->getParent()->getRight()) {
		// 		z->getParent()->setRight(z->getRight());
		// 	}
		// 	z->getRight()->setParent(z->getParent());
		// 	z->setParent(z->getRight());
		// 	z->setRight(z->getParent()->getLeft());
		// 	if(z->getLeft()!=nullptr) {
		// 		z->getLeft()->setParent(z);
		// 	}
		// 	z->getLeft()->setParent(z);
		// 	z->getParent()->setLeft(z);
		// }
		// z->getRight()->setParent(z->getParent());
		// z->setParent(z->getRight());
		// z->setRight(z->getParent()->getLeft());
		// if(z->getLeft()!=nullptr) {
		// 	z->getLeft()->setParent(z);
		// }
		// z->getLeft()->setParent(z);
		// z->getParent()->setLeft(z);
		// this->root_ = z->getParent();
		if(z->getParent()!=nullptr) {
			if(z==z->getParent()->getLeft()) {
				z->getParent()->setLeft(z->getRight());
			}
			else if(z==z->getParent()->getRight()) {
				z->getParent()->setRight(z->getRight());
			}
			if (z->getRight()!=nullptr) {
				z->getRight()->setParent(z->getParent());
			}
			z->setParent(z->getRight());
			if(z->getParent()!=nullptr) {
				z->setRight(z->getParent()->getLeft());
			}
			else {
				z->setRight(nullptr);
			}
			if(z->getRight()!=nullptr) {
				z->getRight()->setParent(z);
			}
			if(z->getLeft()!=nullptr) {
				z->getLeft()->setParent(z);
			}
			if(z->getParent()!=nullptr) {
				z->getParent()->setLeft(z);
			}
			return;
		}
		if (z->getRight()!=nullptr) {
			z->getRight()->setParent(z->getParent());
		}
		z->setParent(z->getRight());




		if(z->getParent()!=nullptr) {
			z->setRight(z->getParent()->getLeft());
		}
		else {
			z->setRight(nullptr);
		}






		if(z->getRight()!=nullptr) {
			z->getRight()->setParent(z);
		}
		if(z->getLeft()!=nullptr) {
			z->getLeft()->setParent(z);
		}

		if(z->getParent()!=nullptr) {
			z->getParent()->setLeft(z);
		}


		this->root_ = z->getParent();
	}



	// AVLNode<Key,Value>* Parent = kore->getParent();
	// AVLNode<Key,Value>* rightChild = kore->getRight();

	// kore->setRight(rightChild->getLeft());

	// if(rightChild->getLeft() != nullptr) {
	// 	rightChild->getLeft()->setParent(kore);
	// }

	// rightChild->setLeft(kore);
	// kore->setParent(rightChild);
	// rightChild->setParent(Parent);

	// if(Parent != nullptr) {
	// 	if(kore == Parent->getLeft()) {
	// 		Parent->setLeft(rightChild);
	// 	}
	// 	if(kore == Parent->getRight()) {
	// 		Parent->setRight(rightChild);
	// 	}
	// }



template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* oya, AVLNode<Key,Value>* kodomo) {
	/*
	basically just follows the implementation from the in class slides
	*/
	if(oya == nullptr || oya->getParent() == nullptr) {
		return;
	}
	AVLNode<Key,Value>*otou = oya->getParent();
	if(oya==otou->getLeft()) {
		otou->updateBalance(-1);
		if(otou->getBalance() == 0) {
			return;
		}
		else if(otou->getBalance()==-1) {
			insertFix(otou, oya);
		}
		else if(otou->getBalance()==-2) {
			if(oya->getLeft()==kodomo) {
				rotateRight(otou);
				oya->setBalance(0);
				otou->setBalance(0);
			}
			else {
				rotateLeft(oya);
				rotateRight(otou);
				if(kodomo->getBalance()==-1) {
					oya->setBalance(0);
					otou->setBalance(1);
					kodomo->setBalance(0);
				}
				else if(kodomo->getBalance()==0) {
					oya->setBalance(0);
					otou->setBalance(0);
					kodomo->setBalance(0);
				}
				else if(kodomo->getBalance()==1) {
					oya->setBalance(-1);
					otou->setBalance(0);
					kodomo->setBalance(0);
				}
			}
		}
	}
	else if(oya==otou->getRight()) {
		otou->updateBalance(1);
		if(otou->getBalance() == 0) {
			return;
		}
		else if(otou->getBalance()==1) {
			insertFix(otou, oya);
		}
		else if(otou->getBalance()==2) {
			if(oya->getRight()==kodomo) {
				rotateLeft(otou);
				oya->setBalance(0);
				otou->setBalance(0);
			}
			else {
				rotateRight(oya);
				rotateLeft(otou);
				if(kodomo->getBalance()==-1) {
					oya->setBalance(1);
					otou->setBalance(0);
					kodomo->setBalance(0);
				}
				else if(kodomo->getBalance()==0) {
					oya->setBalance(0);
					otou->setBalance(0);
					kodomo->setBalance(0);
				}
				else if(kodomo->getBalance()==1) {
					oya->setBalance(0);
					otou->setBalance(-1);
					kodomo->setBalance(0);
				}
			}
		}
	}
}

template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key, Value>* nood, int nenDiff) {
	/*
	basically just follows the implementation from the in class slide
	*/
	if(nood == nullptr) {
		return;
	}
	AVLNode<Key, Value>* oya= nood->getParent();
	int diff = 0;
	if(oya!=nullptr) {
		if(nood == oya->getLeft()) {
			diff = 1;
		}
		else if(nood==oya->getRight()) {
			diff = -1;
		}
	}
	// else if(nood->getLeft()!=nullptr && nood->getRight()!=nullptr) {
	// 	if(nood->getLeft()->getKey() > nood->getRight()->getKey()) {
	// 		c = nood->getLeft();
	// 	}
	// 	else if (nood->getLeft()->getKey() < nood->getRight()->getKey()) {
	// 		c = nood->getRight();
	// 	}
	// }
	// else if(nood->getLeft()==nullptr) {
	// 	c = nood->getRight();
	// }
	// else if(nood->getRight()==nullptr) {
	// 	c = nood->getLeft();
	// }

	if(nenDiff==-1) { // handles the case where the removal is in the left subtree
		if(nood->getBalance() + nenDiff == -2) { // handles a left subtree imbalance
			AVLNode<Key, Value>* c = nood->getLeft();
			if(c->getBalance() == -1) {
				rotateRight(nood);
				nood->setBalance(0);
				c->setBalance(0);
				removeFix(oya, diff);
			}
			else if(c->getBalance()==0) {
				rotateRight(nood);
				nood->setBalance(-1);
				c->setBalance(1);
			}
			else if(c->getBalance()==1) {
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(c); // zig
				rotateRight(nood); //zag
				if(g->getBalance()==1) {
					nood->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0);
				}
				else if(g->getBalance()==0) {
					nood->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if(g->getBalance()==-1) {
					nood->setBalance(1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(oya, diff);
			}
		}
		else if (nood->getBalance() + nenDiff == -1) {
			nood->setBalance(-1); //balanced so done
		}
		else if (nood->getBalance() + nenDiff == 0) {
			nood->setBalance(0);
			removeFix(oya, diff);
		}
		
	}
	else {
		if(nood->getBalance() + nenDiff == 2) {
		AVLNode<Key, Value>* c = nood->getRight();
		if(c->getBalance() == 1) {
			rotateLeft(nood);
			nood->setBalance(0);
			c->setBalance(0);
			removeFix(oya, diff);
		}
		else if(c->getBalance()==0) {
			rotateLeft(nood);
			nood->setBalance(1);
			c->setBalance(-1);
		}
		else if(c->getBalance()==-1) {
			AVLNode<Key, Value>* g = c->getLeft();
			rotateRight(c); // zag
			rotateLeft(nood); //zig
			if(g->getBalance()==1) {
				nood->setBalance(-1);
				c->setBalance(0);
				g->setBalance(0);
			}
			else if(g->getBalance()==0) {
				nood->setBalance(0);
				c->setBalance(0);
				g->setBalance(0);
			}
			else if(g->getBalance()==-1) {
				nood->setBalance(0);
				c->setBalance(1);
				g->setBalance(0);
			}
			removeFix(oya,diff);// recursive call
		}

	}
	else if (nood->getBalance() + nenDiff == 1) {
		nood->setBalance(1); // balanced so done
	}
	else if (nood->getBalance() + nenDiff == 0) {
		nood->setBalance(0);
		removeFix(oya, diff); //recursive call
	}
}
}

// void AVLTree<Key, Value>::baransuChecker(AVLNode<Key, Value>* kore) {
// 	if(abs(kore->getParent()->getBalance()) == 1) {
// 		return;
// 	}
// 	else if (kore->getParent()->getBalance()==0){
// 		if(kore->getParent()->getLeft()==kore) {
// 			kore->getParent()->setBalance(-1);
// 		}
// 		if(kore->getParent()->getRight()==kore) {
// 			kore->getParent()->setBalance(1);
// 		}
// 		insertFix(kore->getParent(), kore);
// 	}
// }


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}



#endif
