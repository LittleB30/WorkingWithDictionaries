// Implementation file for AVL search tree

#include "AVLDictionary.h"

int max(int x, int y)
{
  if (x > y)
    return x;
  else
    return y;
}

AVLDictionary::AVLDictionary()
{
  root = NULL;
  size = 0;
}

AVLDictionary::AVLDictionary(const AVLDictionary& orig)
{
  this->copyDict(orig);
}

AVLDictionary::~AVLDictionary()
{
  this->deleteDict();
}

AVLDictionary& AVLDictionary::operator=(const AVLDictionary& orig)
{
  if (this->root != orig.root)
    {
      this->deleteDict();
      this->copyDict(orig);
    }
  return *this;
}


int getNodeHeight(AVLTreeNode* t)
{
  return t == NULL ? -1 : t->height;
}

void rotateWithLeftChild(AVLTreeNode*& k2)
{
  AVLTreeNode* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max(getNodeHeight(k2->left), getNodeHeight(k2->right)) + 1;
  k1->height = max(getNodeHeight(k1->left), k2->height) + 1;
  k2 = k1;
}

void rotateWithRightChild(AVLTreeNode*& k2)
{
  AVLTreeNode* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  k2->height = max(getNodeHeight(k2->left), getNodeHeight(k2->right)) + 1;
  k1->height = max(k2->height, getNodeHeight(k1->left)) + 1;
  k2 = k1;
}

void doubleWithLeftChild(AVLTreeNode*& k3)
{
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

void doubleWithRightChild(AVLTreeNode*& k3)
{
  rotateWithLeftChild(k3->right);
  rotateWithRightChild(k3);
}

void insert(AVLTreeNode* p, AVLTreeNode*& t)
{

  if (t == NULL)
    t = p;
  else
    {
      if (p->data < t->data) // headed left
	{
	  insert(p, t->left);
	  if ( getNodeHeight(t->left) - getNodeHeight(t->right) == 2)
	    if (p->data < t->left->data)
	      rotateWithLeftChild(t);
	    else
	      doubleWithLeftChild(t);
	}
      else
	{
	  insert(p, t->right);
	  if (getNodeHeight(t->right) - getNodeHeight(t->left) == 2)
	    if (p->data > t->right->data)
	      rotateWithRightChild(t);
	    else
	      doubleWithRightChild(t);
	}
    }
  t->height =max(getNodeHeight(t->left), getNodeHeight(t->right)) + 1;
}

void AVLDictionary::addEntry(string anEntry)
{
  // create the node
  AVLTreeNode* p = new AVLTreeNode;
  p->data = anEntry;
  p->height = 0;
  p->left = NULL;
  p->right = NULL;
  
  insert(p, root);
}

bool AVLDictionary::findEntry(string key)
{
  AVLTreeNode* q = root;
  bool found = false;

  while (!found && q)
    {
      if (q->data == key)
	{
	  found = true;
	}
      else if (q->data < key)
	{
	  q = q->right;
	}
      else
	{
	  q = q->left;
	}
    }
  return found;
}
	
void printInOrder(AVLTreeNode* p, ostream& outStream)
{
  if (p)
    {
      printInOrder(p->left, outStream);
      outStream << p->data << endl;
      printInOrder(p->right, outStream);
    }
}

void AVLDictionary::printSorted(ostream& outStream)
{
  printInOrder(root,outStream);
}

AVLTreeNode* copyTree(const AVLTreeNode* node)
{
  if (!node)
    return NULL;
  else
    {
      AVLTreeNode* newNode = new AVLTreeNode;
      newNode->data = node->data;
      newNode->height = node->height;
      newNode->left = copyTree(node->left);
      newNode->right = copyTree(node->right);
      return newNode;
    }
}

void AVLDictionary::copyDict(const AVLDictionary& orig)
{
  this->size = orig.size;
  this->root = copyTree(orig.root);
}

void deleteTree(AVLTreeNode* node)
{
  if (node)
    {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
}

void AVLDictionary::deleteDict()
{
  deleteTree(this->root);
  this->root = NULL;
}
