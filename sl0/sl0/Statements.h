#pragma once
#include "StdAfx.h"
#include "Value.h"
#include "Error.h"
#include "Varibles.h"
#include "DataStruct.h"

/// Przestrzeñ nazw struktur danych.
namespace DataStruct
{
	/**
	 * Instrukcja z³o¿ona. Ci¹g instukcji zawarty w nawiasach { i }.
	 */
	class CompoundStatement : public Statement
	{
		vector <Statement*> statements;

	public:
		/**
		 * Dodaje instrukcjê.
		 * @param statement Instrukcja do dodania
		 */
		void addStatement(Statement* statement)
		{
			statements.push_back(statement);
		}

		void Exec()
		{
			varMan.beginScope();
			for(unsigned i=0;i<statements.size();i++)
				statements[i]->Exec();
			varMan.endScope();
		}

		void debug()
		{
			cout << "Statements: " << endl;
			for(unsigned i=0;i<statements.size();i++)
				statements[i]->debug();
		}

		bool checkTypes()
		{
			bool isOk=true;
			varMan.beginScope();
			for(unsigned i=0;i<statements.size();i++)
				if( ! statements[i]->checkTypes() ) isOk=false;
			varMan.endScope();
			return isOk;
		}
	};
	
	/// Instrukcja warunkowa.
	class IfStatement: public Statement
	{
		Expression* condition;
		Statement* ifTrue;
		Statement* ifFalse;
		
	public:
		/**
		 * Tworzy instrukcjê warunkow¹.
		 * @param cond Warunek
		 * @param ifT Instrukcja wykonywana w przypadku prawdziwoœci warunku
		 * @param ifF Instrukcja wykonywana w przypadku fa³szywoœci warunku
		 */
		IfStatement(Expression* cond, Statement* ifT, Statement* ifF):condition(cond), ifTrue(ifT), ifFalse(ifF){}
		
		/**
		 * Tworzy instrukcjê warunkow¹.
		 * @param cond Warunek
		 * @param ifT Instrukcja wykonywana w przypadku prawdziwoœci warunku
		 */
		IfStatement(Expression* cond, Statement* ifT):condition(cond), ifTrue(ifT), ifFalse(NULL){}

		~IfStatement()
		{
			if(condition!=NULL) delete condition;
			if(ifTrue!=NULL) delete ifTrue;
			if(ifFalse!=NULL) delete ifFalse;
		}

		void Exec()
		{
			if(condition->Eval().getBool())
			{
				varMan.beginScope();
				ifTrue->Exec();
				varMan.endScope();
			}
			else if(ifFalse!=NULL)
			{
				varMan.beginScope();
				ifFalse->Exec();
				varMan.endScope();
			}
		}

		void debug()
		{
			cout << "if [" << endl;
			condition->debug();
			cout << "] then [" << endl;
			ifTrue->debug();
			if(ifFalse!=NULL)
			{
				cout << "] else [" << endl;
				ifFalse->debug();
			}
			cout << "] " << endl;
		}
		
		bool checkTypes()
		{
			bool isOk = true;
			Value::Type condType=condition->checkTypes();
			if(condType == Value::ERROR)
				isOk = false;

			if(condType != Value::BOOL)
				error.warning("condition shall be boolean");

			varMan.beginScope();
			if(! ifTrue->checkTypes())
				isOk=false;
			varMan.endScope();
			
			varMan.beginScope();
			if( ifFalse != NULL )
				if(! ifFalse->checkTypes())
					isOk=false;
			varMan.endScope();

			return isOk;
		}
	};

	/// Instrukcja switch.
	class SwitchStatement: public Statement
	{
		Expression* condition;
		vector<Statement*> statements;
		struct Case
		{
			Value::Value value;
			unsigned int statement;
		};
		vector<Case> cases;
		unsigned int defaultcase;
		static const int UNDEFINED_CASE = -1;
		
	public:
		/**
		 * Tworzy instrukcjê switch.
		 * @param cond Warunek
		 */
		SwitchStatement(Expression* cond):condition(cond),defaultcase(UNDEFINED_CASE){}

		~SwitchStatement()
		{
			if(condition!=NULL) delete condition;
		}

		/**
		 * Dodaje instrukcjê.
		 * @param statement Instrukcja do dodania
		 */
		void addStatement(Statement* statement)
		{
			statements.push_back(statement);
		}
		
