/**
 * This file contains implemntation for the methods of the class big_integer
 * created by: black_knight
 */

#include "big_integer.h"
#include <cctype>
#include <algorithm>
#include<iostream>

#define EMPTY_STRING ""
#define MINUS_SIGN '-'
#define INTO_INT '0'

using namespace std;

/* ------------------ Constructors ------------------------ */

/**
 * default constructor
 */
big_integer::big_integer ():big_integer(0)
{
}

/**
 * copy constructor
 */
big_integer::big_integer (const big_integer& other)
        :_data(other._data), _negative(other._negative)
{
}

/**
 * constructor receiving int number
 */
big_integer::big_integer (const int i):big_integer(to_string(i), false)
{
}

/**
* constructor receiving string. if not valid initialized with zero.
*/
big_integer::big_integer (const  string& str): big_integer(str, true)
{
}

/**
 * helper constructor in order to unite handling of the constructors for int and string
 * @param validate: if need to check for validity of string
 */
big_integer::big_integer (const string &str, bool validate): _data("0"), _negative(false)
{
    string str2;
    str2 = str;
    if (str.empty())
    {
        return;
    }

    // case minus
    if (str[0] == MINUS_SIGN)
    {
        _negative = true;
        str2.erase(0, 1);
    }

    if(str2.empty())
    {
        _negative = false;
        return;
    }

    // check validity
    bool valid = true;
    if (validate)
    {
        for (auto c : str2)
        {
            if (!isdigit(c))
            {
                valid = false;
            }
        }
    }
    // reverse order
    if (valid)
    {
        str2 = _reverse(str2);
        _data = _omitLeadingZeros(str2);
    }
}

/* ------------------ REGULAR OPERATORS AND HELPER FUNCS ------------------------ */

/**
* an overloading for the operator +
*/
big_integer big_integer::operator+(const big_integer &other) const
{
    return _commandCenter(other, ADD);

}

/**
* adds 2 positive numbers. activated by commandCenter func.
*/
big_integer big_integer::_addPositive(const big_integer &other)const
{

    return big_integer(_reverse(_stringAdd(this->_data, other._data)));
}

/**
* adds 2 strings repersenting positive numbers
*/
const std::string big_integer::_stringAdd (const std::string &first, const std::string &second)const
{
    int result = 0, saveOne = 0;
    string finalResult;
    string minData = (first.size() < second.size()) ? first : second;
    string maxData = (first.size() >= second.size()) ? first : second;
    // add all digits one by one
    for (unsigned int i = 0; i < maxData.size() ; i++)
    {
        // add both
        if (i < minData.size())
        {
            result = (first[i] - INTO_INT) + (second[i] - INTO_INT) + saveOne;
        }
        // add rest
        else
        {
            result = (maxData[i] - INTO_INT) + saveOne;
        }
        saveOne = 0;
        if (result >= 10)
        {
            saveOne = 1;
            result -= 10;
        }
        finalResult += to_string(result);
    }
    // add final digit
    if(saveOne == 1)
    {
        finalResult += to_string(saveOne);
    }
    return finalResult;
}

/**
* an overloading for the operator -
*/
big_integer big_integer::operator-(const big_integer &other) const
{
    return _commandCenter(other, SUB);
}

/**
 * subtratcts 2 positive numbers. activated by commandCenter func.
 */
big_integer big_integer::_subtractPositive(const big_integer &other)const
{
    big_integer objToReturn;
    if (_isEqualOrBigger(other._data, this->_data))
    {
        objToReturn = big_integer(_reverse(_stringSubtract(other._data, this->_data)));
        objToReturn._negative = true;
    }
    else
    {
        objToReturn = big_integer(_reverse(_stringSubtract(this->_data, other._data)));
    }
    return objToReturn;

}

