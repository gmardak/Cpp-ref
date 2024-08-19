#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name

// -------------------Declaring a Class and Creating Objects------------------------------

class Player {                              // A class declaration;
    //attributes                            // Attributes;
    std::string name;
    int health;

    //methods
    void talk(std::string text_to_display); // Methods;
    bool is dead();
};

Player frank;                               // Creating an object from a class
Player *enemy = new Player();               // Creating a pointer to a class that will be stored
delete enemy;                               // in heap, and freeing the memory;

class Account{};
Account frank_account;
Account mary_account;

Account accounts[] = {frank_account, mary_account};     // Creating an array of accounts
std::vector<Account> vec_accounts = {frank_account};    // Creating vector of objects accounts;
vec_accounts.push_back(mary_account);                   // Pushing account object to vector;

// -------------------Accessing Class Members------------------------------

class Account{                      // Class definition;
    double balance {100};

    void deposit(double amount){
        balance += amount;
    }
};

Account frank_account;              // Creating frank_account object from Account class;
frank_account.balance;              // Accessing balance attribute of frank_account obj;
frank_account.deposit(100.0);       // Accessing method of the object;

Account *mary_account = new Account();      // Creating a pointer to the Account class;

(*mary_account).balance;                    // Dereference and access attributes and methods;
(*mary_account).deposit(100.0);

mary_account->balance;                      // -> operator deferences pointer;
mary_account->deposit(100.0);               // Use -> to deference a pointer to class

// -------------------Access Modifiers: public and private------------------------------

class Account{                          // Class definition;
    private:
        double balance {100};           // Only object methods have access to private attributes;

    public:
        void deposit(double amount){    // To access method outside of class, it has to public;
            balance += amount;
        }
};

Account frank_account;
frank_account.balance = 1000;           // ERROR!
frank_account.deposit(1000.0);          // OK

// -------------------Implementing Member Methods------------------------------

class Account{                          // Class definition;
    private:
        double balance {100};           // Only object methods have access to private attributes;

    public:
        bool deposit(double);           // It is easier to separate class methods specification
};                                      // and implementation to hpp and cpp files;
    // in cpp file
bool Account::deposit(double amount){   // Implement methods in separate cpp file
    this->balance += amount;            // Access the class method:
    return true;
}                                       // type Class_Name::Class_method(){};

// -------------------Constructors and Destructors------------------------------
// *** Constructors are invoked during object creatin ***
// *** Same name as the class, no return type is specified, can be overloaded ***
// *** Destructors invoked automatically, no return type and no parameters ***
// *** Only 1 destructor is allowed per class and cannot be overloaded; Frees up memory ***
// *** If you provided a constructor for the class, then you have to specify default constructor***

class Player {
    private:
        std::string name;
        int health;
        int xp;

    public:
        // Overloaded Constructors;
        Player();                                       // No args constructor, default constructor;
        Player(std::string name);                       // Constructor if name is provided;
        Player(std::string name, int health, int xp);
        // Destructor
        ~Player();
};

Player::Player(){};
Player::Player(std::string name){
    this->name = name;
}
Player::Player(std::string name, int health, int xp){
    this->name = name;
    this->health = health;
    this->xp = xp;
}

{
Player slayer;                                  // No args constructor is called;
Player frank {"Frank"};                         // Contructor with name as parameter is called
}                                               // 2 Destructors will be called because objects
                                                // are now out of scope;
Player *enemy = new Player("Thanos", 100, 1000) // Constructor, with all parameters will be called;
delete enemy;                                   // Destructor will be called;

// -------------------Constructor Initialization lists------------------------------
// *** When you don't provide initialization list, attributes will be populated with data ***
// *** More effecient, it doesn't create, copy the data to attribute and destroy it ***
// *** Order of initialization is the order of declaration in the class ***
class Player {
    private:
        std::string name;
        int health;
        int xp;

    public:
        // Overloaded Constructors;
        Player();                                       // No args constructor, default constructor;
        Player(std::string name);                       // Constructor if name is provided;
        Player(std::string name, int health, int xp);
        // Destructor
        ~Player();
};

Player::Player() : name("None"), health{0}, xp{0}{};                // You add initialization
Player::Player(std::string name) : name(name), health{0}, xp{0}{}   // list by adding colon                                           
                                                                    // provide the parameters;
Player::Player(std::string name, int health, int xp) : 
    name(name), health{health}, xp{xp}{};

// -------------------Delegating Constructors------------------------------
// *** C++ allows delegating constructors; Avoids duplicating code ***

class Player {
    private:
        std::string name;
        int health;
        int xp;

    public:
        // Overloaded Constructors;
        Player();                                       // No args constructor, default constructor;
        Player(std::string name);                       // Constructor if name is provided;
        Player(std::string name, int health, int xp);
        // Destructor
        ~Player();
};

Player::Player(std::string name, int health, int xp) :  // Three parameters constructor
    name(name), health{health}, xp{xp}{};

Player::Player() : Player("None", 0, 0){};                  // Delegating no-args constructor to
                                                            // above constructor;
Player::Player(std::string name) : Player(name, 0, 0) {};   // Delegating with name parameter;

// -------------------Default Parameters and Default Values------------------------------
// *** Default parameters can simplify the code ***

class Player {
    private:
        std::string name;
        int health;
        int xp;