		/**
		 * Dodaje przypadek.
		 * @param value Wartoœæ
		 */
		void addCase(Value::Value value)
		{
			Case this_case;
			this_case.value = value;
			this_case.statement = statements.size();
			cases.push_back(this_case);
		}
		/**
		 * Dodaje przypadek domyœlny.
		 */
		void addDefault()
		{
			if(defaultcase == UNDEFINED_CASE) // default is undefined
			defaultcase=statements.size();
		}

		void Exec()
		{
			Value::Value value=condition->Eval();
			int exec_from=UNDEFINED_CASE;// start execution from this point
			for(unsigned int i=0;i<cases.size();i++)
				if(Value::op("==", value, cases[i].value).getBool() && exec_from==UNDEFINED_CASE)
					exec_from=cases[i].statement;
			
			if(exec_from == UNDEFINED_CASE) exec_from = defaultcase;
			if(exec_from == UNDEFINED_CASE) exec_from = statements.size();

			for(unsigned int i=exec_from;i<statements.size();i++)
			{
				try
				{
					varMan.beginScope(); // we cannot declare varibles in switch, so each statement is closed in own scope
					statements[i]->Exec();
					varMan.endScope();
				}
				catch(ControlException c)
				{
					if(c.type == ControlException::BREAK)
					{
						varMan.endScope();
						break;
					}
					else throw;
				}
			}
		}

		void debug()
		{
			cout << "switch [" << endl;
			condition->debug();
			cout << "] of [" << endl;
			unsigned int casecount=0;
			for(unsigned int i=0;i<statements.size();i++)
			{
				while(casecount<cases.size() && cases[casecount].statement == i)
					cout << "Case = " << cases[casecount++].value << " then: " << endl;
				statements[i]->debug();
			}
			cout << "] " << endl;
		}
		
		bool checkTypes()
		{
			Value::Type condType=condition->checkTypes();
			if(condType == Value::ERROR)
				 return false;

			for(unsigned int i=0;i<statements.size();i++)
			{
				varMan.beginScope();
				statements[i]->checkTypes();
				varMan.endScope();
			}

			return true;
		}
	};
	
	/// Pêtla while.
	class WhileStatement: public Statement
	{
		Expression* condition;
		Statement* loop;
	public:

		/**
		 * Tworzy pêtlê while.
		 * @param cond Warunek pêtli
		 * @param statem Instrukcja pêtli
		 */
		WhileStatement(Expression* cond, Statement* statem):condition(cond), loop(statem){}

		~WhileStatement()
		{
			if(condition!=NULL) delete condition;
			if(loop!=NULL) delete loop;
		}

		void Exec()
		{
			varMan.beginScope();
			while(condition->Eval().getBool())
			{
				try
				{
					loop->Exec();
				}
				catch(ControlException c)
				{
					if(c.type == ControlException::BREAK)
					{
						break;
					}
					else if(c.type == ControlException::CONTINUE)
					{
						continue;
					}
					else
					{
						throw;
					}
				}
			}
			varMan.endScope();
		}

		void debug()
		{
			cout << "while [" << endl;
			condition->debug();
			cout << "] preform [" << endl;
			loop->debug();
			cout << "] " << endl;
		}

		bool checkTypes()
		{
			bool isOk=true;
			Value::Type condType=condition->checkTypes();

			if(condType == Value::ERROR)
				 isOk=false;

			if(condType != Value::BOOL)
				error.warning("condition shall be boolean");

			varMan.beginScope();
			if(! loop->checkTypes()) isOk=false;
			varMan.endScope();

			return true;
		}
	};
	
	/// Pêtla do-while.
	class DoWhileStatement: public Statement
	{
		Expression* condition;
		Statement* loop;
	public:

		/**
		 * Tworzy pêtlê do-while.
		 * @param cond Warunek pêtli
		 * @param statem Instrukcja pêtli
		 */
		DoWhileStatement(Expression* cond, Statement* statem):condition(cond), loop(statem){}

		~DoWhileStatement()
		{
			if(condition!=NULL) delete condition;
			if(loop!=NULL) delete loop;
		}

		void Exec()
		{
			varMan.beginScope();
			do {
				try
				{
					loop->Exec();
				}
				catch(ControlException c)
				{
					if(c.type == ControlException::BREAK)
					{
						break;
					}
					else if(c.type == ControlException::CONTINUE)
					{
						continue;
					}
					else
					{
						throw;
					}
				}
			} while(condition->Eval().getBool());
			varMan.endScope();
		}

