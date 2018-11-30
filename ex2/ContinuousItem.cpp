/**
 * this file contains implemntion for abstract class ContiniousItem
 * and derived classes of it
 */

#include "ContinuousItem.h"

/**
 * constructor for contiuousItem
 */
ContinuousItem::ContinuousItem(int catalogId, const string &name, double price,
                               double quantity) : Item(catalogId, name, price)
{
    _quantity = quantity;
    _isDiscret = false;
}

/**
* see header for details
*/
double ContinuousItem::getQuantity() const
{
    return _quantity;
}

/**
* see header for details
*/
void ContinuousItem::setQuantity(double num)
{
    _quantity = num;
}

/**
 * printing object fields
 */
void ContinuousItem::printItem () const
{
    Item::printItem();
    cout << "Quantity: " << _quantity << endl;
    cout << "Price: " << _price << endl;
}

/**
 * printing object fields
 */
void candy::printItem () const
{
    ContinuousItem::printItem();
    cout << "Calories: " << _calory << endl;
}

/**
 * printing object fields
 */
void cloth::printItem () const
{
    ContinuousItem::printItem();
    cout << "Weight: " << _weight << endl;
}