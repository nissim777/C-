/**
 * this file contains implemention for Parser used in order to validate and identify
 * Items according to file and responsible on creating and returning the objects
 */

#include "Parser.h"

#define MAX_ITEM_FIELDS 7
#define MIN_ITEM_FIELDS 5
#define FIRST_FIELD 1
#define SECOND_FIELD 2
#define THIRD_FIELD 3
#define FORTH_FIELD 4
#define FIFTH_FIELD 5
#define SIXTH_FIELD 6
#define SEVENTH_FIELD 7
#define EXCEPTION -1
#define DOUBLE true
#define DIMENSION_NUM 3
#define SPACE ' '
#define EMPTY_STRING ""
#define ONE_SPACE " "

unsigned long gVectorReserve = 0;

/**
 * outputs file into string after deleting empty lines
 * NOTE: also implemented like this in order to avoid need to close file in case of error in item 
 */
const string clearSpaces (ifstream &file)
{
    unsigned long lineCount = 0;
    string toReturnString, line;
    while (getline(file, line))
    {
        if(!line.empty())
        {
            lineCount ++;
            toReturnString += (line + "\n");
        }
    }
    file.close();
    gVectorReserve += lineCount / MIN_ITEM_FIELDS;
    return toReturnString;
}


/**
 * identitfy and validate the item according to the lines that were written in the file
 */
ITEM identifiyValidateItem (string &singleItem)
{
    ITEM toReturn;
    string line, quantityString;
    istringstream stream(singleItem);
    singleItem = EMPTY_STRING;
    bool finallyIdentified = false, valid = true;

    for (int lineNum = 1; lineNum <= MAX_ITEM_FIELDS; lineNum++)
    {
        getline(stream, line);
        switch(lineNum)
        {
            case FIRST_FIELD:
                if (!omitPrefix(line, "Item: ") || (!readNumber(line)))
                {
                    valid = false;
                }
                break;
            case SECOND_FIELD:
                if (!omitPrefix(line, "Name: ")) 
                {
                    valid = false;
                }
                break;
            case THIRD_FIELD:
                // validation of int or double will be done at the end of function
                if (!omitPrefix(line, "Quantity: ")) 
                {
                    valid = false;
                }
                else
                {
                    quantityString = line;
                }
                break;
            case FORTH_FIELD:
                if (!omitPrefix(line, "Price: ") || !readNumber(line, DOUBLE))
                {
                    valid = false;
                }
                break;
            case FIFTH_FIELD:
                if (omitPrefix(line, "Calories: "))
                {
                    if (readNumber(line, DOUBLE))
                    {
                        toReturn = CANDY;
                        finallyIdentified = true;
                    }
                    else
                    {
                        valid = false;
                    }
                }
                else if (omitPrefix(line, "Weight: "))
                {
                    if (readNumber(line, DOUBLE))
                    {
                        toReturn = CLOTH;
                        finallyIdentified = true;
                    }
                    else
                    {
                        valid = false;
                    }
                }
                else if (omitPrefix(line, "Author: "))
                {
                    toReturn = MOVIE_BOOK;
                }
                else if (!omitPrefix(line, "Dimensions: ") ||
                         !readNumber(line, DOUBLE, DIMENSION_NUM))
                {
                    valid = false;
                }
                break;
            case SIXTH_FIELD:
                 if  (omitPrefix(line, "Material: "))
                 {
                     toReturn = FURNITURE;
                 }
                 else if (omitPrefix(line, "Capacity: "))
                 {
                     if (readNumber(line, DOUBLE))
                     {
                         toReturn = KITCHEN_TOOL;
                         finallyIdentified = true;
                     }
                     else
                     {
                         valid = false;
                     }
                 }
                 else if (!omitPrefix(line, "Year of publication: "))
                 {
                     valid = false;
                 }
                break;
            case SEVENTH_FIELD:
                if  (omitPrefix(line, "Color: "))
                {
                    finallyIdentified = true;
                }
                else if(omitPrefix(line, "Length: ") && readNumber(line, DOUBLE))
                {
                    finallyIdentified = true;
                }
                else
                {
                    valid = false;
                }
                break;
        }
        
        if (!valid)
        {
            throw runtime_error("Error! Invalid item");
        }
        
        singleItem += (line + "\n");
        if (finallyIdentified)
        {
            // if no more lines exist
            if (!getline(stream, line))
            {
                return validateQuantityType(toReturn, quantityString);
            }
            else
            {
                throw runtime_error("Error! Invalid item");
            }
        }
    }
    return toReturn;
}

/**
 * a helper func validate quantity variable, which is different for discrete and continous items
 */
ITEM validateQuantityType (const ITEM &toReturn, string &quantityString)
{   
    // check suitable quantity field
    if (toReturn == CANDY || toReturn == CLOTH)
    {
        // case continuous itme: validate is number
        if (!readNumber(quantityString, DOUBLE))
        {
            throw EXCEPTION;
        }
    }
    else
    {
        // case discretItem: validate is int
        if (!readNumber(quantityString))
        {
            throw EXCEPTION;
        }
    }
    return toReturn;
}

/**
 * parsing the lines of item field values in order to create an item object
 * note: activate after item validation
 */
