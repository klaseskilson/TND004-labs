/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r) {
  l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node() {
  if (!l_thread)
    delete left;
  if (!r_thread)
    delete right;
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v) {
  if (l_thread && v.first < value.first) {
    Node* p = new Node(v, left, this);
    left = p;
    left->l_thread = left->r_thread = true;
    l_thread = false;
    return true;
  } else if (r_thread && value.first < v.first) {
    Node* p = new Node(v, this, right);
    right = p;
    right->l_thread = right->r_thread = true;
    r_thread = false;
    return true;
  } else if (!l_thread && v.first < value.first) {
    return left->insert(v);
  } else if (!r_thread && v.first > value.first) {
    return right->insert(v);
  }

  return false;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight) {
  if (key < value.first)
  {
    if (l_thread)
    {
        return false;
    }
    else
    {
        return left->remove(key, this, false);
    }
  }
  else if (value.first < key)
  {
      if(r_thread)
      {
          return false;
      }
      else
      {
          return right->remove(key, this, true);
      }
  }
  else if (!l_thread && !r_thread)
  {
    // replace this value with smallest value
    value = right->findMin()->value;
    return right->remove(value.first, this, true);
  }
  else if (key == value.first)
  {
    removeMe(parent, isRight);
    return true;
  }

  //return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight) {
  if (!isRight) {
    // case 1
    if (!r_thread) {
      // case 1a
      // move parent
      parent->left = right;
      // move thread if right->left is a thread
      right->findMin()->left = left;
    } else if (!l_thread) {
      // case 1b
      parent->left = left;
      left->findMax()->right = parent;
    } else {
      // case 1c
      parent->l_thread = true;
      parent->left = left;
    }
  } else {
    // case 2
    if (!r_thread) {
      // case 2a
      // move parent's right
      parent->right = right;
      left->findMin()->right = parent;
    } else if (!l_thread) {
      // case 2b
      parent->right = left;
      left->findMax()->right = right;
    } else {
      // case 2c
      parent->r_thread = true;
      parent->right = right;
    }
  }

  l_thread = r_thread = true;
  // somehow delete this node
  delete this;
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key) {
  if (key < value.first && !l_thread)
    return left->find(key);
  else if (value.first < key && !r_thread)
    return right->find(key);
  else if (value.first == key)
    return this;

  // not found
  return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin() {
  if (!l_thread)
    return left->findMin();

  return this;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax() {
  if (!r_thread)
    return right->findMax();

  return this;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const {
  if (!l_thread) //display left sub-tree
    left->display();

  cout << value.first << " "; //display key stored in the node

  if (!r_thread) //display right sub-tree
    right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
