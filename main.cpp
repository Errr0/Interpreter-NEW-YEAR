#include <iostream>
#include "token.cpp"

using void_func = void(*)();
using int_func  = int(*)();

struct FunctionObject {
    using void_func = void(*)();
    using int_func  = int(*)();
    void* return_value;
    ReturnType type;
    void* func;

    // Konstruktor dla void()
    FunctionObject(void_func f) {
        type = ReturnType::Void;
        func = (void*)f;
    }

    // Konstruktor dla int()
    FunctionObject(int_func f) {
        type = ReturnType::Int;
        func = (void*)f;
    }

    void call() {
        switch (type) {
            case ReturnType::Void:
                ((void_func)func)();
                break;

            case ReturnType::Int: {
                int result = ((int_func)func)();
                return_value = (void*)&result;
                std::cout << "Returned int: " << result << std::endl;
                std::cout << "Returned int: " << *((int*)return_value) << std::endl;
                break;
            }
        }
    }
};

// --- przykładowe funkcje ---
void helloFunction() {
    std::cout << "Hello from void function!" << std::endl;
}

int numberFunction() {
    std::cout << "Hello from int function!" << std::endl;
    return 42;
}

int main() {
    FunctionObject f1(helloFunction);
    FunctionObject f2(numberFunction);

    f1.call();
    f2.call();

    return 0;
}





// struct FunctionObject {
//     //type
//     FunctionObject(){

//     }
//     void sayHello() {
//         std::cout << "Hello from object!" << std::endl;
//     }
// };

// int main() {
//     FunctionObject obj;

//     Token token = Token(TokenType::Function, (void*)&obj);

//     // rzutowanie z powrotem
//     ((FunctionObject*)token.value)->sayHello();

//     return 0;
// }

// using void_func = void (*)();
// using int_func = int (*)();

// void helloFunction() {
//     std::cout << "Hello from function!" << std::endl;
// }

// int main(){
//     Token token = Token(TokenType::Function, (void*)&helloFunction);
//     ((void_func)token.value)();
//     return 0;
// }