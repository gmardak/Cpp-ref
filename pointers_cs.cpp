#include <iostream>
#include <string>
#include <vector>
// Legends:
// *** definition ***- definition of how to declare
// ---Chapter Name--- - chatper name
// ### Subchapte Name ### - subchapter name

// --------------Pointers and Reference--------------------

    // *** variable_type *pointer_name {nullptr}; ***
    // *** Pointers only can contain an address to a memory in heap, nothing else ***

    int *int_ptr;                       // Contains garbage data;
    char *char_ptr = nullptr;           // Points to nowhere;
    std::string *string_ptr {nullptr};  // Points to nowwhere, a null pointer;

    int num {10};                       // num = 10;
    int size = sizeof(num);             // Size will be 8, because in my machine int takes 8 bytes;
    int *int_ptr = &num;                // int_ptr = 0x61ff1c it contains an address;

    // ### Deferencing Pointers ###

    int score = 100;                        // Regular int declaration;
    int *score_ptr = &score;                // pointer to memory where score is saved;
    int deferenced_pointer = *score_ptr;    // Deferncing pointer, getting the actual 
                                            // value of the data stored in memory
                                            // Deferenced_pointer = 100, in this case;
    *score_ptr = 200;                       // changing the actual value to 200, it will change
                                            // Score also;     

    // ### Dynamic Memory Allocation ###

    int = *in_ptr {nullptr};
    int_ptr = new int;                  // This will allocate an address in heap to store int
                                        // if we lose the pointer then it is hanging there, thus
                                        // we must deallocate the memory, or we have memory leak;
    delete int_ptr;                     // Frees the allocated storage;

    // ### Arrays and Pointers ###

    int *array_ptr {nullptr};
    int size = 0;

    array_ptr = new int[size];          // Allocate array of heap
    delete [] array_ptr;                // Free the memory allocated to array ptr;
                                        
    int scores [] = {100, 95, 89};      // Array name and pointer are the same;
    int *scores_ptr = {scores};         // You can pass array name to pointer, because array
                                        // name is actually address of the first element;
    std::cout << score_ptr[1];         // Will display actual value of the array element;
    std::cout << *(score_ptr + 1);      // Is the same as score_ptr[1];

    // ### Pointer Arithmetic ###
    int *array_ptr {nullptr};
    int size = 0;

    array_ptr = new int[size];
    array_ptr++;                    // Increments a pointer to the next array element;
    array_ptr += n;                 // Increment pointer by n * sizeof(type);

    int *array_ptr_2 = new int[size];
    array_ptr == array_ptr_2;       // Will compare address, not value, will be true if they
                                    // are pointing to the same address;

    // ### Const and Pointers ###
    // First case: pointing to constant data
    int high_score = 100;
    const int *score_ptr = {&high_score};   // The data pointed to by the pointer is constant
                                            // and cannot be changed, but address to point
                                            // can be changed;
    *score_ptr = 86;                        // ERROR;
    score_ptr = &low_score;                 // OK by compiler;
    //Second case: constant pointer only
    int *const score_ptr = &high_score;     // The data pointed to by pointer can be changed, but
                                            // pointer itseld cannot;
    *score_ptr = 86;                        // OK;
    score_ptr = &low_score;                 // ERROR;
    // Third case: constant data and pointer
    const int *const score_ptr = &high_score;   // Constant pointer and constant data

    // ### Passing Pointers to Functions ###

    void double_data(int *int_ptr){         // Pass-by-reference, the actual parameter can be 
        *int_ptr *= 2;                      // a pointer or address of a variable;
    }
    int value = 10;
    double_data( &value );                  // Calling the function by reference;

    // ### Returning a Pointer from a Function ###
    // *** type *function ();

    int *largest_int(int *int_ptr_1, int *int_ptr_2){   // The function will return an address
        if (*int_ptr_1 > *int_ptr_2){                   // of whatever type we specified in
            return int_ptr_1;                           // function definition;
        }                                               // It is deferencing pointer and comparing
        return int_ptr_2;                               // the actual data;
    }                                                   // Dont declare local function variables
                                                        // and return their address, because
                                                        // local variable will be destroyed
                                                        // once function call is ended;

    // ### What is reference ###
    vector<string> stooges {"Larry", "Moe", "Curly"};
    for (string name : stooges){                        // Will not modify the vector, because
        name = "Test";                                  // you are passing by value;
    }

    for (string &name : stooges){                       // Will modify the vector, since we 
        name = "Test";                                  // are passing by reference, we are
    }                                                   // passing actual address of the vector;