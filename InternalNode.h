#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  int transferSize;
  BTreeNode **children;
  int *keys;
  BTreeNode *findLoc(int value);
  void sortInsert(BTreeNode *value);
  bool lazyInsert(BTreeNode *value);   // returns true if inserted
  InternalNode* splitInsert(BTreeNode *value);
  BTreeNode* popMin();
  BTreeNode* popMax();
public:
  InternalNode(int ISize, int LSize, InternalNode *p,
    BTreeNode *left, BTreeNode *right);
  int getMinimum()const;
  InternalNode* insert(int value); // returns pointer to new InternalNode
    // if it splits else NULL
  void insert(BTreeNode *oldRoot, BTreeNode *node2); // if root splits use this
  void insert(BTreeNode *newNode); // from a sibling
  void print(Queue <BTreeNode*> &queue);
  void updateKeys();
}; // InternalNode class

#endif
