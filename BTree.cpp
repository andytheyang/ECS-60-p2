// Author: Andy Yang
// Author: Manvinder Sodhi
//#define NDEBUG

#include <iostream>
#include <cassert>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;


BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
  LeafNode *target = dynamic_cast<LeafNode *> (root);

  if (target)  // is a LeafNode
  {
    LeafNode *split = target->insert(value);

    if (split)	// LeafNode needs split
    {
      InternalNode *parent = new InternalNode(internalSize, leafSize, NULL,
                                              NULL, NULL);
      target->setParent(parent);	// set parents to root
      split->setParent(parent);
      parent->insert(target);	// should be on the left
      parent->insert(split);	// should be on the right
      root = parent;
    }  // if split needed
  }  // if target is a LeafNode
  else
    root->insert(value);
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()
