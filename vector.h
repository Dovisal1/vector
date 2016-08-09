#include <initializer_list>
#include <cctype>

/*
 *
 *  A primitive vector-like container.
 *  Hopefully it will become more refined.
 *
 */


template <class Type>
class myVector
{

private:

    Type * p;
    unsigned int sz;
    
    //set all elements to the argument
    void initialize(Type val)
    {
        for (unsigned int i=0; i < sz; i++)
            p[i] = val;   
    }
    
    //Sets all elements to zero
    void initialize()
    {
        initialize(0);  
    }

    //hopefully this isn't a memory leak
    void enlarge(unsigned int inc)
    {
        //creating a new array with the new size
        Type * temp = new Type[sz+inc];

        //setting the new array to the values of the old
        for(unsigned int i=0; i < sz; i++)
            temp[i] = p[i];

        //initializing all the extra slots to zero
        for(unsigned int i = sz; i < sz + inc; i++)
            temp[i] = 0;    

        //deleting the old array
        delete[] p; 

        //setting the pointer to the new array
        p = temp;   

        //increasing the size by the increase
        sz += inc;

        //temp will go out of scope here
        //the array remains and p points to it
    }




    //The argument is the amount of element
    //that will be removed from the end
    void reduce(unsigned int red)
    {
        //reducing the size
        sz -= red;

        //creating an array with the new size
        Type * temp = new Type[sz];

        //saving as many elements as possible
        for(unsigned int i=0; i < sz; i++)
            temp[i] = p[i];

        //deleting the old array
        delete[] p;

        //pointing vector to the right array
        p = temp;
    }



    //Original versions of the container relied more on this method:

    //makes sure vector is not too small
    //enlarges it as necessary
    void checkSize(unsigned int pos)
    {
        //we want to enlarge to vector to be able to
        //inlcude that position
        //Adding 1 is necessary because size is
        //actually one greater than the last position index
        if ( pos >= sz )
            this->enlarge(pos - sz + 1);
    }





public:
    //constructors
    myVector() : p(new Type[0]) ,sz(0) { }


    myVector(unsigned int size) : p(new Type[size]), sz(size)
    {
        this->initialize();
    }



    myVector(unsigned int size, Type val) : p(new Type[size]), sz(size)
    {
        this->initialize(val);
    }



    myVector(std::initializer_list<Type> seq) : p(new Type[seq.size()] ), sz( seq.size() )
    {
        //Copying the elements of the initializer list into the vector
        std::copy(seq.begin(), seq.end(), p);
    }



    //destructor
    ~myVector() { delete[] p; }

    

    //write methods:

    void push_back(Type val)
    {
        //extending the array by one
        this->enlarge(1);

        //adding to the end
        p[sz-1] = val;
    }



    //Swaps two elements in the vector

    void swap(unsigned int pos1, unsigned int pos2)
    {
        Type hold;
        hold = p[pos1];
        p[pos1] = p[pos2];
        p[pos2] = hold; 
    }



    //bubble sorts the vector in ascending order
    void sort()
    {
        bool switched = true;

        for(unsigned int pass = 0; pass < sz - 1; pass++)
        {
            switched = false;

            for(unsigned int j = 0; j < sz - pass - 1; j++)
                if( p[j] > p[j+1] )
                    this->swap(j, j+1);
        }

    }


    //bubble sorts the vector in descending order
    void rsort()
    {
        bool switched = true;

        for(unsigned int pass = 0; pass < sz - 1; pass++)
        {
            switched = false;

            for(unsigned int j = 0; j < sz - pass - 1; j++)
                if( p[j] < p[j+1] )
                    this->swap(j, j+1);
        }

    }



    void replace(unsigned int pos, Type elem)
    {
        p[pos] = elem;
    }



    void replace(unsigned int start, unsigned stop, Type elem)
    {
        for(unsigned int i = start; i < stop; i++)
            p[i] = elem;
    }



    void insert(unsigned int pos, Type elem)
    {
        Type *temp = new Type[sz+1];
        sz++;

        unsigned int i;

        for(i = 0; i < pos; i++)
            temp[i] = p[i];

        temp[i] = elem;
        i++;

        for( ; i < sz; i++)
            temp[i] = p[i-1];

        delete[] p;

        p = temp;
    }


    //Erase methods:

    void clear ()
    {
        delete[] p;

        sz = 0;

        p = new Type[0];
    }




    void resize(unsigned int size)
    {
        if(size > sz)
            this->enlarge(size-sz);
        else if(size < sz)
            this->reduce(sz-size);
    }


    void pop_back()
    {
        this->reduce(1);
    }



