#include <iostream>
#include <vector>

// --- przykładowy Token ---
enum class TokenType { Number, Function };

struct Token {
    TokenType type;
    void* value;

    Token(TokenType t = TokenType::Number, void* v = nullptr)
        : type(t), value(v) {}
};

// --- typy zwracane ---
enum class ReturnType {
    Void,
    Token,
    TokenVector
};

// --- argumenty ---
enum class ArgType {
    None,
    Token,
    TokenVector
};

// --- aliasy funkcji ---
using void_func               = void(*)();
using token_func              = Token(*)();
using tokenvector_func        = std::vector<Token>(*)();

using void_token_func         = void(*)(Token);
using token_token_func        = Token(*)(Token);
using tokenvector_token_func  = std::vector<Token>(*)(Token);

using void_vec_func           = void(*)(std::vector<Token>);
using token_vec_func          = Token(*)(std::vector<Token>);
using tokenvector_vec_func    = std::vector<Token>(*)(std::vector<Token>);

// --- FunctionObject ---
struct FunctionObject {
    ReturnType rtype;
    ArgType atype;
    void* func;

    // konstruktory: brak argumentów
    FunctionObject(void_func f) {
        rtype = ReturnType::Void;
        atype = ArgType::None;
        func = (void*)f;
    }

    FunctionObject(token_func f) {
        rtype = ReturnType::Token;
        atype = ArgType::None;
        func = (void*)f;
    }

    FunctionObject(tokenvector_func f) {
        rtype = ReturnType::TokenVector;
        atype = ArgType::None;
        func = (void*)f;
    }

    // konstruktory: argument Token
    FunctionObject(void_token_func f) {
        rtype = ReturnType::Void;
        atype = ArgType::Token;
        func = (void*)f;
    }

    FunctionObject(token_token_func f) {
        rtype = ReturnType::Token;
        atype = ArgType::Token;
        func = (void*)f;
    }

    FunctionObject(tokenvector_token_func f) {
        rtype = ReturnType::TokenVector;
        atype = ArgType::Token;
        func = (void*)f;
    }

    // konstruktory: argument vector<Token>
    FunctionObject(void_vec_func f) {
        rtype = ReturnType::Void;
        atype = ArgType::TokenVector;
        func = (void*)f;
    }

    FunctionObject(token_vec_func f) {
        rtype = ReturnType::Token;
        atype = ArgType::TokenVector;
        func = (void*)f;
    }

    FunctionObject(tokenvector_vec_func f) {
        rtype = ReturnType::TokenVector;
        atype = ArgType::TokenVector;
        func = (void*)f;
    }

    // --- CALL(): brak argumentów ---
    void call() {
        switch (rtype) {
            case ReturnType::Void:
                if (atype == ArgType::None)
                    ((void_func)func)();
                break;

            case ReturnType::Token:
                if (atype == ArgType::None) {
                    Token result = ((token_func)func)();
                    std::cout << "Returned Token, type=" << (int)result.type << "\n";
                }
                break;

            case ReturnType::TokenVector:
                if (atype == ArgType::None) {
                    auto result = ((tokenvector_func)func)();
                    std::cout << "Returned vector<Token>, size=" << result.size() << "\n";
                }
                break;
        }
    }

    // --- CALL(): argument Token ---
    void call(Token arg) {
        switch (rtype) {
            case ReturnType::Void:
                if (atype == ArgType::Token)
                    ((void_token_func)func)(arg);
                break;

            case ReturnType::Token:
                if (atype == ArgType::Token) {
                    Token result = ((token_token_func)func)(arg);
                    std::cout << "Returned Token, type=" << (int)result.type << "\n";
                }
                break;

            case ReturnType::TokenVector:
                if (atype == ArgType::Token) {
                    auto result = ((tokenvector_token_func)func)(arg);
                    std::cout << "Returned vector<Token>, size=" << result.size() << "\n";
                }
                break;
        }
    }

