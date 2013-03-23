#pragma once
#include "StdAfx.h"
#include "Value.h"
#include "Error.h"
#include "DataStruct.h"
#include "Varibles.h"
#include "Functions.h"

/// Przestrzeñ nazw struktur danych.
namespace DataStruct
{
	/// Wyra¿enie prszypisania.
	class AssignmentExpression: public Expression
	{
		Expression* left;
		Expression* right;
		string operatorName;
		
	public:
		/**
		 * Tworzy wyra¿enie przypisania.
		 * @param l Lewa strona przypisania. Musi byæ l-wartoœci¹, czyli zwracaæ nam nazwê zmiennej do której bêdziemy przypisywali.
		 * @param r Prawa strona przypisania. Z niej obliczamy wartoœæ zmiennej.
		 * @param opName Nazwa operatora. (np. =, +=, itd.)
		 */
		AssignmentExpression(Expression* l, Expression* r, string opName):	left(l),
								right(r),
								operatorName(opName){}

		~AssignmentExpression()
		{
			if(left!=NULL) delete left;
			if(right!=NULL) delete right;
		}
		
		Value::Value Eval()
		{
			left->Eval();
			Value::Value* lval=left->Lvalue();
			Value::Value value;
			
			if( lval == NULL )
			{
				error.error("must be l-value");
				value = right->Eval();
			}
			else
			{
				Value::Type type = lval->type;
				if(operatorName=="=")			value =  right->Eval().cast(type);
				else
				{
					string assignOp = operatorName.substr(0,operatorName.length()-1); // += -> +
					value = Value::op(assignOp,*lval, right->Eval() ).cast(type);
				}
				lval->val = value.val;
			}
			return value;
		}

		Value::Value* Lvalue()
		{
			return left->Lvalue();
		}

		void debug()
		{
			cout << "[" << endl;
			left->debug();
			right->debug();
			cout << "assignment "<< operatorName <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			left->checkTypes();
			Value::Value* lval=left->Lvalue();
			Value::Type type;
			
			if( lval == NULL )
			{
				error.error("must be l-value");
				type = right->checkTypes();
			}
			else
			{
				type = lval->type;
				if(operatorName=="=")			type =  right->checkTypes();
				else
				{
					string assignOp = operatorName.substr(0,operatorName.length()-1); // += -> +
					type = Value::checkTypes(assignOp,lval->type, right->checkTypes() );
				}
				type = lval->type;
			}
			return type;
		}
	};

	/**
	 * Wyra¿enie arytmetyczne. Mo¿e siê rekurencyjnie zawieraæ, by reprezentowaæ 
	 * bardziej skomplikowane wyra¿enia (np. 2+2*2, 2+3-1, 5>=2+1)
	 */
	class ArithmeticExpression: public Expression
	{
		Expression* left;
		Expression* right;
		string operatorName;
		
	public:
		/**
		 * Tworzy wyra¿enie arytmetyczne.
		 * @param l Lewa strona wyra¿enia.
		 * @param r Prawa strona wyra¿enia.
		 * @param opName Nazwa operatora (np. +, *, ||, >=)
		 */
		ArithmeticExpression(Expression* l, Expression* r, string opName):	left(l),
								right(r),
								operatorName(opName){}

		~ArithmeticExpression()
		{
			if(left!=NULL) delete left;
			if(right!=NULL) delete right;
		}

		Value::Value Eval()
		{
			return Value::op(operatorName, left->Eval(), right->Eval() ) ;
		}

		Value::Value* Lvalue()
		{
			return NULL;//Arithmetic Expression cannot be l-value
		}

		void debug()
		{
			cout << "[" << endl;
			left->debug();
			right->debug();
			cout << "operator "<< operatorName <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			return Value::checkTypes(operatorName, left->checkTypes(), right->checkTypes() ) ;
		}
	};

	/// Konwersja typów.
	class CastExpression: public Expression
	{
		Expression* expression;
		string type;

	public:
		/**
		 * Tworzy wyra¿enie konwersji typów.
		 * @param expr Podwyra¿enie
		 * @param typeName Nazwa typu
		 */
		CastExpression(Expression* expr, string typeName):	expression(expr),
							type(typeName){}
		~CastExpression()
		{
			if(expression!=NULL) delete expression;
		}

		Value::Value Eval()
		{
			Value::Value val=expression->Eval();

			val.cast(Value::StrToType(type));

			return val;

		}

		Value::Value* Lvalue()
		{
			return NULL;
		}

		void debug()
		{
			cout << "[" << endl;
			expression->debug();
			cout << "cast to "<< type <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			Value::Type valType=expression->checkTypes();

			if(valType == Value::ERROR)
				return valType;

			valType=Value::StrToType(type);

			return valType;
		}
	};
	
