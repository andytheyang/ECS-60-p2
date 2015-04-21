// Author: Andy Yang
#include <iostream>
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
    transferSize = LSize / 2;
    halfSize = transferSize + 1;
  }  // if LSize is even
  else	// if LSize is odd
  {
    transferSize = LSize / 2;
    halfSize = transferSize;
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
  // TODO: implement this
  // TODO: updatekeys()
  // TODO: count++;
  return false;	// simulate failure to lazy insert
}  // lazyInsert()

LeafNode* LeafNode::splitInsert(int value)
{
//  LeafNode *splitNode = NULL;	// placeholder
  LeafNode *splitNode = new LeafNode(leafSize, NULL, this, NULL);
  // TODO: move elements to splitNode
  // TODO: garbage cleanup?
  for (int i = 1; i <= transferSize; i++)
  {
    splitNode->sortInsert(values[--count]);	// add greatest half
  }  // for transferSize

  sortInsert(value);
  splitNode->sortInsert(values[--count]);

  return splitNode;
}  // splitInsert() inserts when split is needed

LeafNode* LeafNode::insert(int value)
{
  if (count < leafSize)		// if there is space
    sortInsert(value);		// perform regular insert
  else if (!lazyInsert(value))	// attempt lazy insert
    return splitInsert(value);	// if it fails, split (last resort)

  return NULL; // if insert without split (lazy or regular)
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


