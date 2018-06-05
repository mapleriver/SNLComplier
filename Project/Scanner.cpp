#include "Scanner.h"
#include<fstream>
#include<iostream>
#include<locale>

Scanner::Scanner(std::ifstream &sourceCode) :
	sourceCode(sourceCode)
{
	this->reservedWords = {
		{"program",Tag::PROGRAM},{"type",Tag::TYPE},{"var",Tag::VAR},
		{"procedure",Tag::PROCEDURE},{"begin",Tag::BEGIN},{"end",Tag::END},
		{"array",Tag::ARRAY},{"of",Tag::OF},{"record",Tag::RECORD},
		{"if",Tag::IF},{"then",Tag::THEN},{"else",Tag::ELSE},{"fi",Tag::FI},
		{"while",Tag::WHILE},{"do",Tag::DO},{"endwh",Tag::ENDWH},
		{"read",Tag::READ},{"write",Tag::WRITE},{"return",Tag::RETURN},
		{"integer",Tag::INTEGER},{"char",Tag::CHAR}
	};
}

Tag Scanner::getLexemeTag(std::string word)
{
	auto it = reservedWords.find(word);
	if (it != reservedWords.end()) {
		return it->second;
	}
	else {
		return Tag::ID;
	}
}

std::list<Token> Scanner::getTokenSequence()
{
	std::list<Token> tokenSequence;

	Token curToken;
	do {
		curToken = getNextToken();
		tokenSequence.push_back(curToken);
	} while (curToken.tag != Tag::ENDFILE);

    sourceCode.seekg(std::ios::beg);

	return tokenSequence;
}

Token Scanner::getNextToken()
{
	state curState = state::START;
	int c = '\0';
	std::string curLexeme;
	while (curState != state::DONE) {
		c = sourceCode.get();
		switch (curState) {
		case state::START:
			curState = nextStateFromSTART(c);
			break;
		case state::INCOMMENT:
			curState = nextStateFromINCOMMENT(c);
			break;
		case state::INASSIGN:
			curState = nextStateFromINASSIGN(c);
			break;
		case state::INRANGE:
			curState = nextStateFromINRANGE(c);
			break;
		case state::INNUM:
			curState = nextStateFromINNUM(c);
			break;
		case state::INCHAR:
			curState = nextStateFromINCHAR(c);
			break;
		case state::INID:
			curState = nextStateFromINID(c);
			break;
		case state::DONE:
			break;
		default:
			scanFailer(curState);
			curState = state::DONE;
			break;
		}

		if (isPartOfLexeme) {
			curLexeme += static_cast<char>(c);
		}
		isPartOfLexeme = true;
	}

	processCurToken(curToken, curLexeme);
	return curToken;
}

Scanner::state Scanner::nextStateFromSTART(const int c)
{
	state curState = state::START;
	if (isdigit(c)) {
		curState = state::INNUM;
	}
	else if (isalpha(c)) {
		curState = state::INID;
	}
	else if (':' == c) {
		curState = state::INASSIGN;
	}
	else if ('.' == c) {
		curState = state::INRANGE;
	}
	else if ('\'' == c) {
		isPartOfLexeme = false;
		curState = state::INCHAR;
	}
	else if (' ' == c || '\t' == c || '\n' == c) {
		if (c == '\n') {
			++(this->lineNo);
		}
		isPartOfLexeme = false;
	}
	else if ('{' == c) {
		curState = state::INCOMMENT;
		isPartOfLexeme = false;
	}
	else {
		if (c == EOF) {
			isPartOfLexeme = false;
		}
		curToken.tag = getTokenTagFromSingleChar(c);
		curState = state::DONE;
	}
	return curState;
}

Tag Scanner::getTokenTagFromSingleChar(const int c)
{
	Tag tag;
	switch (c) {
	case EOF:
		tag = Tag::ENDFILE;
		break;
	case '=':
		tag = Tag::EQ;
		break;
	case '<':
		tag = Tag::LT;
		break;
	case '+':
		tag = Tag::PLUS;
		break;
	case '-':
		tag = Tag::MINUS;
		break;
	case '*':
		tag = Tag::TIMES;
		break;
	case '/':
		tag = Tag::OVER;
		break;
	case '(':
		tag = Tag::LPAREN;
		break;
	case ')':
		tag = Tag::RPAREN;
		break;
	case ';':
		tag = Tag::SEMI;
		break;
	case ',':
		tag = Tag::COMMA;
		break;
	case '[':
		tag = Tag::LMIDPAREN;
		break;
	case ']':
		tag = Tag::RMIDPAREN;
		break;
	default:
		tag = Tag::ERROR;
		break;
	}
	return tag;
}

Scanner::state Scanner::nextStateFromINCOMMENT(const int c)
{
	state curState = state::INCOMMENT;
	isPartOfLexeme = false;
	if (c == EOF) {
		curState = state::DONE;
		curToken.tag = Tag::ENDFILE;
	}
	else if (c == '}') {
		curState = state::START;
	}
	return curState;
}

Scanner::state Scanner::nextStateFromINASSIGN(const int c)
{
	if ('=' == c) {
		curToken.tag = Tag::ASSIGN;
	}
	else {
		this->sourceCode.unget();
		isPartOfLexeme = false;
		curToken.tag = Tag::ERROR;
	}
	return state::DONE;
}

Scanner::state Scanner::nextStateFromINRANGE(const int c)
{
	if ('.' == c) {
		curToken.tag = Tag::UNDERANGE;
	}
	else {
		sourceCode.unget();
		isPartOfLexeme = false;
		curToken.tag = Tag::DOT;
	}
	return state::DONE;
}

Scanner::state Scanner::nextStateFromINNUM(const int c)
{
	state curState = state::INNUM;
	if (!isdigit(c)) {
		sourceCode.unget();
		isPartOfLexeme = false;
		curToken.tag = Tag::INTC;
		curState = state::DONE;
	}
	return curState;
}

Scanner::state Scanner::nextStateFromINCHAR(const int c)
{
	if (isalnum(c)) {
		int sc = sourceCode.get();
		if ('\'' == sc) {
			isPartOfLexeme = true;
			curToken.tag = Tag::CHARC;
		}
		else {
			sourceCode.unget();
			sourceCode.unget();
			curToken.tag = Tag::ERROR;
		}
	}
	else {
		sourceCode.unget();
		curToken.tag = Tag::ERROR;
	}
	return  state::DONE;
}

Scanner::state Scanner::nextStateFromINID(const int c)
{
	state curState = state::INID;
	if (!isalnum(c)) {
		sourceCode.unget();
		isPartOfLexeme = false;
		curToken.tag = Tag::ID;
		curState = state::DONE;
	}
	return curState;
}

void Scanner::processCurToken(Token& curToken, std::string& curLexeme)
{
    curToken.lexeme = "";
    curToken.line = lineNo;
	if (curToken.tag == Tag::ID) {
		curToken.tag = this->getLexemeTag(curLexeme);
	}
    if(curToken.tag == Tag::ID ||
            curToken.tag == Tag::CHAR ||
            curToken.tag == Tag::INTC){
        curToken.lexeme = curLexeme;
    }
}

void Scanner::scanFailer(const Scanner::state curState)
{
	std::cerr << "Scanner parse failer: state = " << static_cast<int>(curState) << std::endl;;
	curToken.tag = Tag::ERROR;
}

