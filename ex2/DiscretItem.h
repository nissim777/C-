/**
 * this file contains header for abstract class DiscretItem
 * and derived classes of it
 */

#ifndef EX2_DISCRETITEM_H
#define EX2_DISCRETITEM_H

#define DIMENSION_NUM 3
#include "Item.h"

/**
 * this class defines abstract class DiscretItem
 */
class DiscretItem: public Item
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
    virtual ~DiscretItem () = 0;

protected:
    int _quantity;

    /**
     * constructor for DiscretItem
     */
    DiscretItem(int catalogId, const string &name, double price,
                int quantity);

    /**
    * printing object fields
    */
    virtual void printItem() const;
};

/**
* inline function for pure virtual destructor
*/
inline DiscretItem::~DiscretItem(){}

/**
 * this class defines item furniture
 */
class furniture: public DiscretItem
{
public:

    /**
    * constructor for furniture
    */
    furniture(int catalogId, const string &name, double price,
              int quantity, const double dim[], string material, string color);
   /**
   * destructor for furniture
   */
    ~furniture()
    {
    }
    /**
     *
    * printing object fields
    */
    virtual void printItem() const;

private:
    double _dimensions[DIMENSION_NUM];
    string _material;
    string _color;
};

/**
 * this class defines item kitchen_tool
 */
class kitchenTool: public DiscretItem
{
public:
    /**
    * constructor for kitchen tool
    */
    kitchenTool(int catalogId, const string &name, double price,
                int quantity, const double dim[], double capacity);
    /**
    * destructor for kitchen tool
    */
    ~kitchenTool ()
    {
    }
    /**
    * printing object fields
    */
    virtual void printItem() const;

private:
    double _dimensions[DIMENSION_NUM];
    double _capacity;

};

/**
 * this class defines item movie_or_book
 */
class movieOrBook: public DiscretItem
{
public:
    /**
    * constructor for movie_or_book
    */
    movieOrBook(int catalogId, const string &name, double price,
                int quantity, const string &author, int publishYear, int length);

    /**
    * destructor for movie_or_book
    */
    ~movieOrBook ()
    {
    }

    /**
    * printing object fields
    */
    virtual void printItem() const;
private:
    string _author;
    int _publishYear;
    int _length;
};

#endif //EX2_DISCRETITEM_H
