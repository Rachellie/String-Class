// String.cpp
//
// ICS 46 Winter 2020
// Project #0: Getting to Know the ICS 46 VM
//
// Implement all of your String member functions in this file.
//
// Note that the entire standard library -- both the C Standard
// Library and the C++ Standard Library -- is off-limits for this
// task, as the goal is to exercise your low-level implementation
// skills (pointers, memory management, and so on).

#include "String.hpp"
#include "OutOfBoundsException.hpp"


String::String()
{
	burger = new char[1];
	burger[0] = '\0';
	burger_size = 0;
}

String::String(const char* chars)
{
	int i = 0;
	while(chars[i] != '\0')
	{
		i++;
	}
	burger = new char[i+1];
	for (int j = 0; j < i+1; ++j)
	{
		burger[j] = chars[j];
	}
	burger_size = i;
}

String::String(const String& s)
{
	burger = new char[s.length()+1];
	for (int i = 0; i < s.length(); ++i)
	{
		burger[i] = s.burger[i];
	}
	burger[s.length()+1] = '\0';
	burger_size = s.length();
}

String::~String() noexcept
{
	delete[] burger;
}

String& String::operator=(const String& s)
{
	delete[] burger;
	burger = new char[s.length()];
	//char* temp_arr = new char[s.length()+1];
	for (int i = 0; i < s.length(); ++i)
	{
		burger[i] = s.burger[i];
	}
	burger_size = s.length();

	return *this;
}

void String::append(const String& s)
{
	char* new_string = new char[burger_size + s.length()];
	for (int i = 0; i < burger_size; ++i)
	{
		new_string[i] = burger[i];
	}
	for (int i = 0; i < s.length(); ++i)
	{
		new_string[burger_size+i] = s.burger[i];
	}
	delete[] burger;
	burger = new_string;
	burger_size += s.length();
}

char String::at(unsigned int index) const
{
	if (index >= burger_size)
	{
		throw OutOfBoundsException();
	}
	return burger[index];
}

char& String::at(unsigned int index)
{
	if (index >= burger_size)
	{
		throw OutOfBoundsException();
	}
	return burger[index];
}

void String::clear()
{
	delete[] burger;
	burger = new char[1];
	burger[0] = '\0';
	burger_size = 0;
}

int String::compareTo(const String& s) const noexcept
{
	for (int i = 0; i < burger_size; ++i)
	{
		if (burger[i] > s.burger[i])
		{
			return 1;
		}
		else if (burger[i] < s.burger[i])
		{
			return -1;
		}
	}

	if (burger_size == s.length())
	{
		return 0;
	}
	else if (burger_size < s.length())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

String String::concatenate(const String& s) const
{
	char* temp_str = new char[burger_size + s.length()+1];

	for (int i = 0; i < burger_size; ++i)
	{
		temp_str[i] = burger[i];
	}
	for (int i = 0; i < s.length(); ++i)
	{
		temp_str[burger_size+i] = s.burger[i];
	}

	String new_str = String(temp_str);
	delete[] temp_str;
	return new_str;
}

bool String::contains(const String& substring) const noexcept
{
	for (int i = 0; i < burger_size; ++i)
	{
		if (burger[i] == substring.burger[0])
		{
			for (int j = 1; j < substring.length(); ++j)
			{
				if (burger[i+j] != substring.burger[j])
				{
					break;
				}
				else if (j == substring.length()-1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool String::equals(const String& s) const noexcept
{
	if (burger_size == s.length())
	{
		for (int i = 0; i < burger_size; ++i)
		{
			if (burger[i] != s.burger[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

int String::find(const String& substring) const noexcept
{
	if (! this->contains(substring))
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < burger_size; ++i)
		{
			if (burger[i] == substring.burger[0])
			{
				for (int j = 0; j < substring.length(); ++j)
				{
					if (burger[i+j] != substring.burger[j])
					{
						break;
					}
				}
				return i;
			}
		}
		return -1;
	}
}

bool String::isEmpty() const noexcept
{
	if (burger_size == 0)
	{
		return true;
	}
	return false;
}

unsigned int String::length() const noexcept
{
	return burger_size;
}

String String::substring(unsigned int startIndex, unsigned int endIndex) const
{
	
	if (startIndex < burger_size and startIndex >= 0 and endIndex <= burger_size and endIndex >= 0)
	{
		if (startIndex < endIndex)
		{
			char* new_arr = new char[endIndex-startIndex+1];
			for (int i = 0; i < endIndex-startIndex; ++i)
			{
				new_arr[i] = burger[startIndex+i];
			}
			new_arr[endIndex-startIndex] = '\0';
			String new_str = String(new_arr);
			delete[] new_arr;
			return new_str;
		}
		else
		{
			return String();
		}
	}
	else
	{
		throw OutOfBoundsException();
	}
}

const char* String::toChars() const noexcept
{
	return burger;
}