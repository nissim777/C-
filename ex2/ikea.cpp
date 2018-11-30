/**
 * this file contains the main program invoking the parser in order to validate
 * and create items and managing & printing the stock of the store.
 */

#include <algorithm>
#include "Parser.h"

#define END_ITEM_LINE "-----"
#define MENU_LENGTH 7
#define BY_NAME false
#define TO_SELL true

#define DOUBLE true
using namespace std;

/**
* read from file and attempt to create item objects
*/
void readFromFile(const string &fileString, vector<Item*> &v);

/**
 * main function activate other functions according to user choice at menu
 */
void commandCenter(vector<Item*> &v, int choice);

/**
 * prints the main menu
 */
void printMenu();

/**
 * order vector by catalog number or by name
 */
void orderVector (vector<Item*> &v, bool byCatalog = true);

/**
 * name comparator for vector
 */
bool nameComparator(const Item *first, const Item *second);

/**
 * number comparator for vector
 */
bool numberComparator(const Item *first, const Item *second);

/**
 * sell item. return true iff item exists with enough stock for selling
 */
bool sellItem(Item &i);

/**
 * add an item object to suitable place in a vector ordered by catalog Id
 */
void addToOrderedVector(vector<Item*> &v, Item* itemToAdd);

/**
* find an item by catalog number. also attempts to sell in case toSell is true
*/
void printByCatalogId (vector<Item *> &v, int num, bool toSell = false);

/**
* find an item by catalog number. also attempts to sell in case toSell is true
*/
void printByName (vector<Item *> &v, const string &name);

/**
* print stock by citem atalog Id (vector always will be ordered like that as default)
*/
void printByCatalogId(const vector<Item*> &v);

/**
* print stock by item name
*/
void printByName(vector<Item*> &v);

/**
 * clear all vector items at the end of the program
 */
static bool deleteAll(Item* my_item);

/**
* a class in order to validate int data is not invalid (double or string)
*/
class GetInt
{
public:
    int&  val;
    GetInt(int& v): val(v) {}

    /**
     * an overloading for istream cin
     * passed by r value reference in order to allow using this class directly with operator >>
     * means doesn't need to decalre a variable
     */
    friend istream& operator>>(istream& i, GetInt && data)
    {
        string my_str;
        i.ignore();
        getline(i, my_str);

        if (i.fail())
        {
            i.clear();
            throw invalid_argument("Invalid argument");
        }

        size_t pos;
        try
        {
            data.val = stoi(my_str, &pos);
        }
        catch (exception &e)
        {
            // throws new exception in order to overload the "stoi" exception message
            throw invalid_argument("invalid argument");
        }
        if (pos < my_str.size())
        {
            throw invalid_argument("Invalid argument");
        }
        return i;
    }
};

/**
* main program invoking the parser in order to validate
* and create items and managing & printing the stock of the store.
*/
int main(int argc, char** argv)
{
    cout << fixed << std::setprecision(2);

    // case entered file parameter into main()
    ifstream in;
    if (argc == 2)
    {
        in.open(argv[1]);
        cin.rdbuf(in.rdbuf());
    }
    string choiceString;
    int choice;
    vector<Item*> v;

    do
    {
        printMenu();
        cin >> choiceString;
        try
        {
            if (!readNumber(choiceString))
            {
                throw runtime_error("invalid argument");
            }
            choice = stoi(choiceString);
            commandCenter(v, choice);
        }
        catch (const exception& e)
        {
            std::cerr << e.what() << endl;
        }
        cout << endl;
    }
    while (choice != 7);

    remove_if(v.begin(), v.end(), deleteAll);
    v.clear();

}


/**
* read from file and attempt to create item objects
*/
void readFromFile(const string &fileString, vector<Item*> &v)
{
    string fileRepresentionString, singleItem, line, lastLine;
    ifstream file;
    file.open(fileString);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file");
    }
    // delete all empty lines
    fileRepresentionString = clearSpaces(file);
    istringstream clearStock(fileRepresentionString);
    // reserve [memory optimization]
    v.reserve(gVectorReserve);

    /* attempts to build item objects */
    while (getline(clearStock, line))
    {
        if (line != END_ITEM_LINE)
        {
            singleItem += (line + "\n");
        }
            /* attempts to builds an item object. throws runtime error in case of failure */
        else
        {
            ITEM itemEnum = identifiyValidateItem(singleItem);
            addToOrderedVector(v, castToItemObject(itemEnum, singleItem));
            singleItem = EMPTY_STRING;
        }
        lastLine = line;
    }
    if (lastLine != END_ITEM_LINE)
    {
        throw runtime_error("end line missing");
    }
}

/**
 * main function activate other functions according to user choice at menu
 */
void commandCenter(vector<Item*> &v, int choice)
{
    int subChoiceInt;
    string subChoiceString;
    switch(choice)
    {
        case 1:
            cout << "please enter file path: ";
            cin.ignore();
            getline(cin, subChoiceString);
            readFromFile(subChoiceString, v);
            break;
        case 2:
            cout << "please enter catalog id: ";
            cin >> GetInt(subChoiceInt);
            printByCatalogId(v, subChoiceInt);
            break;
        case 3:
            cout << "please enter product name: ";
            cin.ignore();
            getline(cin, subChoiceString);
            printByName(v, subChoiceString);
            break;
        case 4:
            printByCatalogId(v);
            break;
        case 5:
            printByName(v);
            break;
        case 6:
            cout << "please enter catalog number: ";
            cin >> GetInt(subChoiceInt);
            printByCatalogId(v, subChoiceInt, TO_SELL);
            break;
        case 7:
            break;
        default:
            throw runtime_error("invalid argument");
    }
}


