#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/********************** 单词的词法类型 ********************/
enum class Tag
{
    /* 簿记单词符号 */
    ENDFILE = 256,	ERROR,
    /* 保留字 */
    PROGRAM,	PROCEDURE,	TYPE,	VAR,		IF,
    THEN,		ELSE,		FI,		WHILE,		DO,
    ENDWH,		BEGIN,		END,	READ,		WRITE,
    ARRAY,		OF,			RECORD,	RETURN,

    INTEGER,	CHAR,
    /* 多字符单词符号 */
    ID,			INTC,		CHARC,
    /*特殊符号 */
    ASSIGN,		EQ,			LT,		PLUS,		MINUS,
    TIMES,		OVER,		LPAREN,	RPAREN,		DOT,
    COLON,		SEMI,		COMMA,	LMIDPAREN,	RMIDPAREN,
    UNDERANGE
};

class Token
{
public:
    Token();
    Tag tag;
    std::string lexeme;
    size_t line;
    std::string toString();

private:
    std::string getTagString();
};

#endif // TOKEN_H
