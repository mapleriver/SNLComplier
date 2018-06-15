#pragma once
#include"Scanner.h"

#include<list>
#include<string>
#include<map>
#include<Token.h>

struct ParseTreeNode;
using Terminal = Tag;
enum class Nonterminal;

class Parser
{
private:
	Scanner& scanner;
public:
	ParseTreeNode * getParseTree();
	void printParseTree(ParseTreeNode * parseTree);
	Parser(Scanner& scan);
	~Parser();

private:
	Token curToken;
	void readNextToken();
	void match(Terminal expectedTer);
	void syntaxError(const char* errMessage);

	ParseTreeNode * program();
		ParseTreeNode * programHead();


		ParseTreeNode * declarePart();

			ParseTreeNode * typeDec();
				ParseTreeNode * typeDeclaration();
					ParseTreeNode * typeDecList();
						void typeId(ParseTreeNode * typeDecNode);
						void typeName(ParseTreeNode * typeDecNode);
							void baseType(ParseTreeNode * typeDecNode);
							void structureType(ParseTreeNode * typeDecNode);
								void arrayType(ParseTreeNode * typeDecNode);
								void recType(ParseTreeNode * typeDecNode);
									ParseTreeNode * fieldDecList();
										ParseTreeNode * fieldDecMore();
										void idList(ParseTreeNode * typeDecNode);
											void idMore(ParseTreeNode * typeDecNode);
						ParseTreeNode * typeDecMore();

			ParseTreeNode * varDec();
				ParseTreeNode * varDeclaration();
					ParseTreeNode *varDecList();
						ParseTreeNode * varDecMore(); 
						void varIdList(ParseTreeNode * varDecNode);
							void varIdMore(ParseTreeNode * varDecNode);

			ParseTreeNode * procDec();
				ParseTreeNode * procDeclaration();
					void paramList(ParseTreeNode * procDecNode);
						ParseTreeNode * paramDecList();
							ParseTreeNode * paramMore();
							ParseTreeNode * param();
								void formList(ParseTreeNode * paramDecNode);
									void fidMore(ParseTreeNode * paramDecNode);
						
					ParseTreeNode * procDecPart();

					ParseTreeNode * procBody();
				

		ParseTreeNode * programBody();
			ParseTreeNode * stmList();
				ParseTreeNode * stmMore();
				ParseTreeNode * stm();
					ParseTreeNode * assCall();
						ParseTreeNode * callStmRest();
							ParseTreeNode * actParamList();
								ParseTreeNode * actParamMore();
					ParseTreeNode * assignmentRest();
					ParseTreeNode * conditionalStm();
					ParseTreeNode * loopStm();
					ParseTreeNode * inputStm();
					ParseTreeNode * outputStm();
					ParseTreeNode * returnStm();

					ParseTreeNode * exp();
						ParseTreeNode * simpleExp();
							ParseTreeNode * term();
								ParseTreeNode * factor();
									ParseTreeNode * variable();
										void variMore(ParseTreeNode * varNode);
											ParseTreeNode * fieldvar();
												void fieldvarMore(ParseTreeNode * varNode);
						

};

enum class Nonterminal {
	Program, ProgramHead, ProgramName, DeclarePart,
	TypeDec, TypeDeclaration, TypeDecList, TypeDecMore,
	TypeId, TypeName, BaseType, StructureType,
	ArrayType, Low, Top, RecType,
	FieldDecList, FieldDecMore, IdList, IdMore,
	VarDec, VarDeclaration, VarDecList, VarDecMore,
	VarIdList, VarIdMore, ProcDec, ProcDeclaration,
	ProcDecMore, ProcName, ParamList, ParamDecList,
	ParamMore, Param, FormList, FidMore,
	ProcDecPart, ProcBody, ProgramBody, StmList,
	StmMore, Stm, AssCall, AssignmentRest,
	ConditionalStm, StmL, LoopStm, InputStm,
	InVar, OutputStm, ReturnStm, CallStmRest,
	ActParamList, ActParamMore, RelExp, OtherRelE,
	Exp, OtherTerm, Term, OtherFactor,
	Factor, Variable, VariMore, FieldVar,
	FieldVarMore, CmpOp, AddOp, MultOp
};

enum class ParseNodeType {
	PROG, PHEAD, DECPART, TYPEDEC, VARDEC, PROCDEC, STMLIST, STMT, EXP
};

enum class DecType {
	ARRAY, CHAR, INTEGER, RECORD, ID
};

