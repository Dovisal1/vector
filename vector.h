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
	void initialize();
	void enlarge(unsigned int);

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
	
};