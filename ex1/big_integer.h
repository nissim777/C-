/**
 * This file contains a class for string representation of big integers
 * created by: black_knight
 */
#ifndef CPP_BIG_INTEGER_H
#define CPP_BIG_INTEGER_H
#include<string>

/**
 * This class contains an implementation of representation of big integers stored in strings
 * and calculating efficiently the basic operations as like: plus, minus, div ect.
 */
class big_integer
{
public:

    /**
    * enums for the basic operations sent to command Center function
    */
    enum Operation
    {
        ADD,
        MULT,
        SUB,
        DIV,
        MOD
    };

    /**
    * default constructor
    */
    big_integer ();

    /**
     * copy constructor
     */
    big_integer (const big_integer &other);

    /**
     * constructor receiving int number
     */
    big_integer (const int i);

    /**
    * constructor receiving string. if not valid initialized with zero.
    */
    big_integer (const  std::string &str);

    /**
    * an overloading for the operator + to be used by the class
    */
    big_integer operator+(const big_integer &other) const;

    /**
    * an overloading for the operator - to be used by the class
    */
    big_integer operator-(const big_integer &other)const;

    /**
    * an overloading for the operator * to be used by the class
    */
    big_integer operator*(const big_integer &other) const;

    /**
    * an overloading for the operator / to be used by the class
    */
    big_integer operator/(const big_integer &other) const;

    /**
    * an overloading for the operator % to be used by the class
    */
    big_integer operator%(const big_integer &other) const;

    /**
    * an overloading for the operator += to be used by the class
    */
    big_integer operator+=(const big_integer & other);

    /**
    * an overloading for the operator -= to be used by the class
    */
    big_integer operator-=(const big_integer &other);

    /**
    * an overloading for the operator *= to be used by the class
    */
    big_integer operator*=(const big_integer &other);

    /**
    * an overloading for the operator /= to be used by the class
    */
    big_integer operator/=(const big_integer &other);

    /**
    * an overloading for the operator >= to be used by the class
    */
    bool operator>=(const big_integer &other) const;

    /**
    * an overloading for the operator == to be used by the class
    */
    bool operator==(const big_integer &other) const;

    /**
    * an overloading for the operator > to be used by the class
    */
    bool operator>(const big_integer &other) const;

    /**
    * an overloading for the operator < to be used by the class
    */
    bool operator<(const big_integer &other) const;

    /**
    * an overloading for the operator <= to be used by the class
    */
    bool operator<=(const big_integer &other) const;

    /**
    * an overloading for the operator != to be used by the class
    */
    bool operator!=(const big_integer &other) const;

    /**
    * an overloading for the [assignment] operator = to be used by the class
    */
    big_integer& operator=(const big_integer& other);

    /**
    * an overloading for the [printing] operator << to be used by the class
    */
    friend std::ostream& operator<<(std::ostream &o, const big_integer& obj);

private:
    std::string _data;
    bool _negative;

    /**
    * helper constructor in order to unite handling of the constructors for int and string
    */
    big_integer (const std::string &str, bool validate);

    /**
    * main helper function manipulates the result of the "dummy" positive helper functions to deal
    * with minus numbers.
    * deals with: + - * / %
    */
    big_integer _commandCenter (big_integer other, Operation oper)const;

    /**
    * main helper function adjusting the command Center function results in order to deal with
    * equal operations.
    * deals with: += -= *= /=
    */
    big_integer _helperEqual (const big_integer &other, Operation oper);

    /**
    * adds 2 positive numbers
    */
    big_integer _addPositive(const big_integer &other)const;

    /**
    * subtratcts 2 positive numbers
    */
    big_integer _subtractPositive(const big_integer &other)const;

    /**
    * multiplys 2 positive numbers
    */
    big_integer _multiplyPositive(const big_integer &other)const;

    /**
    * divides 2 positive numbers
    */
    big_integer _dividePositive(const big_integer &other)const;

    /**
    * modulus 2 positive numbers
    */
    big_integer _moduloPositive(const big_integer &other) const;

    /**
    * adds 2 strings repersenting positive numbers
    */
    const std::string _stringAdd (const std::string &first, const std::string &second)const;

    /**
    * subtracts 2 strings repersenting positive numbers
    */
    const std::string _stringSubtract (const std::string &first, const std::string &second)const;

    /**
    * multiplys 2 strings repersenting positive numbers
    */
    const std::string _stringMultiply (const std::string &first, const std::string &second)const;

    /**
    * divides 2 strings repersenting positive numbers (recursivly)
    */
    void _recursiveDivide (const std::string &dividend, std::string &finalResult,
                           int finalResultIndex, const std::string &divisor) const;

    /**
    * helper divide function: finds the index of the minimal number can be divided
    * in the current phase
    */
    unsigned long _findMinDividendIndex (const std::string &dividend, const std::string &divisor) const;

    /**
    * helper divide function: finds the qutient of the division of minimal dividend by the divisor
    */
    const std::string _findQutient (const std::string &currDividend, const std::string &divisor) const;

    /**
    * helper divide function: checks if the current dividend is bigger or equel to the divisor
    * usually checks for >=.  can check for == if isEqual is true.
    * also in use by the the boolean operations functions
    */
    bool _isEqualOrBigger (const std::string &thisString, const std::string &otherString,
                           bool isEqual = false) const;

    /**
    * reverses the string representation to be accessed more conviently
    */
    static std::string _reverse(const std::string &);

    /**
    * corrects the result -0
    */
    void _checkZero();

    /**
    * omits leading zero from the string representation
    */
    std::string& _omitLeadingZeros (std::string &str)const;

};
#endif //CPP_BIG_INTEGER_H