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
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  // students must write this
  // check if there is space

  if (count < leafSize)	// if there is space
  {
    int i;

    for (i = count; i > 0 && value < values[i - 1]; i--)
    {
      values[i] = values[i - 1];	// move one space down 
    }  // sorted insert

    // at this point, i points to position where value must be inserted
    values[i] = value;

    count++;
    return NULL;
  }  // if there is space
  else
  {
    LeafNode *splitNode = NULL;		// IMPLEMENTATION NOT COMPLETE
    return splitNode;
  }
//  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


