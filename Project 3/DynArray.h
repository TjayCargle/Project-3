#pragma once
template <typename Type>
class DynArray
{
private:

	Type * myItem;
	unsigned int Size;
	unsigned int Capacity;

public:

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Constructor
	// Notes : Constructs an empty array (Size 0 Capacity 0)
	/////////////////////////////////////////////////////////////////////////////

	DynArray()
	{
		myItem = nullptr;
		Size = 0;
		Capacity = 0;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Destructor
	// Notes : cleans up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////

	~DynArray()
	{
		delete[] myItem;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Copy Constructor
	/////////////////////////////////////////////////////////////////////////////

	DynArray(const DynArray<Type>& that)
	{
		
		Size = that.Size;
		Capacity = that.Capacity;
	
		myItem = new Type[Capacity];
		for (unsigned int i = 0; i < Size; i++)
		{
			myItem[i] = that.myItem[i];
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function :	Assignment Operator
	/////////////////////////////////////////////////////////////////////////////

	DynArray<Type>& operator=(const DynArray<Type>& that)
	{
		if (&that != this)
		{
			
			Size = that.Size;
			Capacity = that.Capacity;
			delete[] myItem;
			myItem = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				myItem[i] = that.myItem[i];
			}
		}
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index to access
	// Return : Type & - returns the array element at [index]
	// Notes : performs no error checking. user should ensure index is 
	//		valid with the size() method
	/////////////////////////////////////////////////////////////////////////////

	Type& operator[](const unsigned int index)
	{
		return myItem[index];
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index to access
	// Return : const Type & - returns the array element at [index]
	// Notes : performs no error checking. user should ensure index is 
	//		valid with the size() method
	/////////////////////////////////////////////////////////////////////////////

	const Type& operator[](const unsigned int index) const
	{
		return myItem[index];
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function :	size
	// Returns : int - returns the number of items being stored
	// Notes : this function returns the number of items being stored, 
	/////////////////////////////////////////////////////////////////////////////
	unsigned int size() const
	{
		return Size;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : capacity
	// Returns : int - returns the number of items the array can store before 
	//		the next resize
	// Notes : this function returns the number of items the array can store, 
	//		not the number of bytes
	/////////////////////////////////////////////////////////////////////////////
	unsigned int capacity() const
	{
		return Capacity;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function :	clear
	// Notes : cleans up any dynamic memory and resets size and capacity to 0
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		delete[] myItem;
		Size = 0;
		Capacity = 0;
		myItem = nullptr;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : append
	// Parameters : item - the item to be appended to the next open spot
	// Notes : this function will append the item to the next open spot. if 
	//		no room exists, the array's capacity will be doubled and then 
	//		the item will be added
	/////////////////////////////////////////////////////////////////////////////
	
	void append(const Type& item)
	{
		if (Size == Capacity)
		{
			if (Capacity == 0)
			{
				myItem = new Type[1];
				Capacity = 1;
				myItem[Size] = item;
				
				
			}
			else
			{
				 Type * temp = new Type[Capacity * 2];
					for (unsigned int i = 0; i < Size; i++)
					{
						temp[i] = myItem[i];
					}
				delete[] myItem;
				myItem = temp;
				Capacity *= 2;
				myItem[Size] = item;
			
				
				
			}
		}
		else
		{
			Type * temp = new Type[Capacity * 2];
			for (unsigned int i = 0; i < Size; i++)
			{
				temp[i] = myItem[i];
			}
			delete[] myItem;
			myItem = temp;
			myItem[Size] = item;
		
			
		}
		Size++;
		
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : reserve
	// Parameters : newCap - the new capacity
	// Notes : 	- default parameter - reserve more space in the array, based on //		the expansion rate (100%, 1 minimum).
	//		- non-default parameter, expand to the specified capacity
	//		- if newCap is LESS than the current capacity, do nothing. 
	//		This function should NOT make the array smaller.
	/////////////////////////////////////////////////////////////////////////////
	void reserve(const unsigned int & newCap = 0)
	{
		
		if (newCap == 0)
		{
			if (Capacity > 0)
			{
				Type * temp = new Type[Capacity * 2];
				for (unsigned int i = 0; i < Size; i++)
				{
					temp[i] = myItem[i];
				}
				delete[] myItem;
				Capacity *= 2;
				myItem = new Type[Capacity];
				for (unsigned int i = 0; i < Size; i++)
				{
					myItem[i] = temp[i];
				}
				delete[] temp;
			}
			else
			{
				Capacity = 1;
				myItem = new Type[Capacity];
			}
		}
		else if (newCap > Capacity)
		{
			Type * temp = new Type[newCap];
			for (unsigned int i = 0; i < Size; i++)
			{
				temp[i] = myItem[i];
			}
			delete[] myItem;
			Capacity = newCap;
			myItem = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				myItem[i] = temp[i];
			}
			delete[] temp;
		}
	}

};