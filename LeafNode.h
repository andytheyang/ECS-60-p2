#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
private:
  int *values;
  int transferSize;	// for split
  void sortInsert(int value);
  bool lazyInsert(int value);	// returns true if inserted
  LeafNode* splitInsert(int value);
  int popMin();
  int popMax();
  void updateKeys();
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int getMinimum() const;
  LeafNode* insert(int value); // returns pointer to new Leaf if splits
  // else NULL
  void print(Queue <BTreeNode*> &queue);
}; //LeafNode class

#endif
