enum class TokenType{
    Null,
    Function,
    Variable
};

class Token{
    public:
    TokenType type;
    void* value;
    Token(TokenType type = TokenType::Null, void* value = nullptr, bool copyPtrValue = true){
        this->type = type;
        this->value = value;
    }
    ~Token(){

    }
};