/**
* adds 2 strings repersenting positive numbers
*/
const string big_integer::_stringSubtract (const string &first, const string &second)const
{
    int result = 0, saveOne = 0;
    string final_result;
    // subtract all digits one by one
    for (unsigned int i = 0; i < first.size(); i++)
    {
        //sub both
        if (i < second.size())
        {
            result = (first[i] - INTO_INT) - (second[i] - INTO_INT) - saveOne;
        }
        // sub both
        else
        {
            result = (first[i] - INTO_INT) - saveOne;
        }
        saveOne = 0;
        if (result < 0)
        {
            result += 10;
            saveOne = 1;
        }
        final_result += to_string(result);
    }
    return _omitLeadingZeros(final_result);
}

/**
* an overloading for the operator *
*/
big_integer big_integer::operator*(const big_integer &other) const
{
    return _commandCenter(other, MULT);
}

/**
* multiplys 2 positive numbers. activated by commandCenter func.
*/
big_integer big_integer::_multiplyPositive(const big_integer &other)const
{
    return big_integer(_reverse(_stringMultiply(this->_data, other._data)));
}

/**
* multiplies 2 strings repersenting positive numbers
*/
const string big_integer::_stringMultiply (const string &first, const string &second)const
{
    string finalResult;
    int result = 0;
    for (unsigned int i = 0; i < first.size(); i++)
    {
        for (unsigned int j = 0; j < second.size(); j++)
        {
            string stringResult;
            result = (first[i] - INTO_INT) * (second[j] - INTO_INT);
            stringResult += _reverse(to_string(result));
            for (unsigned int zero = 0; zero < i + j ; zero++)
            {
                stringResult = "0" + stringResult;
            }
            finalResult = _stringAdd((finalResult), (stringResult));
        }
    }
    return (finalResult);
}


/**
* an overloading for the operator /
*/
big_integer big_integer::operator/(const big_integer &other)const
{
    if (other._data == "0")
    {
        return big_integer("0");
    }
    return _commandCenter(other, DIV);
}

/**
* divides 2 positive numbers. activated by commandCenter func.
*/
big_integer big_integer::_dividePositive(const big_integer &other)const
{
    string toReturn, dividend = _data, divisor = other._data, finalResult;
    for (unsigned int i = 0; i < _data.size(); i++)
    {
        finalResult += "0";
    }
    // recursive call for the divide operation
    _recursiveDivide(dividend, finalResult, finalResult.size() - 1, divisor);
    finalResult = _omitLeadingZeros(finalResult);
    finalResult = _reverse(finalResult);
    return big_integer(finalResult);
}

/**
* divides 2 strings repersenting positive numbers (recursivly)
*/
void big_integer::_recursiveDivide (const std::string &dividend, std::string &finalResult,
                                    int finalResultIndex, const string &divisor) const
{
    // recursion stop condition
    if (dividend.empty() || !_isEqualOrBigger(dividend, divisor) || dividend == "0" )
    {
        return;
    }
    // (1) split dividend into current Dividend & rest:  [Curr|Rest]
    unsigned long minDividendIndex = _findMinDividendIndex(dividend, divisor);
    string currDividend = dividend.substr(minDividendIndex), restDividend, qutient, product, remainder;
    if (currDividend != dividend)
    {
        restDividend = dividend.substr(0, minDividendIndex);
    }

    // (2) divide current Dividend by divisor
    qutient = _findQutient(currDividend, divisor);

    // (3) multyply qutient at the divisor
    product = _stringMultiply(qutient, divisor);

    // (4) find remainder
    remainder = _stringSubtract(currDividend, product);
    if(remainder == "0")
    {
        remainder = EMPTY_STRING;
    }
    // (5) add remainder to the rest of Dividend
    restDividend += remainder;

    // (6) place the qutient
    finalResultIndex -= (currDividend.size() - 1);
    finalResult[finalResultIndex] = qutient[0];

    // progress index forward
    finalResultIndex--;

    // progress index backward
    finalResultIndex += remainder.size();

    // delete leadings zeros
    if(remainder.empty() && !restDividend.empty())
    {
        while (restDividend[restDividend.size() - 1] == '0')
        {
            restDividend.erase(restDividend.size() - 1);
            finalResultIndex--;
        }
    }

    return _recursiveDivide(restDividend, finalResult, finalResultIndex, divisor);
}