		void debug()
		{
			cout << "do [" << endl;
			loop->debug();
			cout << "] while [" << endl;
			condition->debug();
			cout << "] " << endl;
		}

		bool checkTypes()
		{
			bool isOk=true;
			Value::Type condType=condition->checkTypes();

			if(condType == Value::ERROR)
				 isOk=false;

			if(condType != Value::BOOL)
				error.warning("condition shall be boolean");

			varMan.beginScope();
			if(! loop->checkTypes()) isOk=false;
			varMan.endScope();

			return isOk;
		}
	};

	/// Pêtla for.
	class ForStatement: public Statement
	{
		Statement* first;
		Expression* condition;
		Expression* afterLoop;
		Statement* loop;
	public:

		/**
		 * Tworzy pêtlê for.
		 * @param init Polecenie inicjalizuj¹ce
		 * @param cond Warunek pêtli
		 * @param end Wyra¿enie koñca pêtli
		 * @param statem Instrukcja pêtli
		 * for([init],[cond],[end]) [statem];
		 */
		ForStatement(Statement* init, Expression* cond, Expression* end, Statement* statem):first(init), condition(cond), afterLoop(end), loop(statem){}

		~ForStatement()
		{
			if(first!=NULL) delete first;
			if(condition!=NULL) delete condition;
			if(afterLoop!=NULL) delete afterLoop;
			if(loop!=NULL) delete loop;
		}

		void Exec()
		{
			varMan.beginScope();
			first->Exec();
			while(condition->Eval().getBool())
			{
				try
				{
					loop->Exec();
				}
				catch(ControlException c)
				{
					if(c.type == ControlException::BREAK)
					{
						break;
					}
					else if(c.type == ControlException::CONTINUE)
					{
						afterLoop->Eval();
						continue;
					}
					else
					{
						throw;
					}
				}
				afterLoop->Eval();
			}
			varMan.endScope();
		}

		void debug()
		{
			cout << "for [" << endl;
			first->debug();
			cout << "-------" << endl;
			condition->debug();
			cout << "-------" << endl;
			afterLoop->debug();
			cout << "] preform [" << endl;
			loop->debug();
			cout << "] " << endl;
		}

		bool checkTypes()
		{
			bool isOk=true;

			varMan.beginScope();

			if( ! first->checkTypes() )
				isOk=false;
			Value::Type condType=condition->checkTypes();

			if(condType == Value::ERROR)
				 isOk=false;

			if(condType != Value::BOOL)
				error.warning("condition shall be boolean");

			Value::Type endType=afterLoop->checkTypes();

			if(endType == Value::ERROR)
				 isOk=false;

			if(! loop->checkTypes()) isOk=false;

			varMan.endScope();

			return isOk;
		}
	};
	
	/// Instrukcja przerwania pêtli
	class BreakStatement: public Statement
	{
	public:
		void Exec()
		{
			throw ControlException(ControlException::BREAK);
		}

		void debug()
		{
			cout << "break" << endl;
		}

		bool checkTypes()
		{
			return true; 
		}
	};

	/// Instrukcja kontynuacji pêtli
	class ContinueStatement: public Statement
	{
	public:
		void Exec()
		{
			throw ControlException(ControlException::CONTINUE);
		}

		void debug()
		{
			cout << "continue" << endl;
		}

		bool checkTypes()
		{
			return true; 
		}
	};
	
	/// Instrukcja powrotu z funkcji
	class ReturnStatement: public Statement
	{
		Expression* expression;
	public:
		ReturnStatement():expression(NULL){}
		ReturnStatement(Expression* expr):expression(expr){}
		void Exec()
		{
			if(expression==NULL)
				throw ControlException(ControlException::RETURN);
			else
			{
				Value::Value value = expression->Eval();
				throw ControlException(ControlException::RETURN,value);
			}
		}

		void debug()
		{
			if(expression==NULL)
				cout << "return" << endl;
			else
			{
				cout << "return ["<<endl;
				expression->debug();
				cout << "]"<<endl;
			}
		}

		bool checkTypes()
		{
			return true; 
		}
	};

	/// Deklaracja zmiennej.
	class Declaration
	{
		string name;
		Expression* value;
		Value::Type type;
		