    // --- CALL(): argument vector<Token> ---
    void call(std::vector<Token> args) {
        switch (rtype) {
            case ReturnType::Void:
                if (atype == ArgType::TokenVector)
                    ((void_vec_func)func)(args);
                break;

            case ReturnType::Token:
                if (atype == ArgType::TokenVector) {
                    Token result = ((token_vec_func)func)(args);
                    std::cout << "Returned Token, type=" << (int)result.type << "\n";
                }
                break;

            case ReturnType::TokenVector:
                if (atype == ArgType::TokenVector) {
                    auto result = ((tokenvector_vec_func)func)(args);
                    std::cout << "Returned vector<Token>, size=" << result.size() << "\n";
                }
                break;
        }
    }
};

// --- Funkcje testowe ---
// Bez argumentów
void f_void() {
    std::cout << "Hello void()!\n";
}

Token f_token() {
    std::cout << "Hello Token()!\n";
    return Token(TokenType::Number, nullptr);
}

std::vector<Token> f_tokenvec() {
    std::cout << "Hello vector<Token>()!\n";
    return { Token(TokenType::Number, nullptr) };
}

// Z argumentem Token
void f_void_token(Token t) {
    std::cout << "Hello void(Token)! Type=" << (int)t.type << "\n";
}

Token f_token_token(Token t) {
    std::cout << "Hello Token(Token)! Type=" << (int)t.type << "\n";
    return t;
}

std::vector<Token> f_tokenvec_token(Token t) {
    std::cout << "Hello vector<Token>(Token)! Type=" << (int)t.type << "\n";
    return { t, Token(TokenType::Function, nullptr) };
}

// Z argumentem vector<Token>
void f_void_vec(std::vector<Token> v) {
    std::cout << "Hello void(vector<Token>)! size=" << v.size() << "\n";
}

Token f_token_vec(std::vector<Token> v) {
    std::cout << "Hello Token(vector<Token>)! size=" << v.size() << "\n";
    return v.empty() ? Token(TokenType::Number, nullptr) : v[0];
}

std::vector<Token> f_tokenvec_vec(std::vector<Token> v) {
    std::cout << "Hello vector<Token>(vector<Token>)! size=" << v.size() << "\n";
    return v;
}

// --- MAIN ---
int main() {
    FunctionObject f1(f_void);
    FunctionObject f2(f_token);
    FunctionObject f3(f_tokenvec);
    FunctionObject f4(f_void_token);
    FunctionObject f5(f_token_token);
    FunctionObject f6(f_tokenvec_token);
    FunctionObject f7(f_void_vec);
    FunctionObject f8(f_token_vec);
    FunctionObject f9(f_tokenvec_vec);

    f1.call();
    f2.call();
    f3.call();

    Token tok(TokenType::Function, nullptr);
    f4.call(tok);
    f5.call(tok);
    f6.call(tok);

    std::vector<Token> args = { Token(TokenType::Function, nullptr) };
    f7.call(args);
    f8.call(args);
    f9.call(args);

    return 0;
}






// #include <iostream>
// #include "token.cpp"

// using void_func = void(*)();
// using int_func  = int(*)();

// struct FunctionObject {
//     using void_func = void(*)();
//     using int_func  = int(*)();
//     void* return_value;
//     ReturnType type;
//     void* func;

//     // Konstruktor dla void()
//     FunctionObject(void_func f) {
//         type = ReturnType::Void;
//         func = (void*)f;
//     }

//     // Konstruktor dla int()
//     FunctionObject(int_func f) {
//         type = ReturnType::Int;
//         func = (void*)f;
//     }

//     void call() {
//         switch (type) {
//             case ReturnType::Void:
//                 ((void_func)func)();
//                 break;

//             case ReturnType::Int: {
//                 int result = ((int_func)func)();
//                 return_value = (void*)&result;
//                 std::cout << "Returned int: " << result << std::endl;
//                 std::cout << "Returned int: " << *((int*)return_value) << std::endl;
//                 break;
//             }
//         }
//     }
// };

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