/**
 * this file contains implmention for abstract class item
 */

#include "Item.h"


/**
* constructor for Item object (used for delegation)
*/
Item::Item (int catalogId, const string &name, double price): _catalogId(catalogId), _name(name),
_price (price), _isDiscret(false)
{
}

/**
* see header for details
*/
const string& Item::getName() const
{
    return _name;
}

/**
* see header for details
*/
int Item::getId() const
{
    return _catalogId;
}

/**
* see header for details
*/
bool Item::getIsDiscret() const
{
    return _isDiscret;
}

/**
* overloading for < operator (compare by catalogID)
*/
bool Item::operator<(const Item &other) const
{
    return this->_catalogId < other._catalogId;
}

/**
* printing object fields
*/
void Item::printItem () const
{
    cout << "Item: " << _catalogId << endl;
    cout << "Name: " << _name << endl;
}

/**
* overloading for printing operator
*/
std::ostream& operator<<(std::ostream &o, Item &obj)
{
    obj.printItem();
    return o;
}