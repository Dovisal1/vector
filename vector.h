/*
 *
 *  The vector class interface
 *
 *
 *
 */

template <class Type>
class myVector
{
	Type * p;
	unsigned int sz;
	unsigned int tracker;

	//Sets all elements to zero
	void initialize();

	//enlarges vector by its param
	void enlarge(unsigned int);

	//makes sure vector is not too small
	//enlarges it as necessary
	void checkSize(unsigned int);

public:
	//constructors
	myVector();
	myVector(unsigned int);

	//destructor
	~myVector();

	//write methods
	void pushBack(Type);
	void insert (unsigned int, Type);

	//read methods
	unsigned int size() const { return sz; }
	Type get(unsigned int) const;
	void print() const;

	//copy constructor
	myVector(const myVector&);

	//copy assignment 
	myVector& operator= (const myVector&);

	//redefining the offset operator
	//return a reference so that we can alter value
	Type& operator[] (unsigned int);
	
};