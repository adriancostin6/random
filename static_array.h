#include <initializer_list>
#include <algorithm>

//static array of fixed size allocated on the stack
template<typename T, size_t S>
class static_array
{
public:
    ////////////////////////////////////////////////////////////////////////////////
    //constructors
    ////////////////////////////////////////////////////////////////////////////////
    
    static_array(){} 
    
    //constructor with member initializer list
    //use case: static_array<T> arr{elem1,elem2...};
    static_array(std::initializer_list<T> il)
    { std::copy(il.begin(),il.end(), data_); }
    
    ////////////////////////////////////////////////////////////////////////////////
    //operators - todo
    ////////////////////////////////////////////////////////////////////////////////
    
    //        inline bool
    //        operator<(static_array<T,S> a, static_array<T,S> b)
    //        {}
    //        inline bool
    //        operator>(static_array<T,S> a, static_array<T,S> b)
    //        {}
    //        inline bool
    //        operator<=(static_array<T,S> a, static_array<T,S> b)
    //        {}
    //        inline bool
    //        operator>=(static_array<T,S> a, static_array<T,S> b)
    //        {}
    //        inline bool
    //        operator==(static_array<T,S> a, static_array<T,S> b)
    //        {}
    //        inline bool
    //        operator!=(static_array<T,S> a, static_array<T,S> b)
    //        { return !(a == b); }
    
    ////////////////////////////////////////////////////////////////////////////////
    //element access
    ////////////////////////////////////////////////////////////////////////////////
    
    //no bounds checking, accessing an index outside the array is undefined
    //behaviour
    T& operator[](size_t index){ return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    
    ////////////////////////////////////////////////////////////////////////////////
    //operations
    ////////////////////////////////////////////////////////////////////////////////
    
    //returns element at index
    //throws if index is invalid 
    constexpr const T& at(size_t index) const
    { 
    	if(index < size())
    		return data_[index];
    	throw std::out_of_range ("Index out of range");
    }
    
    //access front and back elements
    constexpr const T& front() const { return data_[0]; }
    constexpr const T& back() const { return data_[size()-1]; }
    
    //check if empty
    constexpr bool empty() { return size() == 0; }
    
    //get size and data 
    constexpr size_t size() const { return S; }
    T* data(){ return data_; }
    const T* data() const { return data_; }

private:
    T data_[S] = {};
};
