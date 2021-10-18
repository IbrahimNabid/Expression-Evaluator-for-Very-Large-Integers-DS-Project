#ifndef __BIGINT_H__
#define __BIGINT_H__

#include "VList.h"
#include <iostream>
#include <string>

namespace ds {

class BigInt {
private:
  VList<int> digits; // stores the digits of the BigInt

public:
  /**
   * Construct a new BigInt object from string.
   *
   * @param val a string of unlimited digits; default is empty string
   */
  explicit BigInt(const std::string &val = "") {
    for (unsigned j = 0; j < val.length(); j++) {
      digits.addLast(val[j] - '0');
    }
  }

  /** Override `<<` to print all digits to os. */
  friend std::ostream &operator<<(std::ostream &os, const BigInt &bi) {
    for (int i = 0; i < bi.digits.size(); i++)
      os << bi.digits.get(i);
    return os;
  }
  // Code below overloads the < operator to return true or false if the bigint is bigger or smaller than the other
  friend bool operator<(const BigInt &a, const BigInt &b)
  {
    // if size of a is more than b, then return false
    if (a.digits.size() > b.digits.size()) 
    {
      return false;
    }
    // if size of a is less than b, then return true
    if (a.digits.size() < b.digits.size())
    {
      return true;
    }
    // checks each digit individually in a and b if the sizes are the same
    for (int i = 0; i < a.digits.size(); i++)
    {
      if (a.digits.get(i) < b.digits.get(i)) // if digit is greater than b, return true
      {
        return true;
      }
      else if (a.digits.get(i) > b.digits.get(i)) // if digit is greater in a, return false
      {
        return false;
      }
    }
    return false;
  }

  inline BigInt operator+(const BigInt &other) const;
  inline BigInt operator-(const BigInt &other) const;
};

/** Return the *sum* of this BigInt and the `other` BigInt. */
BigInt BigInt::operator+(const BigInt &other) const {
  // Reference: https://en.wikipedia.org/wiki/Addition
  // Example: 456 + 1123 = 1579
  // TODO:
  int carry = 0; // carry initialized to 0
  BigInt res; // res initialized to empty BigInt

  int i = digits.size() - 1; // i = last item index in current BigInt
  int j = other.digits.size() - 1; // j = last item index in other BigInt
  int d1, d2, sum;

  // Iterate through the two lists from the back with the least significant digit until all items have been consumed
  while (i >= 0 || j >= 0) 
  {
    if (i < 0) // if i<0, sets d1 to 0 (sets next item to 0 if all items in i are consumed)
    {
      d1 = 0;
    }
    else
    {
      d1 = digits.get(i); // else, d1 set to current item in digits
    }

    if (j < 0) // if j<0, sets d2 to 0 (sets next item to 0 if all items in j are consumed)
    {
      d2 = 0;
    }
    else
    {
      d2 = other.digits.get(j); // else, d2 set to current item in digits
    }

    sum = d1 + d2 + carry; // sum = digit from current list + digit from other list + carry
     
    if (sum < 10) // sets carry to 0 if sum < 10, otherwise carry is set to 1 and 10 is minused from sum
    {
      carry = 0;
    }
    else 
    {
      carry = 1;
      sum -= 10; 
    }

    res.digits.addFirst(sum); // adds sum value to the first item in res
    i--; 
    j--;
  }

  if(carry == 1) // Add 1 to the front of res.digits if carry == 1
  {
    res.digits.addFirst(1);
  }

  return res; // returns res value
}

BigInt BigInt::operator-(const BigInt &other) const {
  // Reference: https://en.wikipedia.org/wiki/Absolute_difference
  // Example: 456 - 1123 = 667
  // TODO:
  if (*this < other) // checks if current BigInt is less than other BigInt
  {
    return other - *this; // if yes, return other - *this
  }
  int borrow = 0; // borrow initialized to 0
  BigInt res; // res initialized to empty BigInt

  int i = digits.size() - 1; // i = last item index in current BigInt
  int j = other.digits.size() - 1; // j = last item index in other BigInt

  int d1, d2, dif;

  // Iterate through the two lists from the back with the least significant digit until all items have been consumed
  while (i >= 0 || j >= 0)
  {
    d1 = digits.get(i); 
    if (j < 0) // if items in j or other BigInt consumed, then assign next item to 0
    {
      d2 = 0; 
    }
    else
    {
      d2 = other.digits.get(j); // else d2 is set to the current j item in the other BigInt
    }
    dif = d1 - d2 - borrow; // dif = digit from current list - digit from other list - borrow

    if (dif >= 0) // If dif < 0, set borrow = 1 and dif += 10; otherwise, borrow = 0
    {
      borrow = 0;
    }
    else
    {
      borrow = 1;
      dif += 10;
    }

    res.digits.addFirst(dif); // add dif value to front of res.digits
    i--;
    j--; 
  }

  while(res.digits.getFirst() == 0 && res.digits.size() != 1) // removes all leading zeros if needed
  {
    res.digits.removeFirst(); 
  }
  return res; //returns res value
}

} // namespace ds

#endif //__BIGINT_H__