/**
 * helper divide function: finds the index of the minimal number can be divided
 * in the current phase
 */
unsigned long big_integer::_findMinDividendIndex (const string &dividend, const string &divisor) const
{
    // match minDividend to the divisor size
    string minDividend = dividend.substr(dividend.size() -divisor.size(), divisor.size());
    unsigned long minDividendIndex = dividend.size() - minDividend.size();
    // case minDividend is still smaller number
    if (!_isEqualOrBigger(minDividend, divisor))
    {
        if (dividend != minDividend)
        {
            minDividendIndex--;
        }
    }
    return minDividendIndex;
}

/**
* helper divide function: finds the qutient of the division of minimal dividend by the divisor
*/
const string big_integer::_findQutient (const string &currDividend, const string &divisor) const
{
    int count = 0;
    string tempCurrDividend = currDividend;
    while (_isEqualOrBigger(tempCurrDividend, divisor))
    {
        tempCurrDividend = _stringSubtract(tempCurrDividend, divisor);
        count ++;
    }
    return to_string(count);
}

/**
* an overloading for the operator %
*/
big_integer big_integer::operator%(const big_integer &other)const
{
    if (other._data == "0")
    {
        return big_integer("0");
    }
    return _commandCenter(other, MOD);
}

/**
* modulus 2 positive numbers. activated by commandCenter func.
*/
big_integer big_integer::_moduloPositive(const big_integer &other) const
{
    big_integer quotient = other._multiplyPositive(_dividePositive(other));
    big_integer result = _subtractPositive(quotient);
    return result;
}

/**
* an overloading for the operator +=
*/
big_integer big_integer::operator+=(const big_integer &other)
{
    return _helperEqual(other, ADD);
}


/**
* an overloading for the operator -=
*/
big_integer big_integer::operator-=(const big_integer &other)
{
    return _helperEqual(other, SUB);
}


/**
* an overloading for the operator *=
*/
big_integer big_integer::operator*=(const big_integer &other)
{
    return _helperEqual(other, MULT);
}

/**
* an overloading for the operator /=
*/
big_integer big_integer::operator/=(const big_integer &other)
{
    if (other._data == "0")
    {
        *this = big_integer("0");
        return *this;
    }
    return _helperEqual(other, DIV);
}

/**
* an overloading for the [assigment] operator =
*/
big_integer& big_integer::operator=(const big_integer &other)
{
    if (this != &other)
    {
        _data = other._data;
        _negative = other._negative;
    }
    return *this;
}

/* ------------------ BOOLEAN OPERATORS ------------------------ */

/**
* an overloading for the operator >=
*/
bool big_integer::operator>=(const big_integer &other) const
{
    string thisString = this->_data, otherString = other._data;
    // if sign not equel
    if (this->_negative != other._negative)
    {
        return (!this->_negative);
    }
    if ((!this->_negative))
    {
        return _isEqualOrBigger(thisString, otherString);
    }
    return _isEqualOrBigger(otherString, thisString);
}

/**
* an overloading for the operator ==
*/
bool big_integer::operator==(const big_integer &other) const
{
    string thisString = this->_data, otherString = other._data;
    if (this->_negative != other._negative && (this->_data != "0" && other._data != "0"))
    {
        return false;
    }
    return _isEqualOrBigger(thisString, otherString, true);
}

/**
* an overloading for the operator <
*/
bool big_integer::operator<(const big_integer &other) const
{
    return !(*this >= other);
}

/**
* an overloading for the operator <=
*/
bool big_integer::operator<=(const big_integer &other) const
{
    return (*this < other) || (*this == other);
}

/**
* an overloading for the operator >
*/
bool big_integer::operator>(const big_integer &other) const
{
    return !(*this <= other);
}

/**
* an overloading for the operator !=
*/
bool big_integer::operator!=(const big_integer &other) const
{
    return(!(*this == other));
}

/**
* an overloading for the [printing] operator <<
*/
std::ostream& operator<<(std::ostream &o, const big_integer& obj)
{
    string isNegative = "";
    if(obj._negative)
    {
        isNegative = "-";
    }

    return o << isNegative << obj._reverse(obj._data);
}

