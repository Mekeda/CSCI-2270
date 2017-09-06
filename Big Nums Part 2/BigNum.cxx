// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class


#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		capacity = DEFAULT_CAPACITY;
		used = 1;
		positive = true;
		digits = new unsigned int[capacity];
		digits[0] = 0;
			
	}    

	BigNum::BigNum(int num)
	{
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity];
		used = 0;
		
		if (num >= 0)
			positive = true;
			
		else
		{
			positive = false;
			num = num * -1;
		}
		
		if (num == 0)
		{
			digits[0] = 0;
			used = 1;
			return;
		}
		
		while (num != 0)
		{
			digits[used] = num % 10;
			num /= 10;
			++used;
		}
		
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{	
		
		string numberstring = strin;
		unsigned int len = numberstring.length();
		unsigned int y, z;
		
		if (strin[0] == '-')
		{
			positive = false;
			used = len - 1;
			z = used;
		}
		
		else if (strin[0] == '+')
		{
			positive = true;
			used = len - 1;
			z = used;
		}
		
		else
		{
			positive = true;
			used = len;
			z = used -1;
		}
	
		
		if (used <= DEFAULT_CAPACITY)
		{
			capacity = DEFAULT_CAPACITY;
		}
		else
		{
			capacity = used;
		}
		
		digits = new unsigned int[capacity];
		
		if (strin[0] == '0' && strin[used -1] == '0')
		{
			digits[0] = 0;
			return;
		}
		
		for (y = 0; y < used; ++y)
		{
			digits[y] = strin[z] - 0x30;
			z--;
		}
		
		unsigned int index = used - 1;
		
		if(digits[0] == 0)
			used = 1;
		
		else
		{
			while (digits[index] == 0)
			{
				digits[index] = digits[index - 1];
				--index;
				--used;
			}
		}
			
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		capacity = anotherBigNum.capacity;
		used = anotherBigNum.used;
		positive = anotherBigNum.positive;
		digits = new unsigned int[anotherBigNum.capacity];
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
    }

    BigNum::~BigNum()
    {
		delete [] digits;
    }
    
    void BigNum::resize(unsigned int n)
	{
		unsigned int helix_fossil = 1;
		while (helix_fossil * DEFAULT_CAPACITY < n)
			helix_fossil *= 2;	
		
		unsigned *largerArray;
		
		if (helix_fossil * DEFAULT_CAPACITY == capacity)
			return;
		
		capacity = helix_fossil * DEFAULT_CAPACITY;
		largerArray = new unsigned int[capacity];
		copy(digits, digits + used, largerArray);
		delete [] digits;
		digits = largerArray;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		unsigned int *temp_copy;
		
		if (this == &anotherBigNum)
			return *this;
		
		if (capacity != anotherBigNum.capacity)
		{
			capacity = anotherBigNum.capacity;
			temp_copy = new unsigned int[anotherBigNum.capacity];
			delete [] digits;
			digits = temp_copy;
		}
		
		used = anotherBigNum.used;
		positive = anotherBigNum.positive;
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
		return *this;
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		BigNum result = *this + addend;
		if(digits[used - 1] == 0)
			result.trim();
		*this = result;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		BigNum result = *this - subtractand;
		if(digits[used - 1] == 0)
			result.trim();
		*this = result;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		*this = *this * multiplicand;
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		// Extra credit.
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		// Extra credit.
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		unsigned int i = 1;
		
		if(positive == false)
		{
			positive = true;
			--*this;
			positive = false;
			if(used == 1 && digits[0] == 0)
				positive = true;
			return *this;
		}
		
		if(digits[0] != 9)
		{
			digits[0] += 1;
			return *this;
		}
		
		digits[0] = 0;
		while(i < used)
		{
			if(digits[i] != 9)
			{
				digits[i] += 1;
				return *this;
			}
			else
			{
				digits[i] = 0;
				++i;
			}
		}
		
		digits[used] = 1;
		++used;
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		unsigned int i = 1;
		
		if(positive == false)
		{
			positive = true;
			++*this;
			positive = false;
			return *this;
		}
		
		if(used == 1 && digits[0] == 0)
		{
			digits[0] = 1;
			positive = false;
			return *this;
		}
		
		if(digits[0] != 0)
		{
			digits[0] -= 1;
			return *this;
		}
		
		digits[0] = 9;
		while(i < used)
		{
			if(digits[i] != 0)
			{
				if(i == used - 1 && digits[i] == 1)
					--used;
				digits[i] -= 1;
				return *this;
			}
			else
			{
				digits[i] = 9;
				++i;
			}
		}
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		// Not using helper function.
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		BigNum result;
		BigNum smaller;
		bool carry = false;
		
		if((a >= b && a.positive) && a.used > b.used)
		{
			result = a;
			smaller = b;
		}
		else if(a < b && !a.positive && (a.digits[0] == 0 || b.digits[0] == 0))
		{
			result = a;
			smaller = b;
		}
		else
		{
			result = b;
			smaller = a;
		}
		
		for(unsigned int i = 0; i < result.used; i++)
		{
			unsigned int total = 0;
			if(smaller.used - 1 >= i)
				total = result.digits[i] + smaller.digits[i];
			else
				total = result.digits[i];
				
			if(i != 0 && carry)
				total++;
				
			carry = false;
			if(total >= 10)
				carry = true;
				
			result.digits[i] = total % 10;
		}
		return result;
		
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		// Extra credit.
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		// Extra credit.
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		return ( a >= b && a != b);
	}

	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return !(a < b);
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		BigNum c(a);
		BigNum d(b);

		if (c.positive == false)
		{
			if (d.positive == true)
			return true;
			if (c.used > d.used)
			return true;
			if (c.used < d.used)
			return false;
		}

		if (c.positive == true)
		{
			if (d.positive == false)
			return false;
			if (c.used > d.used)
			return false;
			if (c.used < d.used)
			return true;
		}

		unsigned int i = c.used - 1;

		if (c.positive == false)
		{
			while (i >= 0)
			{
			if (c.digits[i] > d.digits[i])
				return true;
			if (c.digits[i] < d.digits[i])
				return false;
			--i;
			}

			return false;	    
		}
		else
		{
			while (i >= 0)
			{
			if (c.digits[i] < d.digits[i])
				return true;
			if (c.digits[i] > d.digits[i])
				return false;
			--i;
			}

			return false;  
		}	

	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		return !(a > b);
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		BigNum c(a);
		BigNum d(b);

		if (c.positive != d.positive)
			return false;

		if (c.used != d.used)
			return false;

		for (unsigned int i = 0; i < c.used; ++i)
		{
			if (c.digits[i] != d.digits[i])
			return false;
		}

		return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);
	}

	// trim leading zeros
	void BigNum::trim()
	{
		while (used > 1 && digits[used-1] == 0)
			used--;
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if (bignum.positive == false)
			os << '-';

		for (unsigned int i = 0; i < bignum.used; ++i)
			os << bignum.digits[bignum.used - i - 1];
			
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string a;
		is >> a;
		BigNum temp = BigNum(a);
		bignum = temp;
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		// Extra credit.
		BigNum result;
		return result;
    }
  }



#endif