enum class StmtType {
	IF, WHILE, ASSIGN, READ, WRITE, CALL, RETURN
};

enum class ExpType {
	OP, CONST, VAR
};

enum class VariableType {
	ID, ARRAYMEMB, FIELDMEMB
};

enum class CheckType {
	VOID, INTEGER, BOOLEAN
};

enum class ParamType {
	VALPARAM, VARPARAM
};

#define MAXCHILDRENNUM 3

struct IdAttr;
using SymbolTable = std::map<std::string, IdAttr>;

struct ParseTreeNode
{
public:
	ParseTreeNode(){
		for (int i = 0; i < MAXCHILDRENNUM; ++i) {
			this->children[i] = nullptr;
		}
		this->sibling = nullptr;
		idNum = 0;
	}

	ParseTreeNode(ParseNodeType nodeType):
		ParseTreeNode()
	{
		this->nodeType = nodeType;
	}

	ParseTreeNode(ParseNodeType nodeType, DecType decType) :
		ParseTreeNode(nodeType)
	{
		this->specificType.dec = decType;
	}

	ParseTreeNode(ParseNodeType nodeType, StmtType stmtType):
		ParseTreeNode(nodeType)
	{
		this->specificType.stmt = stmtType;
	}

	ParseTreeNode(ParseNodeType nodeType, ExpType expType) :
		ParseTreeNode(nodeType)
	{
		this->specificType.exp = expType;

		this->attr.exp.varType = VariableType::ID;
		this->attr.exp.checkType = CheckType::VOID;
	}

	~ParseTreeNode() {
		for (int i = 0; i < MAXCHILDRENNUM; ++i) {
			delete this->children[i];
		}
		delete this->sibling;
	}
public:
	ParseTreeNode* children[MAXCHILDRENNUM];
	ParseTreeNode* sibling;
	//int lineNo;

	ParseNodeType nodeType;
	union SpecificType {
		DecType dec;
		StmtType stmt;
		ExpType exp;
	} specificType;

	int idNum;
	std::string name[10];
	SymbolTable symbolTable;
	union Attr{
		Attr() {};
		~Attr() {};
		struct{
			unsigned int lowerBound;
			unsigned int upperBound;
			DecType type;
		}array;

		struct {
			ParamType paramType;
		}process;

		struct{
			Tag op;
			int value;
			VariableType varType;
			CheckType checkType;
		}exp;

		std::string typeName;
	}attr;
};

/******************************************************
**********语义分析需要用到的类型及变量定义************
******************************************************/
/*标识符的类型*/
enum class IdKind {TYPE, VAR, PROC};
/*变量的类别。dir表直接变量(值参)，indir表示间接变量(变参)*/
enum class AccessKind {DIR, INDIR };

/*形参表的结构定义*/
struct  ParamTable
{
	SymbolTable   *  entry;/*指向该形参所在符号表中的地址入口*/
	ParamTable  *  next;
};

/*标识符的属性结构定义*/
struct IdAttr {
	struct typeIR  * idtype;		/*指向标识符的类型内部表示*/
	IdKind    kind;					/*标识符的类型*/
	union
	{
		struct
		{
			AccessKind   access;   /*判断是变参还是值参*/
			int          level;
			int          off;
			bool         isParam;  /*判断是参数还是普通变量*/

		}VarAttr;/*变量标识符的属性*/
		struct
		{
			int         level;     /*该过程的层数*/

			ParamTable  * param;   /*参数表*/

			int         mOff;	   /*过程活动记录的大小*/

			int         nOff;  	   /*sp到display表的偏移量*/

			int         procEntry; /*过程的入口地址*/

			int         codeEntry;/*过程入口标号,用于中间代码生成*/

		}ProcAttr;/*过程名标识符的属性*/

	}specific;/*标识符的不同类型有不同的属性*/
};

enum class TypeKind{ intTy, charTy, arrayTy, recordTy, boolTy };
struct FieldChain
{
	std::string  id;             /*变量名*/
	int    off;                 /*所在记录中的偏移*/
	typeIR  *  UnitType; /*域中成员的类型*/
	FieldChain  * Next;
};

struct  typeIR
{
	int				size;   /*类型所占空间大小*/
	TypeKind		kind;
	union
	{
		struct
		{
			struct typeIR	* indexTy;
			struct typeIR	* elemTy;
			int    low;     /*记录数组类型的下界*/
			int    up;      /*记录数组类型的上界*/
		}ArrayAttr;
		FieldChain * body;  /*记录类型中的域链*/
	} More;
};