/* ------------------ HELPER FUNCS ------------------------ */

/**
* main helper function manipulates the result of the "dummy" positive helper functions to deal
* with minus numbers.
* deals with: + - * / %
*/
big_integer big_integer::_commandCenter (big_integer other, Operation oper)const
{
    big_integer result;
    switch(oper)
    {
        case ADD:
            // -a + b
            if (this->_negative && !other._negative)
            {
                result = other._subtractPositive(*this);
            }
            // a + -b
            else if (!this->_negative && other._negative)
            {
                result = _subtractPositive(other);
            }
            else
            {
                // a + b
                result = _addPositive(other);
                // -a + -b
                if (this->_negative)
                {
                    result._negative = true;
                }
            }
            result._checkZero();
            break;
        case SUB:
            // -a - (b)
            if (this->_negative && !other._negative)
            {
                result = _addPositive(other);
                result._negative = true;
            }
            // a - (-b)
            else if (!this->_negative && other._negative)
            {
                result = _addPositive(other);
            }
            // -a - (-b)
            else if(this->_negative)
            {
                result = other._subtractPositive(*this);
            }
            else
            {
                // a - b
                result = _subtractPositive(other);
            }
            break;
        case MULT:
            result = _multiplyPositive(other);
            // different signs
            if(this->_negative != other._negative)
            {
                result._negative = true;
            }
        break;
        case DIV:
            result = _dividePositive(other);
            // different signs
            if(this->_negative != other._negative)
            {
                result._negative = true;
            }
        break;
        case MOD:
            result = _moduloPositive(other);
            result._negative = this->_negative;
    }
    result._checkZero();
    return result;
}

/**
* main helper function adjusting the command Center function results in order to deal with
* equal operations.
* deals with: += -= *= /=
*/
big_integer big_integer::_helperEqual (const big_integer &other, Operation oper)
{
    big_integer object = _commandCenter(other, oper);
    this->_data = object._data;
    this->_negative = object._negative;
    return *this;
}

/**
 * checks if the current dividend is bigger or equel to the divisor
 * usually checks for >=.  can check for == if isEqual is true.
 * in use by the the boolean operations functions and divide func
 */
bool big_integer::_isEqualOrBigger (const string &thisString, const string &otherString, bool isEqual) const
{
    int thisCurrDigit, otherCurrDigit;
    // if length not equal
    if(thisString.size() != otherString.size())
    {
        if (isEqual)
        {
            return false;
        }
        return (thisString.size()>otherString.size());
    }
    // check digit by digit
    for (unsigned int i = 0; i < thisString.size(); i++)
    {
        thisCurrDigit = thisString[thisString.size() - i - 1];
        otherCurrDigit = otherString[otherString.size() - i - 1];
        if(thisCurrDigit != otherCurrDigit)
        {
            if (isEqual)
            {
                return false;
            }
            return (thisCurrDigit > otherCurrDigit);
        }
    }
    return true;
}

/* STRING MANIPULATIONS */

/**
* reverses the string
*/
string big_integer::_reverse (const string &currentStr)
{
    string reversedStr;
    reversedStr.reserve(currentStr.size()); //OPTIMIZATION
    for(unsigned int i = 0; i < currentStr.size() ; i++)
    {
        reversedStr += currentStr[currentStr.size() - i - 1];
    }
    return reversedStr;
}

/**
 * omits leading zero from string represenation
 */
std::string& big_integer::_omitLeadingZeros (std::string &str)const
{
    bool notZero = false;
    while (str.size() > 1 && !notZero)
    {
        if (str[str.size() - 1] == '0')
        {
            str.erase(str.size() - 1, 1);
        }
        else
        {
            notZero = true;
        }
    }
    return str;
}

/**
 * corrects the result -0
 */
void big_integer::_checkZero()
{
    _data = _omitLeadingZeros(this->_data);
    if (_data == "0")
    {
        _negative = false;
    }
}