/**
 * This file contains implemntation for the methods of the class my_set
 * which contains big_integer and using nested class node for implemntation
 *
 * BONUS: mergeSort was used in order to print in ascending order.
 * running complexibiliy: o(n log n) (log n recursive calls, each time o(n) for merging the ORDERED 2 set members)
 *
 * created by: black_knight
 */

#include "my_set.h"
#include<iostream>

using namespace std;

/**
 * default constructor
 */
my_set::my_set() :_start(nullptr), _size(0)
{
}

/**
* copy constructor
* important note: stores at reverse order
*/
my_set::my_set(const my_set &my_set):_start(nullptr)
{
    node* mySetCurrNode = my_set._start;
    while(mySetCurrNode != nullptr)
    {
        this->add(mySetCurrNode->getNum());
        mySetCurrNode = mySetCurrNode->getNext();
    }
    _size = my_set._size;
}

/**
* destructor
*/
my_set::~my_set()
{
    _destruct(_start);
}

/**
* helper recursive function in order to destruct all nodes in the linked list
*/
void my_set::_destruct (node *p)
{
    if(!p)
    {
        return;
    }
    _destruct(p->getNext());
    delete p;
}

/**
* checks if member is in the set.
* @returns: true iff is in the set.
*/
bool my_set::is_in_set (const big_integer &numObj)const
{
    node* currNode = _start;
    while (currNode != nullptr)
    {
        if(currNode->getNum() == numObj)
        {
            return true;
        }
        currNode = currNode->getNext();
    }
    return false;
}

/**
* adds member to the set, in case not existed yet.
* @returns: true iff was added to the set.
*/
bool my_set::add(const big_integer &numObj)
{
    if (!is_in_set(numObj))
    {
        // adds to beginning
       node* toAdd = new node(numObj);
       toAdd->setNext(_start);
       _start = toAdd;
        _size++;
        return true;
    }
    return false;
}

/**
* removes member from the set, in case existes.
* @returns: true iff was removed from the set.
*/
bool my_set::remove(const big_integer &numObj)
{
    if(is_in_set(numObj))
    {
        node* currNode = _start, *previousNode = nullptr;
        // find node
        while (currNode->getNum() != numObj)
        {
            previousNode = currNode;
            currNode = currNode->getNext();
        }
        // remove node
        if (previousNode == nullptr)
        {
            _start = currNode->getNext();
        }
        else
        {
            previousNode->setNext(currNode->getNext());
        }
        delete currNode;
        _size--;
        return true;
    }
    return false;
}

/**
* calculates the sum of members in the set.
* @returns: (an big_integer) number of the sum of members.
*/
big_integer my_set::sum_set ()const
{
    node* currNode = _start;
    big_integer sum;
    while (currNode != nullptr)
    {
        sum += currNode->getNum();
        currNode = currNode->getNext();
    }
    return sum;
}

/**
* union operator between 2 sets
*/
my_set my_set::operator|(const my_set &other) const
{
    my_set unionSet = *this;
    node* otherCurrNode = other._start;
    while (otherCurrNode != nullptr)
    {
        unionSet.add(otherCurrNode->getNum());
        otherCurrNode = otherCurrNode->getNext();
    }
    return unionSet;
}

/**
 * intersection operator between 2 sets
 */
my_set my_set::operator&(const my_set &other) const
{
    // intersection = A
    my_set intersection(*this);
    node* intersectionCurrNode = intersection._start;
    node* intersectionNextsNode = nullptr;

    // intersection/(!B)
    while (intersectionCurrNode != nullptr)
    {
        intersectionNextsNode = intersectionCurrNode->getNext();
        if (!other.is_in_set(intersectionCurrNode->getNum()))
        {
            intersection.remove(intersectionCurrNode->getNum());
        }
        intersectionCurrNode = intersectionNextsNode;
    }
    return intersection;
}

/**
 * difference operator between 2 sets
 */
