#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name

// -------------------What is Polymorphism------------------------------
// *** We have done polymorphism when we did overloaded functions and operators; compile-time/ static binding ***
// *** Run-time/Dynamic binding ***
// *** When I call deposit method, the class will take care of what kind of account and what method to call ***
// *** Runtime polymorphism: Function Overriding ***
    // Examples of static binding
Account a;
a.withdraw(100.0);              // Account::withdraw();

Savings b;
b.withdraw(100.0);              // Savings::withdraw();

Account *p -> new Trust();
p->withdraw(100.0);             // Account::withdraw(); should be Trust::withdraw();

void display_account(const Account &acc){       // A function that display account info;
    acc.display();
    // will always use Account::display
}


// -------------------Using Base Class Pointer------------------------------
// *** For dynamic polymorphism we must have: Inheritance, Base class pointer/reference, virtual functions ***

// -------------------Virtual Functions------------------------------
// *** If we don't use virtual functions, then it will be statically binded ***
// *** Redefined functions are bound statically ***
// *** Overriden functions are bound dynamically ***
// *** Virtual functions are overriden ***
// *** To override a function, the signature must match exactly, otherwise compiler will
//     treat it as redifined functions

class Account {
    public:
        virtual void withdraw(double amount);
        // ...
};

class Checking : public Account{
    public:
        virtual void withdraw(double amount);
}

// -------------------Virtual Destructors------------------------------
// *** If derived class is destroyed by deleting its storage via the base class pointer
//     and the class a doesn't have a virtual destructor, then behavior is undefined ***
// *** If a class has virtual functions, it must provide virtual destructors ***
// *** If base class destructor is virtual, then all derived class destructors are also virtual ***

class Account {
    public:
        virtual void withdraw(double amount);       // Virtual function;
        virtual ~Account();                         // Virtual destructor;
};

// -------------------Override Specificer------------------------------
// *** We must provide the same function signature and return to override Base class methods ***
// *** If functions signatures are different, then it is redefinition, NOT overriding ***
// *** Redifine - statically bound; Override - dynamically bound ***
// *** Add "override" keyword and compiler is sure that you are tryin to override ***
// *** Sometimes, you make small mistakes in derived function that you are tyring to override
//     and compiler thinks that you are trying to redifine. Adding override prevents it and throw error ***

class Base{
    public:
        virtual void say_hello() const {
            std::cout << "Hello \n";
        }
        virtual ~Base(){};
};

class Derived : public Base{
    public:
        virtual void say_hello() const override {   // Will give you compiler error because
            std::cout << "Hello \n";                // you missed const part from Base class;
        }
        virtual ~Derived(){};
};

// -------------------Final Specifier------------------------------
// *** When used at the class level: prevents a class from being derived from ***
// *** When used at the model level: Prevents virtual method from being overriden in derived class ***

class My_class final {      // You cannot derive any class from this class;
    // ...
};

class Derived final : public Base {};       // You cannot derive any class from Derived;

class A {
    virtual void do_something() final {     // Prevent further overriding;
        // ...
    }
};

// -------------------Using Base Class References------------------------------
// *** We can use Base class references with dynamic polymorphism ***

Trust t;                    // Trust is derived from Account;
Account &ref1 = t;          // Declare ref1 as reference to t, thus ref1 will hold address to t;
ref1.withdraw(1000.0);      // Trust::withdraw, it dynamically binds it;

void do_withdraw(Account &account, double amount){
    account.withdraw(amount);
}

Account a;
do_withdraw(a, 100.0);      // Account::withdraw

Trust t;
do_withdraw(t, 100.0);      // Trust::withdraw


// -------------------Pure Virtual Functions and Abstract Classes------------------------------
// *** Abstract classes: cannot instantiate objects, too generic
//                       used as base classes for inheritance (like shape, account) ***
// *** Concrete classes: used to instantiate objects from (like savings account, circle, square) ***
// *** In order for class to be abstract, it must contain at least 1 pure virtual function ***
// *** Virtual function: used to make class abstract
//                       specified with "=0" in declaration: virtual void function() = 0;
//                       typically do not provide implementation, but you can if you want ***
// *** Derived class must override the base class methods, otherwise, it will also be abstract ***

class Shape {                           // Abstract class;
    private:
        // ...
    public:
        virtual void draw() = 0;        // Pure virtual function;
        virtual void rotate() = 0;      // Pure virtual function;
        virtual ~Shape();
};

class Circle : public Shape{            // Concrete class
    private:
        // ...
    public:
        virtual void draw() override {
            // code
        }
        virtual void rotate() override {
            // code
        }
        virtual ~Circle();
};

// -------------------Abstract Classes as Interfaces------------------------------
// *** Interface specify what class should do, but not how it should do ***
// *** What is using class as an interface: abstract class that has only pure virtual functions
//     Functions provide general set of services, provided as public and must be implemented in derived class ***
// *** C++ uses abstract classes with pure virtual functions to achieve interface ***
// *** Usually you preceed class name with I_ to indicate it is an interface ***

class I_Printable {
    friend std::ostream &operator<<(ostream &, const Printable &obj);

    public:
        virtual void print(ostream &os) const = 0;
        virtual ~Printable();
};

std::ostream &operator<<(ostream &os, const Printable &obj){
    obj.print(os);
    return os;
}

class Any_class : public I_Printable{
    public:
        // must override Printable::print()
        virtual void print(std::ostream &os) override {
            os << "Hi from Any_class";
        }
};

Any_class *ptr = new Any_class();

void function1 (Any_class &obj){
    std::cout << obj << std::endl;
}

void functions2 (Any_class &obj){
    std::cout << obj << std::endl;
}

function1(*ptr);        // "Hi from Any_class";
function2(*ptr);        // "Hi from Any_class";