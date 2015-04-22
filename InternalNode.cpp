#include <cassert>
#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


BTreeNode* InternalNode::findLoc(int value)
{
  int i = -1;
  bool found = false;

  while(!found)
  {
    i++;
    if (i == 0 && value < keys[i])
      found = true;
    else if (i == count && value >= keys[i - 1])
      found = true;
    else if (value >= keys[i - 1] && value < keys[i])
      found = true;
  }  // while not found

  cout << "Location: " << i << endl;
  return children[i];
}  // findloc()

InternalNode* InternalNode::insert(int value)
{
  // TODO: deal with self-splitting
  BTreeNode *target = findLoc(value);
  BTreeNode *split = target->insert(value);
  // TODO: deal with splitting children

  // students must write this
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  // students must write this
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  int i;
  int newKey = newNode->getMinimum();

  for (i = count; i > 0 && newKey < keys[i - 1]; i--)
  {
    children[i] = children[i - 1];  // move one space down
    keys[i] = keys[i - 1];  // move one space down
  }  // semiinsertion sort

  children[i] = newNode;
  keys[i] = newKey;
  count++;
  // students may write this
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);
} // InternalNode::print()