my_set my_set::operator-(const my_set &other) const
{
    my_set intersection = *this&other;
    my_set difference(*this);
    node* intersectionCurrNode = intersection._start;
    // A/(A intersection B)
    while(intersectionCurrNode != nullptr)
    {
        difference.remove(intersectionCurrNode->getNum());
        intersectionCurrNode = intersectionCurrNode->getNext();
    }
    return difference;
}

/**
* assignment operator between 2 sets
*/
my_set& my_set::operator=(const my_set &other)
{
    if (this != &other)
    {
        while (_start != nullptr)
        {
            this->remove(_start->getNum());
        }
        node *otherCurrNode = other._start;
        while (otherCurrNode != nullptr)
        {
            this->add(otherCurrNode->getNum());
            otherCurrNode = otherCurrNode->getNext();
        }
        _size = other._size;
    }
    return *this;
}

/**
 * an overloading for the [printing] operator << printing in ascending order
 */
std::ostream& operator<<(std::ostream &o, const my_set &mySet)
{
    if (mySet._size == 0)
    {
        return o << endl;
    }
    my_set toPrint;
    toPrint = mySet._validatedMergSort();
    my_set::node* currNode = toPrint._start;
    // print members one by one
    while (currNode != nullptr)
    {
        o << currNode->getNum() << endl;
        currNode = currNode->getNext();
    }
    return o;
}

/**
* merge sort helper function: valdites correct printing order
* note: activates only once (activates the mergSore)
*/
const my_set my_set::_validatedMergSort () const
{
    my_set toReturn, toReturnCopy;
    toReturn = my_set::_mergSort(*this);
    // validate order
    if (toReturn._size > 1)
    {
        if (toReturn._start->getNum() > toReturn._start->getNext()->getNum())
        {
            toReturnCopy = toReturn;
            return toReturnCopy;
        }
    }
    return toReturn;
}

/**
* mergSort: recursive sorting algorithm operates at O(n log n)
* divides the set into 2 parts, each of them sending again recursively
* and being sorted by merge at the end.
*/
my_set my_set::_mergSort (const my_set &mySet)
{
    my_set newSet, firstSet, secondSet;
    node* currNode = mySet._start;
    if (mySet._size == 1)
    {
        return mySet;
    }
    // divide
    for(unsigned int i = 0; i < mySet._size; i++)
    {
        if (i < mySet._size / 2)
        {
            firstSet.add(currNode->getNum());
        }
        else
        {
            secondSet.add(currNode->getNum());
        }
        currNode = currNode->getNext();
    }
    firstSet = _mergSort(firstSet);
    secondSet = _mergSort(secondSet);
    return newSet = _merge(firstSet, secondSet);
}


/**
* merge sort helper function: merges two ORDERED partitions into one
*/
my_set my_set::_merge (const my_set &firstSet, const my_set &secondSet)
{
    unsigned int totalSize = firstSet._size + secondSet._size;
    my_set toReturn;
    node *firstIndex = firstSet._start, *secondIndex = secondSet._start;
    for(unsigned int i = 0; i < totalSize; i++)
    {
        if (firstIndex == nullptr)
        {
            toReturn.add(secondIndex->getNum());
            secondIndex = secondIndex->getNext();
        }
        else if (secondIndex == nullptr)
        {
            toReturn.add(firstIndex->getNum());
            firstIndex = firstIndex->getNext();
        }
        else
        {
            if (firstIndex->getNum() < secondIndex->getNum())
            {
                toReturn.add(firstIndex->getNum());
                firstIndex = firstIndex->getNext();
            }
            else
            {
                toReturn.add(secondIndex->getNum());
                secondIndex = secondIndex->getNext();
            }
        }
    }
    return toReturn;
}

/* ---------- NESTED CLASS --------------------------*/

/**
* getter: returns the number stored in the node
*/
const big_integer& my_set::node::getNum()
{
    return _num;
}

/**
* getter: returns the next node in the linked list
*/
my_set::node* my_set::node::getNext()
{
    return _next;
}

/**
* setter: sets the next node in the linked list
*/
void my_set::node::setNext(node* other)
{
    _next = other;
}