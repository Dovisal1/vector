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
	int sz;
	int tracker;
	void initialize();
	void enlarge(int);

public:
	//constructors
	myVector();
	myVector(int);

	//destructor
	~myVector();

	//write methods
	void pushBack(Type);
	void insert (int, Type);

	//read methods
	int size() const { return sz; }
	Type get(int) const;
	void show() const;

	//copy constructor
	myVector(const myVector&);

	//copy assignment 
	myVector& operator= (const myVector&);
	
};