/*
 *
 *  The vector class implementation
 *
 */


#include <iostream>
#include "vector.h"

using namespace std;


template <class Type>
myVector<Type>::myVector() : p(new Type[5]), sz(5)
{
	tracker = 0;
	this->initialize();
}


template <class Type>
myVector<Type>::myVector(unsigned int s) : p(new Type[s]), sz(s)
{
	tracker = 0;
	this->initialize();
}


template <class Type>
myVector<Type>::~myVector()
{
	delete[] p;
}


template <class Type>
void myVector<Type>::pushBack(Type x)
{
	//if the array has no room left 
	if ( tracker >= sz )
		this->enlarge(5);

	p[tracker] = x;
	tracker++;
}


template <class Type>
void  myVector<Type>::enlarge(unsigned int inc)
{
	//creating a new array that is larger than the original
	Type * temp = new Type[sz + inc];

	//setting the new array the values of the old
	for(unsigned int i=0; i < sz; i++)
		temp[i] = p[i];

	//initializing all the extra slots to zero
	for(unsigned int i = sz; i < sz + inc; i++)
		temp[i] = 0;

	//deleting the old array
	delete p;

	//setting the pointer to the new array
	p = temp;

	//increasing the size counter
	sz += inc;
}

template <class Type>
void myVector<Type>::checkSize(unsigned int pos)
{
	//we want to enlarge to vector to be able to
	//inlcude that position
	//Adding 1 is necessary because size is
	//actually one greater than the last position index
	if ( pos >= sz )
		this->enlarge(pos - sz + 1);
}


template <class Type>
void myVector<Type>::insert(unsigned int pos, Type elem)
{
	this->checkSize(pos);

	//inserting the value into the slot
	p[pos] = elem;
}


template <class Type>
void myVector<Type>::initialize()
{
	for (unsigned int i=0; i < sz; i++)
		p[i] = 0;
}


template <class Type>
Type myVector<Type>::get(unsigned int pos) const
{
	this->checkSize(pos);
	return p[pos];
}


template <class Type>
void myVector<Type>::print() const
{
	for (unsigned int i = 0; i < this->size(); i++)
		cout << this->get(i) << " ";

	cout << endl;
}


template <class Type>
myVector<Type>::myVector(const myVector& param) : sz(param.sz), p(new Type[param.sz]), tracker(param.tracker)
{
	for (unsigned int i=0; i < sz; i++)
		p[i] = param.p[i];
}


template <class Type>
myVector<Type>& myVector<Type>::operator= (const myVector& param)
{
	sz = param.sz;
	tracker = param.tracker;
	//p must be deleted because it is
	//pointing to an existing array
	delete p;

	//creating new array
	p = new Type[sz];

	//setting new array to the values of param
	for (unsigned int i=0; i < sz; i++)
		p[i] = param.p[i];

	return *this;
}

template <class Type>
Type& myVector<Type>::operator[] (unsigned int pos)
{
	this->checkSize(pos);
	return p[pos];
}