	/// Wyra¿enie unarne.
	class UnaryExpression: public Expression
	{
		Expression* expression;
		string operatorName;

	public:
		/**
		 * Tworzy wyra¿enie unarne
		 * @param expr Podwyra¿enie
		 * @param opName Nazwa operatora (np. !, -, ++)
		 */
		UnaryExpression(Expression* expr, string opName):	expression(expr),
							operatorName(opName){}

		~UnaryExpression()
		{
			if(expression!=NULL) delete expression;
		}

		Value::Value Eval()
		{
			if(operatorName=="++" || operatorName=="--")
			{
				Value::Value* lval=expression->Lvalue();
				if( lval == NULL )
				{
					error.error("Must be l-value");
					return expression->Eval();
				}
				else
				{
					if(operatorName=="++")
						lval->val = Value::op("+", *lval, Value::Value("1")).cast(lval->type).val;
					else
						lval->val = Value::op("-", *lval, Value::Value("1")).cast(lval->type).val;
				}
				return expression->Eval();
			}
			else return Value::op(operatorName, expression->Eval());
		}

		Value::Value* Lvalue()
		{
			if(operatorName=="++" || operatorName=="--")
				return expression->Lvalue();
			else
				return NULL;
		}

		void debug()
		{
			cout << "[" << endl;
			expression->debug();
			cout << "unary "<< operatorName <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			if(operatorName=="++" || operatorName=="--")
			{
				return expression->checkTypes();
			}
			else return Value::checkTypes(operatorName, expression->checkTypes());
		}
	};
	
	/// Wyra¿enie post. (np. postinkrementacja i++)
	class PostExpression: public Expression
	{
		Expression* expression;
		string operatorName;

	public:
		/**
		 * Tworzy wyra¿enie post
		 * @param expr Podwyra¿enie
		 * @param opName Nazwa operatora (np. ++)
		 */
		PostExpression(Expression* expr, string opName):	expression(expr),
							operatorName(opName){}

		~PostExpression()
		{
			if(expression!=NULL) delete expression;
		}

		Value::Value Eval()
		{
			if(operatorName=="++" || operatorName=="--")
			{
				Value::Value val=expression->Eval();
				Value::Value* lval=expression->Lvalue();
				if( lval == NULL )
				{
					error.error("Must be l-value");
					return expression->Eval();
				}
				else
				{
					if(operatorName=="++")
						lval->val = Value::op("+", *lval, Value::Value("1")).cast(lval->type).val;
					else
						lval->val = Value::op("-", *lval, Value::Value("1")).cast(lval->type).val;
				}
				return val;
			}
			else return Value::Value("0");
		}
		Value::Value* Lvalue()
		{
			if(operatorName=="++" || operatorName=="--")
				return expression->Lvalue();
			else
				return NULL;
		}

		void debug()
		{
			cout << "[" << endl;
			expression->debug();
			cout << "post "<< operatorName <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			if(operatorName=="++" || operatorName=="--")
			{
				return expression->checkTypes();
			}
			else return Value::checkTypes(operatorName, expression->checkTypes());
		}
	};

	/// Litera³ (np. 125)
	class LiteralExpression: public Expression
	{
		Value::Value value;

	public:
		/**
		 * Tworzy litera³
		 * @param val String z waroœci¹ litera³u
		 */

		LiteralExpression(string val)
		{
			value = Value::Value(val);
		}
		
		Value::Value Eval()
		{
			return value;
		}

		Value::Value* Lvalue()
		{
			return NULL;
		}

		void debug()
		{
			cout << "literal: "<< value << endl;
		}

		Value::Type checkTypes()
		{
			return value.type;
		}
	};

	/// Wyra¿enie zmiennej.
	class VarExpression: public Expression
	{
		string name;

	public:
		/**
		 * Tworzy wyra¿enie zmiennej
		 * @param varName Nazwa zmiennej
		 */
		VarExpression(string varName):	name(varName){}

		Value::Value Eval()
		{
			Value::Value* lval=varMan[name];
			if( lval == NULL )
			{
				error.error("Must be l-value");
				return Value::Value();
			}
			else
				return *lval;
		}

		Value::Value* Lvalue()
		{
			return varMan[name];
		}

		void debug()
		{
			cout << "Varible: "<< name << endl;
		}

		Value::Type checkTypes()
		{
			Value::Value* lval=varMan[name];
			if( lval == NULL )
			{
				error.error("Varible not found");
				return Value::ERROR;
			}
			else
				return lval->type;
		}
	};

	class ArrayIndexExpression: public Expression
	{
		Expression* arr;
		Expression* index;
		int indexInteger;
		
