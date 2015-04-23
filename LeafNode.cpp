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


int LeafNode::popMin()
{
  int ret = getMinimum();

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  count--;
  updateKeys();
  return ret;
}  // popLeft()

int LeafNode::popMax()
{
  count--;
  return values[count];
}  // popRight()

void LeafNode::updateKeys()
{
  // TODO: implement update
  if (parent)
    parent->updateKeys();
}  // updatekeys

void LeafNode::sortInsert(int value)
{
  bool update = value < getMinimum();

  int i;

  for (i = count; i > 0 && value < values[i - 1]; i--)
    values[i] = values[i - 1];	// move one space down 

  values[i] = value;
  count++;

  if (update)
    updateKeys();
}  // sortInsert() inserts if there is space

bool LeafNode::lazyInsert(int value)
{
  // TODO: implement this
  if (leftSibling && leftSibling->getCount() < leafSize)	// has space
  {
    leftSibling->insert(popMin());
    sortInsert(value);
    return true;
  }  // leftSibling has space
  else if (rightSibling && rightSibling->getCount() < leafSize)
  {
    if (value >= values[count - 1])	// greater than max
    {
      rightSibling->insert(value);
      return true;
    }

    rightSibling->insert(popMax());
    sortInsert(value);
    return true;
  }  // rightSibling has space

  return false;	// simulate failure to lazy insert
}  // lazyInsert()

LeafNode* LeafNode::splitInsert(int value)
{
  LeafNode *splitNode = new LeafNode(leafSize, parent, this, rightSibling);

  if (rightSibling)
    rightSibling->setLeftSibling(splitNode);

  setRightSibling(splitNode);

  for (int i = 1; i <= transferSize; i++)
  {
    splitNode->sortInsert(values[count - 1]);	// add greatest half
    count--;
  }  // for transferSize

  sortInsert(value);
  splitNode->sortInsert(values[count - 1]);
  count--;

  // TODO: remove this
  updateKeys();
  return splitNode;
}  // splitInsert() inserts when split is needed

LeafNode* LeafNode::insert(int value)
{
  if (count < leafSize)		// if there is space
    sortInsert(value);		// perform regular insert
  else if (!lazyInsert(value))	// attempt lazy insert
    return splitInsert(value);	// if it fails, split (last resort)

  // TODO: remove this
  updateKeys();
  return NULL; // if insert without split (lazy or regular)
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";

  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


