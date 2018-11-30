/**
 * this file contains implemtion for abstract class DiscretItem
 * and derived classes of it
 */

#include "DiscretItem.h"

#define DIMENSION_NUM 3

/**
 * constructor for discretItem
 */
DiscretItem::DiscretItem(int catalogId, const string &name, double price,
                         int quantity) : Item(catalogId, name, price)
{
    _quantity = quantity;
    _isDiscret = true;
}

/**
* see header for details
*/
double DiscretItem::getQuantity() const
{
    return _quantity;
}

/**
* see header for details
*/
void DiscretItem::setQuantity(double num)
{
    _quantity = (int)num;
}

/**
* see header for details
*/
void DiscretItem::printItem () const
{
    Item::printItem();
    cout << "Quantity: " << _quantity << endl;
    cout << "Price: " << _price << endl;
}

/**
 * constructor for furniture
 */
furniture::furniture(int catalogId, const string &name, double price,
                     int quantity, const double dim[], string material, string color):
        DiscretItem(catalogId, name, price, quantity)
{
    for(int i = 0; i < DIMENSION_NUM; i++)
    {
        _dimensions[i] = dim[i];
    }
    _material = material;
    _color = color;
}

/**
* printing object fields
*/
void furniture::printItem () const
{
    DiscretItem::printItem();
    cout << "Dimensions: ";
    for(int i = 0; i < DIMENSION_NUM; i++)
    {
        cout << _dimensions[i];
        if (i != DIMENSION_NUM - 1)
        {
            cout << " ";
        }
    }
    cout << endl;
    cout << "Material: " << _material << endl;
    cout << "Color: " << _color << endl;
}

/**
 * constructor for kitchentool
 */
kitchenTool::kitchenTool(int catalogId, const string &name, double price,
                         int quantity, const double dim[], double capacity):
        DiscretItem(catalogId, name, price, quantity)
{
    for(int i = 0; i < DIMENSION_NUM; i++)
    {
        _dimensions[i] = dim[i];
    }
    _capacity = capacity;
}

/**
 * printing object fields
 */
void kitchenTool::printItem () const
{
    DiscretItem::printItem();
    cout << "Dimensions: ";
    for(int i = 0; i < DIMENSION_NUM; i++)
    {
        cout << _dimensions[i];
        if (i != DIMENSION_NUM - 1)
        {
            cout << " ";
        }
    }
    cout << endl;
    cout << "Capacity: " << _capacity << endl;
}

/**
 * constructor for movieOrBook
 */
movieOrBook::movieOrBook (int catalogId, const string &name, double price,
                          int quantity, const string &author,
                          int publishYear, int length):
        DiscretItem(catalogId, name, price, quantity)
{
     _author = author;
     _publishYear = publishYear;
    _length = length;
}

/**
* printing object fields
*/
void movieOrBook::printItem () const
{
    DiscretItem::printItem();
    cout << "Author: " << _author << endl;
    cout << "Year of publication: " << _publishYear << endl;
    cout << "Length: " << _length << endl;
}
