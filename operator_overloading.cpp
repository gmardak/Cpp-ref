#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name

// -------------------Overloading the Assignment Operator (Copy)------------------------------
// *** Works with L-value reference only ***
// *** Type &Type::operator=(const Type &rhs);

class Mystring{
    private:
        char *str;

    public:
        Mystring();
        Mystring(const char *s);
        Mystring(const Mystring &source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char *get_str() const;
        Mystring &operator=(const Mystring &rhs);       // Copy assignment
};

    // We have only 1 pointer, if more, we need to deep copy all of them;
Mystring &Mystring::operator=(const Mystring &rhs){
    if (this == &rhs){
        return *this;
    }
    delete [] str;      // If we don't release the memory, we orphan the data and have memory leak;
    str = new char[std::strlen(rhs.str) + 1];   // We allocate a new memory in the heap;
    std::strcpy(str, rhs.str);                  // Copy the string C-style string
    return *this;                               // return deferenced this
}

s2 = s1;                // We write this;
s2.operator=(s1);       // operator= method is called;

// -------------------Overloading the Assignment Operator (Move)------------------------------
// *** Works with r-value reference ***
// *** Type &Type::operator=(Type &&rhs);
// *** When we use Move assignment, we are not making copy, we just steal the pointer ***

class Mystring{
    private:
        char *str;

    public:
        Mystring();
        Mystring(const char *s);
        Mystring(const Mystring &source);
        Mystring(const Mystring &&source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char *get_str() const;
        Mystring &operator=(const Mystring &rhs);       // Copy assignment;
        Mystring &operator=(const Mystring &&rhs);      // Move assignment;
};

Mystring &Mystring::operator=(const Mystring &&rhs){
    if (this == &rhs){
        return *this;
    }
    delete [] str;          // If we don't release the memory, we orphan the data and have memory leak;
    str = rhs.str;          // Stealing the pointer;
    rhs.str = nullptr;      // Nullifying the pointer of the r-value;
    return *this;           // return deferenced this;
}

// -------------------Overloading Operators as Member Functions------------------------------

    // Unary operators as member methods (++, --, -, !)
    // ReturnType Type::operatorOP(); 
    
Number Number::operator-() const;
Number Number::operator++();            // Pre-increment;
Number Number::operator++(int);         // Post increment;
bool Number::operator!() const;

Number n1 {100};
number n2 = -n1;
n2 = ++n1;
n2 = n1++;

class Mystring{
    private:
        char *str;

    public:
        Mystring();
        Mystring(const char *s);
        Mystring(const Mystring &source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char *get_str() const;
        Mystring Mystring &operator++() const;
};

Mystring larry1{"Larry"};
Mystring larry2;

larrry2 = -larry1;      // larry1.operator-() is called, that will make tolower case;

    // Binary oeprators as member methods (+, -, ==, !=, <, >)
    // ReturnType Type::operatorOp(const Type &rhs);

class Mystring{
    private:
        char *str;

    public:
        Mystring();
        Mystring(const char *s);
        Mystring(const Mystring &source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char *get_str() const;
        Mystring operator-() const;                     // Member method to overload - op;
        bool operator==(const Mystring &rhs) const;   // Member method to overload == binary op;
        Mystring operator+(Mystring &rhs) const;               // Member method to overload + binary op;
};

bool Mystring::opeartor==(const Mystring &rhs) const{   // Overloading == operator
    if(std::strcmp(str, rhs.str) == 0){                 // so if (s1 == s2) is possible
        return true;                                    // when comparing data;
    }
    return false;
}

Mystring Mystring::operator+(const Mystring &rhs) const {           // Overloading + operator
    int buff_size = std::strlen(str) + std::strlen(rhs.str) + 1;
    char *buff = new char[buff_size];
    std::strcpy(buff, str);
    std::strcat(buff, rhs.str);
    Mystring temp {buff};
    delete [] buff;
    return temp;
}

Mystring Mystring::operator-(){                     // Overloading binary - operator
    char *buff = new char[std::strlen(str) + 1];
    std::strcpy(buff ,str);
    for (int i = 0; i < std::strlen(buff); i++){
        buff[i] = std::tolower(buff[i]);
    }
    Mystring temp {buff};
    delete [] buff;
    return temp;
}

// -------------------Overloading Operators as Global Functions------------------------------
// *** ReturnType operatorOp(Type &obj) ***
// *** You can only have member or global functions to overload operators, not both at the same time ***
// *** Usually declared as friend function to a class ***

class Mystring{

    friend Mystring operator-(const Mystring &obj);                     // Friend function for unary - op;
    friend bool operator==(const Mystring &lhs, const Mystring &rhs);   // Friend function for binary == op;
    friend Mystring operator+(const Mystring &lhs, const Mystring &rhs);// Friend function for binary == op;

    private:
        char *str;

    public:
        Mystring();
        Mystring(const char *s);
        Mystring(const Mystring &source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char *get_str() const;
};


bool operator==(const Mystring &lhs, const Mystring &rhs){  // Overloading == as global functions;
    return (std::strcmp(lhs.str, rhs.str) == 0);
}

Mystring operator-(const Mystring &obj){                // Make lower case overloading - assignment operator; Implemented as global functions;
    char *buff = new char[std::strlen(obj.str) + 1];
    std::strcpy(buff, obj.str);
    for(int i = 0; i < std::strlen(buff); i++){
        buff[i] = std::tolower(buff[i]);
    }
    Mystring temp {buff};

    delete [] buff;

    return temp;
}

Mystring operator+(const Mystring &lhs, const Mystring &rhs){       // Overloading + as non member functions;
    char *buff = new char[std::strlen(lhs.str) + std::strlen(rhs.str) + 1];
    std::strcpy(buff, lhs.str);
    std::strcat(buff, rhs.str);
    Mystring temp {buff};
    delete [] buff;
    return temp;
}

// -------------------Overloading the Stream Insertion and Extraction Operations------------------------------
// *** Doesnt' make sense as member methods, because object name has to come first ***
// *** Will allow: cout << larry; Which display larry.name ***
// *** Also allows: cin >> larry; Which means cin to larry.name;

class Mystring{

    friend std::ostream &operator<<(std::ostream &os, const Mystring &rhs); // friend function for << operator;
    friend std::istream &operator>>(std::istream &in, Mystring &rhs);       // friend function for >> operator;

    private:
        char *str;

    public:
        Mystring();
        Mystring(const char *s);
        Mystring(const Mystring &source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char *get_str() const;
};

std::ostream &operator<<(std::ostream &os, const Mystring &obj){    // Overloading stream insertion << operator;
    os << obj.str;          // If friend function;
    // os << obj.get_str();    If not friend function
    return os;
}

std::ostream &operator>>(std::istream &is, Mystring &obj){          // Overloading stream extraction >> operator;
    char *buff = new char[1000];
    is >> buff;
    obj = Mystring{buff};   // If you have copy or move assignment, overloaded = operator
    delete [] buff;
    return is;
}