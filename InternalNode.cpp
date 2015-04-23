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
  transferSize = ISize / 2;
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

// returns location to insert
BTreeNode* InternalNode::findLoc(int value)
{
  int i = 0;
  bool found = false;

  while(!found)
  {
    if (i == 0 && value < keys[i])
      break;
    else if (i == (count - 1) && value >= keys[i])
      break;
    else if (value >= keys[i] && value < keys[i + 1])
      break;

    i++;
  }  // while not found

  return children[i];
}  // findloc()

InternalNode* InternalNode::insert(int value)
{
  BTreeNode *target = findLoc(value);
  BTreeNode *split = target->insert(value);

  if (split)
  {
    if (count < internalSize)         // if there is space
      sortInsert(split);          // perform regular insert
    else if (!lazyInsert(split))  // attempt lazy insert 
    {
      return splitInsert(split);  // if it fails, split (last resort)
    }
  }

  return NULL; // if insert without split (lazy or regular)
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

  // TODO: remove this
  updateKeys();
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


void InternalNode::updateKeys()
{
  // TODO: don't call above if min isn't changed
  for (int i = 0; i < count; i++)
  {
    if (keys[i] != children[i]->getMinimum())
      keys[i] = children[i]->getMinimum();
  }

  if (parent)
    parent->updateKeys();
}

BTreeNode* InternalNode::popMin()
{
  BTreeNode *ret = children[0];

  for(int i = 0; i < count - 1; i++)
  {
    keys[i] = keys[i + 1];
    children[i] = children[i + 1];
  }

  count--;
  updateKeys();
  return ret;
}  // popLeft()

BTreeNode* InternalNode::popMax()
{
  count--;
  return children[count];
}  // popRight()

void InternalNode::sortInsert(BTreeNode *value)
{
//  bool update = value->getMinimum() < getMinimum();
  int i;

  for (i = count; i > 0 && value->getMinimum() < children[i - 1]->getMinimum(); i--)
  {
    children[i] = children[i - 1];
    keys[i] = keys[i - 1];  // move one space down 
  }

  keys[i] = value->getMinimum();
  children[i] = value;
  count++;

//  if (update)
    updateKeys();
}  // sortInsert() inserts if there is space

bool InternalNode::lazyInsert(BTreeNode *value)
{
  if (leftSibling && leftSibling->getCount() < internalSize)        // has space
  {
    InternalNode *left = dynamic_cast<InternalNode *> (leftSibling);
    assert(left);

    left->insert(popMin());
    sortInsert(value);
    return true;
  }  // leftSibling has space
  else if (rightSibling && rightSibling->getCount() < internalSize)
  {
    InternalNode *right = dynamic_cast<InternalNode *> (rightSibling);
    assert(right);

    if (value->getMinimum() >= children[count - 1]->getMinimum())     // greater than max
    {
      right->insert(value);
      return true;
    }

    right->insert(popMax());
    sortInsert(value);
    return true;
  }  // rightSibling has space

  return false; // simulate failure to lazy insert
}  // lazyInsert()

InternalNode* InternalNode::splitInsert(BTreeNode *value)
{
  InternalNode *splitNode = new InternalNode(internalSize, leafSize, parent, this, rightSibling);

  if (rightSibling)
    rightSibling->setLeftSibling(splitNode);

  setRightSibling(splitNode);

  for (int i = 1; i <= transferSize; i++)
  {
    splitNode->sortInsert(children[count - 1]);   // add greatest half
    count--;
  }  // for transferSize

  sortInsert(value);
  splitNode->sortInsert(children[count - 1]);
  count--;

  // TODO: remove this
  updateKeys();
  return splitNode;
}  // splitInsert() inserts when split is needed

/*
InternalNode* InternalNode::insert()
{
  if (count < leafSize)         // if there is space
    sortInsert(value);          // perform regular insert
  else if (!lazyInsert(value))  // attempt lazy insert 
    return splitInsert(value);  // if it fails, split (last resort)

  return NULL; // if insert without split (lazy or regular)
}  // LeafNode::insert()
*/