	public:
		/**
		 * Tworzy wyra¿enie dostêpu do elementu tablicy.
		 * @param l Lewa strona wyra¿enia.
		 * @param r Prawa strona wyra¿enia.
		 */
		ArrayIndexExpression(Expression* l, Expression* r):	arr(l),
								index(r),indexInteger(-1){}

		~ArrayIndexExpression()
		{
			if(arr!=NULL) delete arr;
			if(index!=NULL) delete index;
		}

		Value::Value Eval()
		{
			indexInteger =  index->Eval().getInt();
			Value::Value* lval = Lvalue();
			if( lval == NULL )
			{
				error.error("Cannot evaluate array expresion");
				return Value::Value();
			}
			else
			{
				return *lval;
			}
		}

		Value::Value* Lvalue()
		{
			if(indexInteger < 0)
				indexInteger =  index->Eval().getInt();
			Value::Value* lval = arr->Lvalue();
			if( lval == NULL )
			{
				error.error("Must be l-value");
				return NULL;
			}
			else
			{
				vector < Value::Value* > vec = boost::any_cast< vector < Value::Value* > >(lval->val);
				if(indexInteger < 0) error.error("Index of array below 0");
				while(static_cast<int>(vec.size()) <= indexInteger) //resize array
				{
					Value::Value* newElement = new Value::Value(*lval->type.arrayType);
					vec.push_back(newElement);
					lval->val = vec;
				}
				return vec[indexInteger];
			}
		}

		void debug()
		{
			cout << "[" << endl;
			arr->debug();
			cout << " index: " << endl;
			index->debug();
			cout <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			Value::Type indexType = index->checkTypes();
			if(indexType == Value::ERROR)
				return Value::ERROR;

			if(indexType != Value::INT)
				error.warning("Shall be integer");

			Value::Type arrType = arr->checkTypes();
			if(arrType != Value::ARRAY)
				error.error("Must be array");

			return *arrType.arrayType;
		}
	};

	/// Wywo³anie funkcji.
	class FunctionExpression: public Expression
	{
		string name;
		vector <Expression*> parameters;

	public:
		/**
		 * Tworzy wywo³anie funkcji.
		 * @param funcName nazwa funkcji
		 */
		FunctionExpression(string funcName):	name(funcName){}

		/**
		 * Dodaje parametr.
		 * @param param Parametr funkcji
		 */
		void addParam(Expression* param)
		{
			parameters.push_back(param);
		}

		Value::Value Eval()
		{
			if(name=="input")
			{
				for(unsigned int i=0;i<parameters.size();i++)
				{
					Value::Value* lval = parameters[i]->Lvalue();
					if( lval == NULL ) continue;
					if(lval->type == Value::CHAR)
					{
						char ch = cin.get();
						lval->val = ch;
					}
					else if(lval->type == Value::FLOAT)
					{
						string input;
						cin >> input;
						lval->val = boost::lexical_cast<float>(input);
					}
					else if(lval->type == Value::INT)
					{
						string input;
						cin >> input;
						lval->val = boost::lexical_cast<int>(input);
					}
					else if(lval->type == Value::ARRAY)
					{
						if(*lval->type.arrayType == Value::CHAR)
						{
							string input;
							getline(cin, input);
							vector <Value::Value*> arr;
							for(unsigned i=0;i<input.size();i++)
							{
								Value::Value* next = new Value::Value(Value::CHAR);
								next->val = static_cast<char>(input[i]);
								arr.push_back(next);
							}
							lval->val = arr;
						}
					}
				}
			}
			else
			{
				Function* function = functMan[name];
				if(function != NULL)
				{
					vector <Value::Value> paramval;
					for(unsigned int i=0;i<parameters.size();i++)
						paramval.push_back(parameters[i]->Eval());
					return function->Call(paramval);
				}
			}
			return Value::Value("0");
		}

		Value::Value* Lvalue()
		{
			return NULL;
		}

		void debug()
		{
			cout << "[" << endl;
			for(unsigned int i=0;i<parameters.size();i++)
			{
				cout << "parameter [" << endl;
				parameters[i]->debug();
				cout << "]" << endl;
			}
			cout << "function "<< name <<" ]" << endl;
		}

		Value::Type checkTypes()
		{
			if(name=="input")
			{
				for(unsigned int i=0;i<parameters.size();i++)
					if( parameters[i]->checkTypes() == Value::ERROR )
						return Value::ERROR;
			}
			else
			{
				Function* function = functMan[name];
				if(function != NULL)
				{
					for(unsigned int i=0;i<parameters.size();i++)
						if( parameters[i]->checkTypes() == Value::ERROR )
							return Value::ERROR;
					return function->getType();
				}
				else
					error.error("function unrecognized: " + name );
			}
			return Value::INT;
		}
	};
}

	