    void erase(unsigned int pos)
    {
        Type * temp = new Type[sz-1];

        //j keeps track of temp
        //i keeps track of p

        unsigned int i, j;

        for(i = 0, j = 0; i < pos; i++, j++)
            temp[j] = p[i];

        for(i = pos + 1; i < sz; i++, j++)
            temp[j] = p[i];

        delete[] p;

        p = temp;
        sz--;
    }


    void erase(unsigned int start, unsigned int stop)
    {

        //calculating the numbers of element to
        //reduce by in new array

        unsigned int range = stop - start;

        Type * temp = new Type[sz-range];

        //j keeps track of temp
        //i keeps track of p

        unsigned int i, j;

        for(i = 0, j = 0; i < start; i++, j++)
            temp[j] = p[i];

        for(i = stop; i < sz; i++, j++)
            temp[j] = p[i];

        delete[] p;

        p = temp;
        sz -= range;
    }


    Type& front()
    {
        return *p;
    }


    Type& back()
    {
        return p[ sz-1 ];
    }


    //status methods:

    //checks if the array has size

    bool empty() const { return sz == 0; }


    //Return largest in the vector
    Type largest()
    {
        Type largest = p[0];

        for(unsigned int i = 1; i < sz; i++)
            if( p[i] > largest)
                largest = p[i];

        return largest;
    }



    //return the smallest in the array
    Type smallest()
    {
        Type smallest = p[0];

        for(unsigned int i = 1; i < sz; i++)
            if( p[i] < smallest)
                smallest = p[i];

        return smallest;
    }


    
    //read methods:

    unsigned int size() const { return sz; }

    unsigned int begin() const { return 0; }


    //This can cause undefined behavior if range error
    //This shouldn't happen because the vector knows its size
    //The programmer must use good practice
    Type at(unsigned int pos) const { return p[pos]; }





    //copy constructor:

    myVector(const myVector& param) : sz(param.sz), p(new Type[param.sz])
    {
        //setting new array to the values of param
        for (unsigned int i=0; i < sz; i++)
            p[i] = param.p[i];

    }


    //copy assignment from other array:

    myVector& operator= (const myVector& param)
    {
        sz = param.sz;

        delete[] p;

        //creating new array
        p = new Type[sz];

        //setting new array to the values of param
        for (unsigned int i = 0; i < sz; i++)
            p[i] = param.p[i];

        return *this;
    }


    //copy assignment to initializer list:

    myVector& operator= (std::initializer_list<Type> seq)
    {
        //takes the lists size
        sz = seq.size();

        delete[] p;

        p = new Type[sz];

        //copies the lists contents to the array
        std::copy(seq.begin(), seq.end(), p);

        //returning value by reference
        //so that we can chain assignments
        //ex: vector1 = vector2 = {1,2,3,4}

        return *this;
    }


    //Offset Operator:


    //return a reference so that we can alter value if we want
    Type& operator[] (unsigned int pos)
    {
        this->checkSize(pos);
        return p[pos];
    }


    //This can have undefined behavior
    const Type& operator[] (unsigned int pos) const
    {
        return p[pos];
    }


    //Returning pointers to the first element;

    Type* data() { return p; }

    const Type* data() const {return p; } 

    Type* end() { return p+sz; }

    const Type* end() const { return p+sz; }

};

//String template specializations

template<>
void myVector<std::string>::initialize()
{
    for (unsigned int i=0; i < sz; i++)
        p[i] = "";   
}

template<>
void myVector<std::string>::enlarge(unsigned int inc)
{
    //creating a new array with the new size
    std::string * temp = new std::string[sz+inc];

    //setting the new array to the values of the old
    for(unsigned int i=0; i < sz; i++)
        temp[i] = p[i]; 

    //initializing all the extra slots to zero
    for(unsigned int i = sz; i < sz + inc; i++)
        temp[i] = "";    

    //deleting the old array
    delete[] p; 

    //setting the pointer to the new array
    p = temp;   

    //increasing the size by the increase
    sz += inc;

    //temp will go out of scope here
    //the array remains and p points to it
}

template<>
void myVector<std::string>::sort()
{
    std::string strupr(std::string);

    bool switched = true;

    for(unsigned int pass = 0; pass < sz - 1; pass++)
    {
        switched = false;

        for(unsigned int j = 0; j < sz - pass - 1; j++)
            if( strupr( p[j] ) > strupr( p[j+1] ) )
                this->swap(j, j+1);
    }

}


//Recieves a string
//Return the uppercase string

std::string strupr(std::string str)
{
    for(int i =0; i < str.length(); i++)
        str[i] = toupper( str[i] );

    return str;
}
