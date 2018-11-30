/**
 * this file contains header for abstract class item
 * base to abstract classes discretItem and continuousItem
 */
#ifndef EX2_ITEM_H
#define EX2_ITEM_H

#include <iostream>
#include <string>

using namespace std;
/**
 * this class defines abstract class item
 */
class Item
{
public:

    /**
    * getter func for name field
    */
    const string &getName() const;

    /**
    * getter func for id field
    */
    int getId() const;

    /**
    * getter func for isDiscret field
    */
    bool getIsDiscret() const;

    /**
    * getter func for quantity (pure virtual)
    */
    virtual double getQuantity() const = 0;

    /**
    * setter func for quantity (pure virtual)
    */
    virtual void setQuantity(double num) = 0;

    /**
    * overloading for < operator (compare by catalogID)
    */
    bool operator<(const Item &other) const;

    /**
    * overloading for printing operator
    */
    friend std::ostream& operator<<(std::ostream &o, Item &obj);

    /**
    * destructor for Item object
    */
    virtual ~Item()
    {

    }

protected:
    int _catalogId;
    string _name;
    double _price;
    bool _isDiscret;

    /**
    * constructor for Item object (used for delegation)
    */
    Item (int catalogId, const string &name, double price);


    /**
    * printing object fields
    */
    virtual void printItem() const;
};

#endif //EX2_ITEM_H
