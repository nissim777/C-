/**
 * This file contains a represntation for set and enables operations between sets:
 * union, intersection, difference and printing by order.
 *
 * BONUS: mergeSort was used in order to print in ascending order.
 * running complexibiliy: o(n log n) (log n recursive calls, each time o(n) for merging the ORDERED 2 set members)
 *
 * created by: black_knight
 */

#ifndef EX0_SET_H
#define EX0_SET_H

#include "big_integer.h"

/**
 * This class contains an implementation of sets storing big_integer objects in a linked list.
 */
class my_set
{
public:
    /**
    * default constructor
    */
    my_set();

    /**
    * copy constructor
    */
    my_set(const my_set &my_set);

    /**
    * destructor
    */
    ~my_set();

    /**
    * checks if member is in the set.
    * @returns: true iff is in the set.
    */
    bool is_in_set (const big_integer &numObj)const;

    /**
    * adds member to the set, in case not existed yet.
    * @returns: true iff was added to the set.
    */
    bool add(const big_integer &numObj);

    /**
    * removes member from the set, in case existes.
    * @returns: true iff was removed from the set.
    */
    bool remove(const big_integer &numObj);

    /**
    * calculates the sum of members in the set.
    * @returns: (an big_integer) number of the sum of members.
    */
    big_integer sum_set ()const;

    /**
    * union operator between 2 sets
    */
    my_set operator|(const my_set &other ) const;

    /**
    * intersection operator between 2 sets
    */
    my_set operator&(const my_set &other ) const;

    /**
    * difference operator between 2 sets
    */
    my_set operator-(const my_set &other ) const;

    /**
    * assignment operator between 2 sets
    */
    my_set& operator=(const my_set &other);

    /**
    * an overloading for the [printing] operator << to be used by the class
    * printing in ascending order
    */
    friend std::ostream& operator<<(std::ostream &o, const my_set &mySet);

private:
    /**
    * nested class contains the represntation of single member in the set (contains big_integer)
    */
    class node
    {
    public:
       /**
       * constructor of a node
       */
       node(const big_integer &num): _next(nullptr), _num(num)
       {
       };
       /**
       * getter: returns the number stored in the node
       */
        const big_integer &getNum();
        /**
        * getter: returns the next node in the linked list
        */
        node *getNext();

        /**
        * setter: sets the next node in the linked list
        */
        void setNext(node *other);

    private:
        node* _next;
        big_integer _num;
    };

    node* _start;
    unsigned int _size;

    /**
    * helper recursive function in order to destruct all nodes in the linked list
    */
    void _destruct (node *p);

    /**
    * mergSort: recursive sorting algorithm operates at O(n log n)
    * divides the set into 2 parts, each of them sending again recursively
    * and being sorted by merge at the end.
    * complexity time: O(n log n)
    */
    static my_set _mergSort (const my_set &mySet);

    /**
    * merge sort helper function: merges two ORDERED partitions into one
    */
    static my_set _merge (const my_set &firstSet, const my_set &secondSet);

    /**
    * merge sort helper function: valdites correct printing order
    * note: activates only once
    */
    const my_set _validatedMergSort () const;
};

#endif //EX0_SET_H
