/**
 * this file contains header for Parser used in order to validate and identify
 * Items according to file and responsible on creating and returning the objects
 */

#include <vector>
#include <fstream>
#include <iomanip>
#include "DiscretItem.h"
#include "ContinuousItem.h"
#include "Item.h"

#ifndef EX2_PARSER_H
#define EX2_PARSER_H
#define EMPTY_STRING ""
#define DOT '.'
#define EMPTY_SPACE ' '
#define LEADING_ZERO '0'

/**
 * enum represents the different Items
 */
enum ITEM
{
    FURNITURE,
    KITCHEN_TOOL,
    MOVIE_BOOK,
    CANDY,
    CLOTH
};

/** a variable represents estimated vector size according to file length. used for reserve. */
extern unsigned long gVectorReserve;

/**
 * outputs file into string after deleting empty lines
 */
const string clearSpaces (ifstream &file);

/**
 * identitfy and validate the item according to the lines that were written in the file
 */
ITEM identifiyValidateItem (string &singleItem);

/**
 * a helper func validate quantity variable, which is different for discrete and continous items
 */
ITEM validateQuantityType (const ITEM &toReturn, string &line);

/**
 * parsing the lines of item field values in order to create an item object
 * note: activate after item validation
 */
Item* castToItemObject (const ITEM &i, const string &singleItem);

/**
 * used for validate (1 or more) integer or double variables. also trims unnessceray spaces/digits
 * activate: readInt, readDouble (including readInt)
 * @param line: string represents the number field
 * @param isDouble: if true checks for double number (otherwise integer)
 * @param numToReceive: number of variables should be validated
 * @return true iff a vaild number representation
 */
bool readNumber(string &line, bool isDouble = false, int numToReceive = 1);

/**
 * reads an integer number. activated by readNumber
 */
void readInt (string &line, string &finalString);

/**
 * read an double number. activated by readNumber, after readInt was activated.
 */
void readDouble (string &line, string &finalString);

/**
 * omits and validate prefix (field name and spaces) from field line
 * returns true iff prefix exists
 */
bool omitPrefix(string &line, const string &prefix);

/**
 * omits and validate suffix (trailing spaces from integer/double)
 * return true iff suffix is contains only trailing spaces
 */
bool omitSuffix(string &line);

/**
 * omits leading zero of an integer/double number
 */
void omitLeadingZeros(string &str);

/**
 * omits spaces from string beginning
 */
void omitPreSpaces (string &line);

#endif //EX2_PARSER_H
