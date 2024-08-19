#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name

// -------------------Generic Programming with Macros------------------------------
// *** C++ preprocessor directives: no type information ***

#define MAX_SIZE 100            // Use const instead
#define PI 3.14569

if(num > MAX_SIZE){             // MAX_SIZE is used here
    std::cout << "Too Big"
}

double area = PI * r * r;

#define MAX(a, b) ((a > b) ? a : b)

std::cout << MAX(10, 20) << std::endl;      // 20;
    // Potential problems;
#define SQUARE(a) a * a         // Problem

result = 100 / SQUARE(5);       // Expect 4, but will get 100 : 100 / 5 * 5 Blind substituion;

#define SQUARE(a) ((a) * (a))       // Use parenthesis


// -------------------Generic Programming with Function Templates------------------------------
// *** Blueprint, allow plug-in any data type, compiler generates the appropriate function/class from blueprint ***

template <typename T>       // OR template <class T>
T max(T a, T b){
    return (a > b) ? a : b; // Whatever type we used must support > operator
}

std::cout << max<int>(a, b);    // Compiler will generate int type of function

std::cout << max<double>(a, b);

Player p1{"Hero", 10, 20};
Player p2 {"Enemy", 99, 3};

std::cout <<max<Player>(p1, p2);        // If Player class doesn't have overloaded > operator
                                        // then it will not compile;

template <typename T1, typename T2>     // OR template <class T>
void func(T1 a, T2 b){
    std::cout << a << " " << b;         // Whatever type we used must support > operator
}

func<int, double>(10, 20.2);
func('A', 12.4);                        // Compiler will deduce the type from function arguments

    // Example
template <typename T>       // OR template <class T>
T max(T a, T b){
    return (a > b) ? a : b; // Whatever type we used must support > operator
}

struct Person {                         // Example with struct that has overloaded < operator;
    std::string name;
    int age;
    bool operator<(const Person &rhs){
        return this->age < rhs.age;
    }
}

Person p1{"Curly", 15};
Person p2{"Moe", 30};
Person p3 = min(p1, p2);
std::cout << p3.name << " is younger " << std::endl;

// -------------------Generic Programming with Class Templates------------------------------
// *** Similar to function template, but at the class level, allow plug-in any data type ***

template <typename T>
    class Item {
        private:
            std::string name;
            T value;                    // T can be anything, int, double, float and so on
        
        public:
            Item(std::string name, T value) : name{name}, value{value} {};
            std::string get_name() const {return name;}
            T get_value() const {return value;}
    }

Item<int> item1 {"Larry", 1};           // In this case T is int
Item<double> item2 {"House", 2.3};      // In this case T is double
std::vector<Item<int>> vec;

// -------------------Creating Generic Array Template Class------------------------------

template <typename T, int N>
class Array {
    int size {N};           // how do we get the N???
    T values[N];        // the N needs to ne known at compile-time!

    friend std::ostream &operator<<(std::ostream &os, const Array<T, N> &arr) {
        os << "[ ";
        for (const auto &val: arr.values)
            os << val << " ";
        os << "]" << std::endl;
        return os;
    }
    public:
        Array() = default;
        Array(T init_val) {
            for (auto &item: values)
                item = init_val;
        }
        void fill(T val) {
            for (auto &item: values )
                item = val;
        }
        int get_size() const {
            return size;
        }
        // overloaded subscript operator for easy use
        T &operator[](int index) {
            return values[index];
        }
    };

// -------------------Introduction to STL Containers------------------------------
// *** Data structure that can store object of almost any type: All primitive types ***
// *** #include <container_type> ***

// -------------------Introduction to STL Iterators------------------------------
// *** Allow abstracting an arbitrary container as asequence of elements ***
// *** They are objects that work like pointers by design ***
// *** Most container classes can be traversed with iterators ***
// *** container_type::iterator_type iterator_name ***
// *** All stl container have begin and end method, return iterative object ***

std::vector<int>::iterator it1;
std::list<std::string>::iterator it2;
std::map<std::string, std::string>::iterator it3;

std::vector<int> vec {1, 2, 3};

std::vector<int>::iterator it = vec.begin();    // Iterator initialization
// or
auto it = vec.begin();

while (it != vec.end()){
    cout << *it << endl;
    ++it;
}

for(auto it = vec.begin(); it != vec.end(); it++){
    std::cout << *it;
}

// -------------------Introduction to STL Iterators------------------------------
// *** #include <algorithm> ***
// *** Different containers support different types of iterators ***
// *** All STL algorithms expect iterators as arguments ***
    // FIND
// *** find tries to locate the first occurence of an element in a container ***
// *** Returns an iterator pointing to the located element or end();