Item* castToItemObject (const ITEM &i, const string &singleItem)
{
    istringstream stream(singleItem);
    string line;

    /* basic fields */
    int catalogId;
    string name;
    double quantity, price;

    /* additional field */
    int num1, num2;
    string str1, str2;
    double double1, dimensions[DIMENSION_NUM];

    /* recieve basic fields: */
    
    // first field
    getline(stream, line);
    catalogId = stoi(line);

    // second field
    getline(stream, line);
    name = line;

    //third field
    getline(stream, line);
    if (i == CANDY || i == CLOTH)
    {
        readNumber(line, DOUBLE);
        quantity = stod(line);
    }
    else
    {
        readNumber(line);
        quantity = stoi(line);
    }

    // forth field
    getline(stream, line);
    price = stod(line);

    /* recieve additional fields: */
    getline(stream, line);

    if (i == FURNITURE || i == KITCHEN_TOOL)
    {
        readNumber(line, DOUBLE, DIMENSION_NUM);
        string subDouble, rest;

        for (int i = 0; i <DIMENSION_NUM; i++)
        {
            auto index = line.find(SPACE);
            subDouble = line.substr(0, index);
            rest = line.substr(index + 1, line.size() - 1);
            dimensions[i] = stod(subDouble);
            line = rest;
        }

        getline(stream, line);
        if (i == KITCHEN_TOOL)
        {
            readNumber(line, DOUBLE);
            double1 = stod(line);
            return new kitchenTool(catalogId, name, price, (int)quantity, dimensions, double1);
        }
        str1 = line;
        getline(stream, line);
        str2 = line;
        return new furniture(catalogId, name, price, (int)quantity, dimensions, str1, str2);
    }

    if(i == MOVIE_BOOK)
    {
        str1 = line;
        getline(stream, line);
        readNumber(line);
        num1 = stoi(line);
        getline(stream, line);
        readNumber(line);
        num2 = stoi(line);
        // build object
        return new movieOrBook(catalogId, name, price, (int)quantity, str1, num1, num2);
    }
    
    if (i == CANDY || i == CLOTH)
    {
        readNumber(line, DOUBLE);
        double1 = stod(line);
        if (i == CANDY)
        {
            return new candy(catalogId, name, price, quantity, double1);
        }
    }
    return new cloth(catalogId, name, price, quantity, double1);
}

/**
 * used for validate (1 or more) integer or double variables. also trims unnessceray spaces/digits
 * activate: readInt, readDouble (including readInt)
 * @param line: string represents the number field
 * @param isDouble: if true checks for double number (otherwise integer)
 * @param numToReceive: number of variables should be validated
 * @return true iff a vaild number representation
 */
bool readNumber(string &line, bool isDouble, int numToReceive)
{
    string finalString;
    // read int or double
    for (int i = 0; i < numToReceive; i++)
    {
        omitPreSpaces(line);
        if(line.empty())
        {
            return false;
        }
        readInt(line, finalString);
        if (isDouble)
        {
            readDouble(line, finalString);
            // check valid num
            if (finalString[0] == DOT || finalString[finalString.size() - 1] == DOT)
            {
                return false;
            }
        }
        finalString += ONE_SPACE;
    }
    // check suffix
    if(!omitSuffix(line))
    {
        return false;
    }
    line = finalString;
    return true;
}

/**
 * reads an integer number. activated by readNumber
 */
void readInt (string &line, string &finalString)
{
    //read number
    while (!line.empty() && isdigit(line[0]))
    {
        finalString += line[0];
        line.erase(0, 1);
    }
    //omit leading zero
    omitLeadingZeros(finalString);
}

/**
 * read an double number. activated by readNumber, after readInt was activated.
 */
void readDouble (string &line, string &finalString)
{
    int count = 0;
    // read dot
    if (!line.empty() && line[0] == DOT)
    {
        finalString += line[0];
        line.erase(0, 1);
    }
    // read after dot
    while (!line.empty() && isdigit(line[0]))
    {
        count++;
        if (count <= 2)
        {
            finalString += line[0];
        }
        line.erase(0, 1);
    }
}

/**
 * omits and validate prefix (field name and spaces) from field line
 * returns true iff prefix exists
 */
bool omitPrefix(string &line, const string &prefix)
{
    string currPrefix = line.substr(0, prefix.size());
    if (currPrefix == prefix)
    {
        // omit prefix
        line.erase(0, prefix.size());
        // omit pre-spaces
        omitPreSpaces(line);
        return true;
    }
    return false;
}

/**
 * omits and validate suffix (trailing spaces from integer/double)
 * return true iff suffix is contains only trailing spaces
 */
bool omitSuffix(string &line)
{
    // omit post-spaces
    while (!line.empty() && line[0] == EMPTY_SPACE)
    {
        line.erase(0, 1);
    }
    // validate only num exist
    if (!line.empty())
    {
        return false;
    }
    return true;
}

/**
 * omits leading zero of an integer/double number
 */
void omitLeadingZeros(string &str)
{
    while(str.length() > 1 && str[0] == LEADING_ZERO && !(str.length()>2 && str[1] == DOT))
    {
        str.erase(0, 1);
    }
}

/**
 * omits spaces from string beginning
 */
void omitPreSpaces (string &line)
{
    while (!line.empty() && line[0] == EMPTY_SPACE)
    {
        line.erase(0, 1);
    }
}


