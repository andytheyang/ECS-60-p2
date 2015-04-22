// Author: Andy Yang
#include <iostream>
#include <cassert>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];

  if (LSize % 2 == 0)	// even number
  {
    // TODO: fix transferSize for odd L
    transferSize = LSize / 2;
  }  // if LSize is even
  else	// if LSize is odd
  {
    transferSize = LSize / 2;
  }  // else
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


void LeafNode::sortInsert(int value)
{
  int i;

  for (i = count; i > 0 && value < values[i - 1]; i--)
    values[i] = values[i - 1];	// move one space down 

  values[i] = value;
  count++;
}  // sortInsert() inserts if there is space

bool LeafNode::lazyInsert(int value)
{
  // TODO: remove this
  return false;
  // TODO: implement this
  LeafNode *left = dynamic_cast<LeafNode *> (leftSibling);

  if (left)  // leftNode exists
  {
    
  }  // exists
  else  // if not (this is the leftmost node)
  {
    LeafNode *right = dynamic_cast<LeafNode *> (rightSibling);

    if (!right)
      return false;	// will only happen if this is root LeafNode

    
  }
  // TODO: updatekeys()
  // TODO: count++;
  return false;	// simulate failure to lazy insert
}  // lazyInsert()

LeafNode* LeafNode::splitInsert(int value)
{
  LeafNode *splitNode = new LeafNode(leafSize, NULL, this, NULL);
  // TODO: garbage cleanup?
  for (int i = 1; i <= transferSize; i++)
  {
    splitNode->sortInsert(values[count - 1]);	// add greatest half
    count--;
  }  // for transferSize

  sortInsert(value);
  splitNode->sortInsert(values[count - 1]);
  count--;

  return splitNode;
}  // splitInsert() inserts when split is needed

LeafNode* LeafNode::insert(int value)
{
  if (count < leafSize)		// if there is space
    sortInsert(value);		// perform regular insert
  else if (!lazyInsert(value))	// attempt lazy insert
    return splitInsert(value);	// if it fails, split (last resort)

  if (parent)
    count--;

  return NULL; // if insert without split (lazy or regular)
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";

  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


