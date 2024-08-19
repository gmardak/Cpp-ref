#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name

// -------------------What is Inheritance------------------------------
// *** Inheritance has "Is A" relationship: Checking Account is an Account ***
// *** Inheritance vs Composition: Composition is "Has a" relationship: student has an account ***
// *** Parent class is generalized, more abstract, for example: Player ***
// *** As you go down in hirearchy, the more specialized is class, for example: Arthur_hero ***

class Account {
    // balance, deposit, withdraw;
};

class Savings_account : public Account{
    // interest rate, specialized withdraw, ...
};

Account account{};
Account *p_account = new Account();         // Creating pointer to an account object

p_account->deposit(1000.0);

Savings_account sav_account {};             // Declaring Saving account object, class has been
                                            // inherited from Account class;

// -------------------Protected Members and Class Access------------------------------
// ***                  Public Inheritance
// *** Base Class                   Access in Derived Class
// *** public: a                    public: a
// *** protected: b                 protected: b
// *** private:c                    c : no access

// ***                  Protected Inheritance: is not "Is a" inheritance
// *** Base Class                   Access in Derived Class
// *** public: a                    protected: a
// *** protected: b                 protected: b
// *** private:c                    c : no access

// ***                  Private Inheritance: is not "Is a" inheritance
// *** Base Class                   Access in Derived Class
// *** public: a                    private: a
// *** protected: b                 private: b
// *** private:c                    c : no access


// -------------------Constructors and destructors------------------------------
// *** Any derived class first calls its base/parent class constructor: from up to down ***
// *** Destructors are called in reverse order: from bottom to up ***
// *** Derived class doesn't inherit: Base class constructor, destructor
//                                    Base class overloaded assignment operator, friend functions
// *** However, Derived class invokes Base class constructors, destructors;

class Base{
    public:
        Base(){
            std::cout << "Base Constructor";
        }
};

class Derived : public Base{
    public:
        Derived(){
            std::cout << "Derived Constructor";
        }
};

Base base;          // Output: Base Constructor
Derived derived;    // Output: Base Constructor
                    //         Derived Constructor


// -------------------Passing Arguments to Base Class Constructors------------------------------

class Base{
    private:
        int value;
    public:
        Base() : value{0};
        Base(int x) : value{x};
};

class Derived : public Base{
    private:
        int doubled_value;
    public:
        Derived() : Base(), doubled_value{0}{
            // code
        }
        Derived(int x) : Base(x), doubled_value{x*2}{
            // code
        }
};

// -------------------Copy/Move Constructors and Operator= with Derived Classes------------------------------
// *** Copy/Move constructores and overloaded= operators are NOT inherited from the Base class ***
// *** We can explicitly invoke the Base class version from the Derived class ***
// *** If we provide Copy/Move/operator= in Derived, then we have to explicitly call Base Copy/Move/operator ***

class Base {
    int value;
    public:
        // Same constructors as previous example
        Base(const Base &other) : value{other.value} {
            // code
        }

        Base &operator=(const Base &rhs){
            if(this != rhs.value){
                value = rhs.value;
            }
            return *this;
        }
};

class Derived : public Base {
    int doubled_value;

    public:
        // Same constructors as previous example
        // Will work in other because derived is Base
        Derived(const Derived &other) : Base(other), doubled_value{other.doubled_value}{
            // code
        }

        Derived &operator=(const Derived &rhs){
            if(this ~= &rhs){
                Base::operator=(rhs);               // Assign Base part
                doubled_value = rhs.doubled_value;  // Assign Derived part
            }
            return *this;
        }
}

// -------------------Redfining Base Class Methods------------------------------
// *** Derived class can directly invoke Base class methods ***
// *** Derived class can OVERRIDE or redefine Base class methods, but signatures must match ***
// *** By default, C++ does static binding at compile time ***

class Account {
    public:
        void deposit(double amount) {
            balance += amount;
        }
};

class Savings_Account : public Account {
    public:
        void deposit(double amount){        // Redefine Base class method;
            amount += some_interest;
            Account::deposit(amount;)       // Invoke call Base class method;
        }
};

Base b;
b.deposit(100.0);               // Base::deposit

Derived d;
d.deposit(100.0);               // Derived::deposit

Base *ptr = new Derived();      // Possible, because Derived is Base
ptr->deposit(100.0)             // Base::deposit will be called, because it was binded to 
                                // Base at compile time, because pointer is pointing to Base class