    public:
        Player(std::string name = "None", int health = 0, int xp = 0);  // Only 1 constuctor
                                                                        // with default params'
        // Destructor
        ~Player();
};

// -------------------Copy Constructors------------------------------
// *** When objects are copied, c++ creates new object from an existing object ***
// *** Passing by value, returning an object from function, constructing one object based on another ***
// *** C++ provides compiler defined copy constructor ***
// *** IF you don't provide copy constructor, the default copy will do memberwise copy ***
// *** Type::Type(const Type &source);

    // Use case: passing by value in function
Player hero {"Hero", 100, 20};

void display(Player p){
    // Display all attributes of p;
    // p is a COPY of hero;
    // Destructor will be called for p after out of scope;
}

display(hero);

    //Use case: returning object by value
Player enemy;

Player create_super_enemy(){
    Player an_enemy{"Super", 1000, 1000};
    return an_enemy;    // COPY of an_enemy is returned;
}
enemy = create_super_enemy();

    // Use case: Construct one object from another
Player hero {"Hero", 100, 20};
Player another_hero {hero};     // COPY of hero is made here;

class Player {
    private:
        std::string name;
        int health;
        int xp;

    public:
        Player(std::string name = "None", int health = 0, int xp = 0);  // Only 1 constuctor
                                                                        // with default params'
        Player(const Player &source);       // COPY CONSTRUCTOR configuration;
        // Destructor
        ~Player();
};

Player::Player(const Player &source)
    : name{source.name}, health{source.health}, xp{source.xp}
{}

// -------------------Shallow Copying with the Copy Constructor------------------------------
// *** Consider a class that contains a pointer as a member attribute; Constructor allocates
//  storage dynamically and initializes pointer; Then Destructor releases that memory ***
// *** Shallow copy copies the address and now 2 pointers are pointing to the same address ***
// *** When shallow copying is called, then the copy destructor will release the memory ***
// *** If a class has pointer, then delete it in Destructor ***


// -------------------Deep Copying with the Copy Constructor------------------------------
// *** Create a copy of hte pointed-to-data; Each pointer will have a pointer to unique storage in heap ***
// *** Use deep copy when you have raw pointer in your data ***

class Deep{
    private:
        int *data;

    public:
        Deep(int d);                    // Constructor;
        Deep(const Deep &source);       // Copy constructor;
        ~Deep();                        // Destructor;
};

Deep::Deep(int d){
    data = new int;                     // Allocate storage
    *data = d;
}

Deep::~Deep(){
    delete data;                        // Release memory;
}

Deep::Deep(const Deep &source){         // Deep COPY Constructor
    data = new int;                     // Allocate memory
    *data = *source.data;               // Create new storage and copy values;
}

// -------------------Move Constructors------------------------------
// *** Deep copy constructor creates a storage in memory, copies; All of this is performance bottleneck ***
// *** Move constructor moves an object rather than copy it ***
// *** R-value reference operator (&&)
// *** Instead of making deep copy, copies the address of the resource from source to the current object ***
// *** And nulls out the pointer in the source ***
// *** Type::Type(Type &&source);

class Move{
    private:
        int *data;

    public:
        void set_data_value(int d);                 // *data = d;
        int get_data_value();                       // return *data;  dereferenced data;
        Move(int d);                                // Constructor;
        Move(const Move &source);                   // Copy Constructor;
        Move(Move &&source);                        // Move Constructor;
        ~Move();
};
    // For example: vector<Move> moves = {};
    // moves.push_back(Move(10));
Move::Move(const Move &source){                     // Deep Copy Constructor;
    data = new int;
    *data = *source.data;
}

Move::Move(Move &&source) : data(source.data){      // Move Constructors;
    source.data = nullptr;
}

// -------------------Using const with Class------------------------------

const Player hero {"Hero", 100, 20};        // const object is declared, cannot change its
                                            // member attributes;
hero.get_name();                            // ERROR! Because compiler will not allow any methods
                                            // of possibility of changing attributes;

class Player{
    private:
        // -*-
    public:
        std::string get_name() const;       // Will be able to call the method;
};

Player villian();
villian.get_name();                         // OK! Because it is const after the method;

// -------------------Static Class Members------------------------------
// *** A single data member that belongs to class, not objects ***
// *** Useful to store class-wide information ***
// *** Example: how many players do we have at current time ***

class Player{
    private:
        static int num_players;             // Static member of the class

    public:
        static int get_num_player();        // Static method of the class
};

    // Then in .cpp file we have to initialize it, it must happen once only

int Player::num_players = 0;
int Player::get_num_player(){
    return num_players;
}

    // The best place to increment and decrement players are in Constructors and Destructors

Player::Player(std::string name, int health, int xp) :  // Three parameters constructor
    name(name), health{health}, xp{xp}{
        ++num_players;
    };

Player::~Player(){
    --num_player;s
}

// -------------------Friend of a Class------------------------------
// *** Friend of a class is a function or class that has access to private class members ***
// *** That function or class is not a member of the class it is accessing ***

class Player{
    friend void display_player(Player &p);                  // Friend function
    friend void Other_class::display_player(Player &p);     // Friend method of another class
    friend class Other_class;                               // Other class;
    
    private:
        // -*-
    public:
        // -*-
};