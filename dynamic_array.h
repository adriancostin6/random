#include <initializer_list>
#include <algorithm>
#include <cstring>
#include <iostream>

template<typename T>
class dynamic_array
{
public:
    ////////////////////////////////////////////////////////////////////////////////
    //constructors
    ////////////////////////////////////////////////////////////////////////////////
    dynamic_array(){}
    
    //constructor for member list initialization
    dynamic_array(std::initializer_list<T> il)
    {
    	size_ += il.size();
    	capacity_ = size_;
    	data_ = new T[capacity_];
    	//      data_ = (T*)malloc((sizeof *data_) * size_);
    	std::copy(il.begin(),il.end(), data_); 
    }
    
    ~dynamic_array() 
    { 
    	std::cout << "destructor called\n";
    	delete[] data_; 
    }
    ////////////////////////////////////////////////////////////////////////////////
    //element access
    ////////////////////////////////////////////////////////////////////////////////
    T& operator[](size_t index){ return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    
    ////////////////////////////////////////////////////////////////////////////////
    //operations
    ////////////////////////////////////////////////////////////////////////////////
    
    //allocate memory so the container can hold at least a number of elements
    //that is equal to size
    //if size is less than capacity do nothing
    void reserve(size_t size) 
    { 
    	if(size <= capacity_)
    		return;
    
    	capacity_ = size;
    	T* data = new T[size_];
    	std::copy(data_, data_ + size_, data);
    	if(data_)
    		delete[] data_;
    	data_ = new T[capacity_];
    	std::copy(data, data + size_, data_);
    	delete[] data;
    	//      data_ = (T*)realloc(data_, (sizeof *data_) * capacity_); 
    }
    
    //returns element at index
    //throws if index is invalid 
    constexpr const T& at(size_t index) const
    { 
    	if(index < size())
    		return data_[index];
    	throw std::out_of_range ("Index out of range");
    }
    
    //resize by 2*N for amortized constant time insertion
    void push_back(const T& data)
    {
    	if(!size_ && !capacity_)
    	{
    		data_ = new T[1];
    		data_[size_] = data;
    		size_++;
    		capacity_ = size_;
    		return;
    	}
    
    	//double capacity on memory reallocation
    	if (size_ == capacity_)
    		reserve(capacity_ * 2);
    
    	data_[size_] = data;
    	size_++; 
    }
    
    //pop the last element of the dynamic array by decreasing the size.
    //when size is half of capacity reallocate the memory to shrink
    //the container so you get amortized constant time for popping as well
    void pop_back()
    {
    	size_--;
    	if(size_ == capacity_/2)
    	{
    		//shrink the capacity
    		capacity_ /= 2; 
    
    		//reallocate the memory block and copy over the values
    		T* data = new T[size_];
    		std::copy(data_, data_ + size_, data);
    		if(data_)
    			delete[] data_;
    		data_ = new T[capacity_];
    		std::copy(data, data + size_, data_);
    		delete[] data;
    	}
    
    }
    
    //replaces the contents of the dynamic array with a number of size elements
    //equal to the value of data
    void assign(size_t size, const T& data = 0)
    {
    	if(data_)
    		delete[] data_;
    
    	size_ = size;
    	capacity_ = size_;
    	data_ = new T[capacity_];
    
    	for(uint32_t i= 0;i<capacity_;++i)
    		data_[i] = data;
    }
    
    //replaces the contents of the dynamic array with contents of memory block
    //of size being pointed at by the data pointer
    void assign (size_t size, const T* data)
    {
    	if(data_)
    		delete[] data_;
    
    	size_ = size;
    	capacity_ = size_;
    	data_ = new T[capacity_];
    
    	std::copy(data, data + size, data_);
    }
    
    //inserts new element(s) before the specified position 
    //
    //input: 
    //  position - pointer to the dynamic array element where to insert
    //  data - data to insert 
    //  size - how many items of data to insert
    void  insert(T* position, const T& data, size_t size = 1)
    {
    	//calculate insert index
    	uint32_t index = position - data_;
    
    	//if size is to small, reallocate
    	if(size_ + size > capacity_)
    		reserve(2 * capacity_);  
    
    	//do size number of shifts to make room for new elements
    	uint32_t shifts = size;
    	while(shifts)
    	{
    		//shift array elements to the right 
    		for(uint32_t i = size_+size-1; i>index; --i)
    			data_[i] = data_[i-1];
    		shifts--;
    	}
    	size_ += size;
    
    	//insert size elements to the array from the index position
    	for(uint32_t i = index; i<index+size; ++i)
    		data_[i] = data;
    
    }
    
    //insert elements stored in memory block pointed to by data, of size
    //returns pointer to the first of the newly inserted elements
    void insert(const T* position, T* data, size_t size)
    {
    	//calculate insert index
    	uint32_t index = position - data_;
    
    	//if size is to small, reallocate
    	if(size_ + size > capacity_)
    		reserve(2 * capacity_);  
    
    	//do size number of shifts to make room for new elements
    	uint32_t shifts = size;
    	while(shifts)
    	{
    		//shift array elements to the right 
    		for(uint32_t i = size_+size; i>index; --i)
    			data_[i] = data_[i-1];
    		shifts--;
    	}
    	size_ += size;
    
    	//insert size elements to the array from the index position
    	std::copy(data, data+size, &data_[index]);
    }
    
    void resize(size_t size, const T& data = 0)
    {
    	//shrink the dynamic array to the specified size
    	if(size < size_)
    	{
    		size_ = size;
    		capacity_ = size_;
    		//allocate temporary block 
    		T* data = new T[size];
    
    		//copy the data 
    		std::copy(data_, data_ + size_, data);
    
    		//free the current block of memory 
    		if(data_)
    			delete[] data_;
    
    		//reallocate the resized block
    		data_ = new T[capacity_];
    
    		//copy the data from the temporary block
    		std::copy(data, data + size_, data_);
    
    		//free temporary block
    		delete[] data;
    	}
    
    	//resize the dynamic array and fill it up to capacity with 0 or
    	//specified value
    	if(size > capacity_)
    	{
    		reserve(size);
    		if(data)
    		{
    			for(uint32_t i= size_;i<capacity_;++i)
    				data_[i] = data;
    			size_ = capacity_;
    		}
    		else
    			size_ = capacity_;
    	}
    }
    
    //free unused memory in dynamic array where capacity > size
    void shrink_capacity()
    {
    	if (size_ >= capacity_)
    		return;
    
    	capacity_ = size_;
    
    	//copy data to temp
    	T* data = new T[size_];
    	std::copy(data_, data_ + size_, data);
    
    	delete[] data_;
    
    	//copy data from temp
    	data_ = new T[size_];
    	std::copy(data, data+ size_, data_);
    
    	delete[] data;
    }
    
    //access front and back elements
    constexpr const T& front() const { return data_[0]; }
    constexpr const T& back() const { return data_[size()-1]; }
    
    //check if empty
    constexpr bool empty() { return size() == 0; }
    
    //get size and data 
    constexpr size_t size() const { return size_; }
    constexpr size_t capacity() const { return capacity_; }
    T* data(){ return data_; }
    const T* data() const { return data_; }
    
    //returns pointer to specified position in the vector
    const T* position(uint32_t index) const
    {
    	//throw exception for invalid index
    	if(index > size_)
    		throw std::out_of_range("Index out of range!");
    	return &data_[index]; 
    }

private:
    T* data_;
    size_t size_ = 0, capacity_ = 0;

};
