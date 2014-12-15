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
	int size() const { return sz; }
	Type get(unsigned int) const;
	void show() const;

	//copy constructor
	myVector(const myVector&);

	//copy assignment 
	myVector& operator= (const myVector&);
	
};