std::vector<int> vec {1, 2, 3};
auto loc = std::find(vec.begin(), vec.end(), 3);
if(loc != vec.end()){
    std::cout << *loc << std::endl;
}
    // Using custom defined class you must provide overloaded == operator
std::vector<Player> team {/* initialized*/};
Player p {"Hero", 100, 12};

auto loc = std::find(team.begin(), team.end(), p);
if(loc != vec.end()){
    std::cout << *loc << std::endl;
}

    // FOR_EACH
    // Using function
void square(int x){
    std::cout << x * x << " ";
}
std::vector<int> vec {1, 2, 3, 4};
std::for_each(vec.begin(), vec.end(), square);      // 1, 4, 9, 16

    //Using lambda expression

std::vector<int> vec {1, 2, 3, 4};

std::for_each(vec.begin(), vec.edn(),
    [](int x) {std::cout << x * x << " ";});

// -------------------Sequence Container - Array------------------------------
// *** #include <array> ***
// *** It is object size, it has its size alway associated with it ***
// *** Fixed size: must be known at compile time, use instead of raw arrays ***
// *** All iterators available and do not invalidate ***

#include <array>

std::array<int, 5> arr { {1, 2, 3, 4, 5} };

arr.size();     // 5
arr.at(0);      // 1
arr[1];         // 2
arr.front();    // 1
arr.back();     // 5
arr.fill(2);    // 2 2 2 2 2
arr.swap(arr1); // swaps 2 arrays
arr.data();     // get raw array address

// -------------------Sequence Container - Deque------------------------------
// *** Dynamic size: elements are NOT stored in contiguous memory ***
// *** Rapid insertion and deletion at the FRONT and BACK O(1) ***
// *** Insertion and removal of elements (linear time O(n)) ***
#include <deque>

std::deque<int> d1{1, 2, 3, 4, 5};
std::deque<int> d2(10, 100);        // ten 100s;

std::deque<std::string? stooges{
    std::string("Larry"),
    "Moe",
    std::string("Curly")
};

d = {2, 4, 6, 8, 10};

std::deque<int> d{1, 2, 3};
d.front();          // first element;
d.back();           // last element;
d.push_back(10);    // O(1) 1 2 3 10
d.push_front(10);   // O(1) 10 1 2 3 10
d.size();           // 5
d.at(1);            // 1
d[0];               // 10

// -------------------Sequence Container - Sets------------------------------
// *** Collection of stored objects that allow fast retrieval using a key, No concept of front or back ***
// *** Usually implemented as a balanced binary tree or hashsets ***
// *** No Duplicates are allowed ***
// *** Sets are sorted ***
// *** set.insert(n) returns pair {iterator to the inserted element or existing, bool operation success }
#include <set>
std::set;
std::unordered_set;
std::multiset;
std::unordered_multiset

std::set<int> s {1, 2, 3, 4, 5};

std::set<int> s {4, 1, 1, 3, 3, 2, 5};      // 1 2 3 4 5
s.insert(7);            // 1 2 3 4 5 7

s.erase(3);             // 1 2 4 5 7

auto it = s.find(5);
if(it != s.end()){
    s.erase(it);        // erase the 5: 1 2 4 7
}

s.count(1);             // true if found, false if not found

// -------------------Sequence Container - Map------------------------------
// *** Collection of stored objects that allow fast retrieval using a key ***
// *** Ususally implemented as balanced binary tree or hashsets ***
// *** Key : Value pairs, ordered by key, no duplicate keys are allowed ***
#include <map>

std::map;
std::unordered_map;
std::multimap;
std::unordered_multimap;

std::map<std::string, int> m1{
    {"Larry", 18},
    {"Moe", 25}
}

std::map<std::string, std::string> m2 {
    {"Bob", "Butcher"},
    {"Anne", "Baker"},
    {"George", "Candlestick maker"}
}

m2.size();          // 3

std::pair<std::string, std::string> p1 {"James", "Mechanic"};
m2.insert(p1);

m2.insert(std::make_pair("Roger", "Ranger"));

m2["Frank"] = "Teacher";        // insert
m2["Frank"] = "Instructor";     // update value
m.at("Frank") = "Professor";    // update value

m.erase("Anne");                // erase Anne

auto it = m2.find("George");    // returns iterator

m2.count("Bob");                // returns 1 if found, 0 if not found

// -------------------Sequence Container - Priority Queue------------------------------
// *** Allows insertions and removal of elements in order from the front of the container ***
// *** Elements are stored internally as vector by default ***
// *** Elements are isnerted in priority order (largest value will always be at the front) ***
// *** No iteratrs are supported ***

#include <queue>

// push - insert an element into sorted order;
// pop - removed the top element (greates);
// top - access the top element (greates);

std::priority_queue<int> pq;

pq.push(10);
pq.push(20);

pq.top();           // 20
pq.pop();           // will pop 20