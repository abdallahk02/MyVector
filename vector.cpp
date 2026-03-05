#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
class MyVector{
private:
    std::unique_ptr<T[]> data_ptr;
    size_t sz;
    size_t cap;

public:
    MyVector() : data_ptr(nullptr), sz(0), cap(0) {} // default constructor

    MyVector(const MyVector& old_vector){
        this->sz = old_vector.sz;
        this->cap = old_vector.cap;
        this->data_ptr = std::make_unique<T[]>(cap);
        for(size_t i = 0; i < sz; i++){
            this->data_ptr[i] = old_vector.data_ptr[i];
        }
    }

    MyVector(size_t vec_sz){
        sz = vec_sz;
        cap = vec_sz*2;
        data_ptr = std::make_unique<T[]>(cap);
    }

    T* begin(){
        return data_ptr.get();
    }

    T* end(){
        return data_ptr.get()+sz;
    }

    void push_back(const T& elem){
        if(sz == cap){
            if(cap > 0) reallocate(cap*2);
            else reallocate(1);
        }
        data_ptr[sz] = elem;
        sz++;
    }

    void pop_back(){
        if(sz == 0){
            throw std::invalid_argument("Cannot pop_back empty vector");
        }

        data_ptr[sz-1] = T();
        sz--;

    }

    void reallocate(size_t newCap){
        if(newCap < sz){
            throw std::invalid_argument("Capacity cannot be less than size");
        }

        auto newBlock = std::make_unique<T[]>(newCap);
        for(size_t i = 0; i < sz; i++){
            newBlock[i] = std::move(data_ptr[i]);
        }
        data_ptr = std::move(newBlock);
        cap = newCap;
    }

    size_t getSize(){
        return sz;
    }

    size_t getCapacity(){
        return cap;
    }

    T& operator[](size_t i){
        if(i >= sz || i < 0){
            throw std::invalid_argument("Index out of bounds");
        }
        return data_ptr[i];
    }
    
};

int main(){

    MyVector<int> test;

    test.push_back(31);
    test.push_back(32);
    test.push_back(33);
    test.push_back(34);

    for(int i = 0; i < test.getSize(); i++){
        std::cout << test[i] << std::endl;
    }

    test.pop_back();
    test.pop_back();

    for(int i = 0; i < test.getSize(); i++){
        std::cout << test[i] << std::endl;
    }

    return 0;
}