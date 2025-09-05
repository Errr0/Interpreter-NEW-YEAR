#include <iostream>

enum class TokenType{
    Null,
    Function,
    Int,
};

enum class ReturnType {
    Void,
    Int
};

struct Token{
    TokenType type;
    void* value;
    Token(TokenType type = TokenType::Null, void* value = nullptr){
        this->type = type;
        this->value = value;
    }
    // ~Token(){

    // }
};

struct FunctionObject {
    using void_func = void(*)();
    using int_func  = int(*)();
    void* return_value;
    ReturnType type;
    void* func;

    FunctionObject(void_func f) {
        type = ReturnType::Void;
        func = (void*)f;
    }

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

// // --- przykładowe funkcje ---
// void helloFunction() {
//     std::cout << "Hello from void function!" << std::endl;
// }

// int numberFunction() {
//     std::cout << "Hello from int function!" << std::endl;
//     return 42;
// }

// int main() {
//     FunctionObject f1(helloFunction);
//     FunctionObject f2(numberFunction);

//     f1.call();
//     f2.call();

//     return 0;
// }