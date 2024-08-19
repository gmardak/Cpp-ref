#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name

// -------------------Issues with Raw Pointer------------------------------
// *** C++ raw pointers flexible: allocate, deallocate, lifetime management ***
// *** Potential problems: unitialized (wild) pointer, memory leaks, dangling pointers, not exception safe ***
// *** Smart pointers will resolve this issues ***

// -------------------What is Smart Pointers? Ownership and RAII------------------------------
// *** Smart pointers are objects, can only point to heap-allocated memory ***
// *** Smart pointers automatically call delete when no longer needed and adhere RAII ***
// *** C++ smart pointers: Uniques, Shared, Weak pointers ***
// *** #include <memory> lib; Wrapper around a raw pointer; Cannot do pointer arithmetics ***
// *** RAII - Resource Acquisition Is Initialization: allocated at stack ***
#include <memory>

{
    std::smart_pointer<Some_Class> ptr = ...;       // You have to provide smart pointer type

    ptr->method();
    cout << (*ptr) << endl;
}

// -------------------Unique Pointers------------------------------
// *** Efficient to use instead of most raw pointer application ***
// *** unique_ptr<T> points to an object of type T on the heap ***
// *** It is unique and can only be one unique_ptr<T>, owns what it points to ***
// *** Cannot be assigned or copied, but CAN be moved ***

{
    std::unique_ptr<int> p1 {new int {100}};
    std::cout << *p1 <<std::endl;               // 100
    *p1 = 200;
    std::cout << *p1 <<std::endl;               // 200

    p1.get();                                   // 0x564388 gets the address of the pointer;
    p1.reset();                                 // p1 is now nullptr;
    if(p1){                                     // will not execute, because now it is nullptr;

    }
}   // Automatically deleted;

{
    std::unique_ptr<Account> p1 {new Account{"Larry"}};
    std::cout << *p1 <<std::endl;                       // Display account;
    p1->deposit(100.0);
    p1->withdraw(100.0);
}   // Automatically deleted;

{
    std::vector<std::unique_ptr<int>> vec;

    std::unique_ptr<int> ptr {new int{100}};

    vec.push_back(ptr)                          // ERROR - copy not allowed
    vec.push_back(std::move(ptr));              // MOVE unique pointer

}   // Automatically deleted;

    // Better way of initializing, no calls to new or delete;
{
    std::unique_ptr<int> p1 = std::make_unique<int>(100);

    std::unique_ptr<Account> p2 = std::make_unique<Account>("Curly", 5000);

    auto p3 = std::make_unique<Player>("Hero", 100, 20);
}


// -------------------Shared Pointers------------------------------
// *** Provide shared ownership of heap objects ***
// *** There can be many shared_ptr pointing to the same object on the heap ***
// *** CAN be assigned and copied and moved
// *** Doesn't support managing arrays by default ***
// *** When use count is zero, the managed object on the heap is destroyed ***

{
    std::shared_ptr<int> p1 {new int {100}};    // 100
    *p1 = 200;                                  // 200
    std::cout << p1.use_count();                // 1

    std::shared_ptr<int> p2 {p1};
    std::cout << p2.use_count();                // 2
    // use_count - the number of shared_ptr objects managing the heap object
    p1.reset();                                 // decrement the use_count; p1 is nulled out
    std::cout << p1.use_count();                // 0
    std::cout << p2.use_count();                // 1
}   // Automatically deleted

{
    std::shared_ptr<Account> p1 {new Account{"Larry"}};
    std::cout << *p1 << std::endl;                      // display account
    p1->withdraw(100.0);
    p1->deposit(100.0);
}

{
    std::vector<std::shared_ptr<int>> vec;
    std::shared_ptr<int> ptr {new int{100}};
    vec.push_bakc(ptr);                         // OK, copy is allowed
    std::cout << ptr.use_count();               // 2
}

{
    std::shared_ptr<int> p1 = std::make_shared<int>(100);       // use_count: 1;
    std::shared_ptr<int> p2 { p1 };                             // use_count: 2;
    std::shared_ptr<int> p3;
    p3 = p1;                                                    // use_count: 3;
    // All 3 pointers point to the same object on the heap
}

// -------------------Weak Pointers------------------------------
// *** Provides a non-owning weak reference ***
// *** Points to and object of type <type> on the heap, doesn't participate in owning relationship ***
// *** Always created from a shared_ptr, doesn't increment or decrement use count ***
// *** Used to prevent strong reference cycles which could prevent objects being deleted ***
// *** Example A(shared_ptr<B>) ---> <--- B(share_ptr<A>), when objects deleted, pointers not, memory leak ***
// *** A(shared_ptr<B>) ---> <--- B(weak_ptr<A>), we made pointer weak, so it will be deleted ***

std::weak_ptr<A> a_ptr;             // Defining weak pointer

class B;

class A{
    std::shared_ptr<B> b_ptr;

    public:
        void set_B(std::shared_ptr<B> &b){
            b_ptr = b;
        }
        A() {cout<< "A Constructor\n";};
        ~A() {cout << "A Destructor\n";};
};

class B {

    // std::shared_ptr<A> a_ptr;        // Make weak to break the strong circular reference;
    std::weak_ptr<A> a_ptr;             // Weak pointer;

    public:
        void set_A(std::shared_ptr<A> &a){
            a_ptr = a;
        }
        B() {cout<< "B Constructor\n";};
        ~B() {cout << "B Destructor\n";};
}

// -------------------Custom Deleters------------------------------
// *** It is only in some special cases, sometimes, you need more than just delete object
// *** when deleting smart pointers ***

void my_deleter(Some_Class *raw_pointer){
    // custom deleter code
    delete raw_pointer;
}

shared_ptr<Some_Class> ptr {new Some_Class{}, my_deleter};