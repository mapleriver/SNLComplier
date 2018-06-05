#ifndef SCANNER_H
#define SCANNER_H
#include<Token.h>
#include<map>
#include<list>

class Scanner
{
private:
	enum class state {
		START, INASSIGN, INCOMMENT, INNUM, INID, INCHAR, INRANGE, DONE
	};
	std::ifstream& sourceCode;
	std::map<std::string, Tag> reservedWords;

public:
    Scanner(std::ifstream &sourceCode);
	std::list<Token> getTokenSequence();
	Token getNextToken();
	Tag getLexemeTag(std::string word);
private: 
	Token curToken;
	bool isPartOfLexeme = true;
	int lineNo = 1;
	Scanner::state nextStateFromSTART(const int c);
	Tag getTokenTagFromSingleChar(const int c);
	Scanner::state nextStateFromINCOMMENT(const int c);
	Scanner::state nextStateFromINASSIGN(const int c);
	Scanner::state nextStateFromINRANGE(const int c);
	Scanner::state nextStateFromINNUM(const int c);
	Scanner::state nextStateFromINCHAR(const int c);
	Scanner::state nextStateFromINID(const int c);
	void processCurToken(Token& curToken,std::string& curLexeme);
	void scanFailer(const Scanner::state curState);

};

#endif // SCANNER_H