/**
 * add an item object to suitable place in a vector ordered by catalog Id
 */
void addToOrderedVector (vector<Item *> &v, Item *itemToAdd)
{
    if (v.empty())
    {
        v.push_back(itemToAdd);
    }
    else
    {
        auto placeToInsert = lower_bound(v.begin(), v.end(), itemToAdd, numberComparator);
        // case same id as existing item
        if (placeToInsert != v.end() && (*placeToInsert)->getId() == itemToAdd->getId())
        {
            // error: duplicate Id for different item
            if ((*placeToInsert)->getName() != itemToAdd->getName())
            {
                delete itemToAdd;
                throw runtime_error("ERROR! duplicate Id for differnt item");
            }
                // add stock quantity
            else
            {
                double newQuantity = (*placeToInsert)->getQuantity() + itemToAdd->getQuantity();
                (*placeToInsert)->setQuantity(newQuantity);
                delete itemToAdd;
            }
        }
        else
        {
            v.insert(placeToInsert, itemToAdd);
        }
    }
}

/**
* find an item by catalog number. also attempts to sell in case toSell is true
*/
void printByCatalogId (vector<Item *> &v, int num, bool toSell)
{
    auto it = find_if (v.begin(), v.end(),
                       [num] (const Item* o) -> bool {return o->getId() == num; });
    if (it == v.end())
    {
        cout << "Item not found" << endl;
    }
    else
    {
        if (toSell)
        {
            if (sellItem(*(*it)))
            {
                cout << *(*it) << END_ITEM_LINE << endl;
            }
        }
        else
        {
            cout << *(*it) << END_ITEM_LINE << endl;
        }

    }
}

/**
* find an item by catalog number. also attempts to sell in case toSell is true
*/
void printByName (vector<Item *> &v, const string &name)
{
    orderVector(v, BY_NAME);
    auto it = find_if (v.begin(), v.end(),
                       [name] (const Item* o) -> bool {return o->getName() == name; });
    if (it == v.end())
    {
        cout << "Item not found" << endl;
    }
    else
    {
        while ((*it)->getName() == name)
        {
            cout << *(*it) << END_ITEM_LINE << endl;
            it++;
        }
    }
}

/**
 * sell item. return true iff item exists with enough stock for selling
 */
bool sellItem(Item &i)
{
    string choiceString;
    double subChoiceDouble, newQuantity;
    if (i.getIsDiscret())
    {
        cout << "Please enter number of items: ";
        cin >> choiceString;
        if(!(readNumber(choiceString)))
        {
            throw runtime_error("invalid argument");
        }
        subChoiceDouble = stoi(choiceString);
    }
    else
    {
        cout << "Please enter desired quantity: ";
        cin >> choiceString;
        if(!(readNumber(choiceString, DOUBLE)))
        {
            throw runtime_error("invalid argument");
        }
        subChoiceDouble = stod(choiceString);
    }
    newQuantity = i.getQuantity() - subChoiceDouble;
    if (newQuantity >= 0)
    {
        i.setQuantity(newQuantity);
        return true;
    }
    else
    {
        cout << "Not enough stock to sell" << endl;
        return false;
    }
}

/**
* print stock by citem atalog Id (vector always will be ordered like that as default)
*/
void printByCatalogId(const vector<Item*> &v)
{
    for(Item* const i: v)
    {
        cout << *i << END_ITEM_LINE << endl;
    }
}

/**
* print stock by item name
*/
void printByName(vector<Item*> &v)
{
    orderVector(v, BY_NAME);
    for(Item* i: v)
    {
        cout << *i << END_ITEM_LINE << endl;
    }
    // returns to default vector ordered by catalog Id
    orderVector(v);
}

/**
* order vector by catalog Id or by name
*/
void orderVector (vector<Item*> &v, bool byCatalog)
{
    if (byCatalog)
    {
        return sort(v.begin(), v.end(), numberComparator);
    }
    else
    {
        return sort(v.begin(), v.end(), nameComparator);
    }
}

/**
 * name compartor for vector sorting
 */
bool nameComparator(const Item *first, const Item *second)
{
    if (first == nullptr || second == nullptr)
    {
        if (first == second)
        {
            return false;
        }

        return (first == nullptr);
    }

    if (first->getName() == second->getName())
    {
        return *first<*second;
    }
    return first->getName() < second->getName();
}

/**
 * Id compartor for vector sorting
 */
bool numberComparator(const Item *first, const Item *second)
{
    if (first == nullptr || second == nullptr)
    {
        if (first == second)
        {
            return false;
        }

        return (first == nullptr);
    }
    return *first<*second;
}

/**
* clear all vector items at the end of the program
*/
static bool deleteAll(Item* my_item)
{
    delete my_item;
    return true;
}

/**
 * prints the main menu
 */
void printMenu()
{
    string str, menuLines[MENU_LENGTH];
    menuLines[0] = "1. Input stock from file";
    menuLines[1] = "2. Find item by catalog number";
    menuLines[2] = "3. Find item by name";
    menuLines[3] = "4. Print stock by catalog number";
    menuLines[4] = "5. Print stock by name";
    menuLines[5] = "6. Sell item";
    menuLines[6] = "7. Exit";

    for (int i = 0; i < MENU_LENGTH; i++)
    {
        cout << menuLines[i] << endl;
    }
}