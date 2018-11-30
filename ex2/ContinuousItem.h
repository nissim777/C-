/**
 * this file contains header for abstract class ContinousItem
 * and derived classes of it
 */

#ifndef EX2_CONTINUOSITEM_H
#define EX2_CONTINUOSITEM_H

#include "Item.h"

/**
 * this class defines abstract class ContinousItem
 */
class ContinuousItem: public Item
{
public:

    /**
    * getter for quantity field
    */
    virtual double getQuantity() const;

    /**
    * setter for quantity field
    */
    virtual void setQuantity(double num);

    /** virtual destructor to validate no objects will be created */
    virtual ~ContinuousItem() = 0;

protected:
    double _quantity;

    /**
     * constructor for contiuousItem
     */
    ContinuousItem(int catalogId, const string &name, double price,
                   double quantity);

    /**
    * printing object fields
    */
    virtual void printItem() const;

};

/**
 * inline function for pure virtual destructor
 */
inline ContinuousItem::~ContinuousItem()
{
}

/**
 * this class defines item candy
 */
class candy: public ContinuousItem
{
public:
    candy(int catalogId, const string &name, double price,
          double quantity, double calory): ContinuousItem(catalogId, name, price, quantity)
    {
        _calory = calory;
    }

    /**
    * destructor for contiuousItem
    */
    ~candy()
    {
    }
    /**
    * printing object fields
    */
    virtual void printItem() const;
private:
    double _calory;
};

/**
 * this class defines item cloth
 */
class cloth: public ContinuousItem
{
public:
    cloth(int catalogId, const string &name, double price,
          double quantity, double weight) : ContinuousItem(catalogId, name, price, quantity)
    {
        _weight = weight;
    }

    /**
    * destructor for contiuousItem
    */
    ~cloth()
    {
    }
    /**
    * printing object fields
    */
    virtual void printItem() const;

private:
    double _weight;
};

#endif //EX2_CONTINUOSITEM_H