	public:
		/**
		 * Tworzy deklaracjê pojedynczej zmiennej.
		 * @param varName Nazwa zmiennej
		 * @param varType Typ zmiennej
		 * @param varValue Wyra¿enie opisuj¹ce wartoœæ zmiennej
		 */
		Declaration(string varName, Value::Type varType, Expression* varValue):name(varName),type(varType),value(varValue){}
		
		/**
		 * Tworzy deklaracjê pojedynczej zmiennej. Domyœlna wartoœæ ustawiona na 0.
		 * @param varName Nazwa zmiennej
		 * @param varType Typ zmiennej
		 */
		Declaration(string varName, Value::Type varType):name(varName),type(varType),value(NULL){}

		~Declaration()
		{
			if(value!=NULL) delete value;
		}
		
		/// Deklaruje zmienn¹.
		void Declare()
		{
			
			varMan.add(name);

			if(value==NULL)
				*varMan[name] = Value::Value(type);
			else
				*varMan[name] = value->Eval().cast(type);
		}
		/**
		 * Deklaruje zmienn¹.
		 * @param man Menad¿er zmiennych;
		 */
		void Declare(VaribleManager man)
		{
			
			man.add(name);

			if(value==NULL)
				*man[name] = Value::Value(type);
			else
				*man[name] = value->Eval().cast(type);
		}

		/// Wyœwietla informacjê debuguj¹ce.
		void debug()
		{
			cout << "varible ["<< name << "]" << endl;
				if(value!=NULL)
				{
					cout << "value [" << endl;
					value->debug();
					cout << "]"<< endl;
				}
		}

		bool checkTypes()
		{
			if(value==NULL)
			{
				Declare();
				return true;
			}
			else
			{
				Value::Type valType = value->checkTypes();
				if(valType == Value::ERROR)
					 return false;
				if(valType != type)
					error.warning("expression not matching value type");
				Declare();
				return true;
			}
		}
	};
	
	/**
	 * Instrukcja deklaracji zmiennych.
	 * Pozwala na zdeklarowanie nawet kilku zmiennych w jednej instrukcji.
	 */
	class DeclarationStatement: public Statement
	{
		vector <Declaration*> declarations;
		
	public:
		/**
		 * Dodaje deklaracjê pojedynczej zmiennej.
		 * @param name Nazwa zmiennej
		 * @param type Typ zmiennej
		 * @param value Wyra¿enie opisuj¹ce wartoœæ
		 */
		void addDeclaration(string name, Value::Type type, Expression* value)
		{
			Declaration* decl=new Declaration(name, type, value);
			declarations.push_back(decl);
		}

		/**
		 * Dodaje deklaracjê pojedynczej zmiennej.
		 * @param name Nazwa zmiennej
		 * @param type Typ zmiennej
		 */
		void addDeclaration(string name, Value::Type type)
		{

			Declaration* decl=new Declaration(name, type);
			declarations.push_back(decl);
		}

		void Exec()
		{
			for(unsigned i=0;i<declarations.size();i++)
				declarations[i]->Declare();
		}

		void debug()
		{
			for(unsigned i=0;i<declarations.size();i++)
				declarations[i]->debug();
		}

		bool checkTypes()
		{
			for(unsigned i=0;i<declarations.size();i++)
				if( ! declarations[i]->checkTypes() ) return false;
			return true; 
		}
	};

	/// Instrukcja pusta
	class NullStatement: public Statement
	{
		void Exec()
		{
			;//do nothing
		}

		void debug()
		{
			cout << "Do nothing" << endl;
		}

		bool checkTypes()
		{
			return true; 
		}
	};

	/// Instrukcja wyra¿eniowa.
	class ExpressionStatement: public Statement
	{
		Expression* expression;

	public:
		/**
		 * Tworzy instrukcjê wyra¿eniow¹.
		 * @param expr Wyra¿enie w instrukcji
		 */
		ExpressionStatement(Expression* expr):expression(expr){}

		~ExpressionStatement()
		{
			if(expression!=NULL) delete expression;
		}

		void Exec()
		{
			expression->Eval();
		}

		void debug()
		{
			cout << "expression [" << endl;
			expression->debug();
			cout << "]" << endl;
		}

		bool checkTypes()
		{
			Value::Type type = expression->checkTypes();
			if(type==Value::ERROR)
				return false;
			return true;
		}
	};
}

	