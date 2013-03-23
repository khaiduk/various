#pragma once
#include "Statements.h"
#include "Value.h"
#include "Varibles.h"
#include "DataStruct.h"

namespace DataStruct
{
	/**
	 * Funkcja.
	 */
	class Function
	{
		string name;
		Value::Type returntype;
		vector <Varible> parameters;
		Statement* body;
		bool isExternal;
	public:
		Function(){}
		/**
		 * Tworzy obiekt funkcji.
		 * @param functionname Nazwa funkcji
		 * @param returns Typ zwracany
		 * @param external Czy funkcja jest zewnêtrzna
		 */
		Function(string functionname, Value::Type returns, bool external):name(functionname), returntype(returns), isExternal(external){}
		~Function(void)
		{
			if(body != NULL)
				delete body;
		}

		/**
		 * Dodaje parametr funkcji.
		 * @param name Nazwa parametru
		 * @param type Typ parametru
		 */
		void addParam(string name, Value::Value type)
		{
			Varible param;
			param.name = name;
			param.value = new Value::Value(type);
			parameters.push_back(param);
		}
		
		/**
		 * Dodaje cia³o funkcji.
		 * @param functionbody Cia³o funkcji
		 */
		void addBody(Statement* functionbody)
		{
			body = functionbody;
		}

		/**
		 * Wywo³uje funkcje.
		 * @param params Parametry funkcji
		 */
		virtual Value::Value Call(vector<Value::Value> params)
		{
			varMan.beginScope();
			if(params.size() != parameters.size() )
			{
				error.error("Number of parameters not matching");
				return Value::Value("0");
			}
			for(unsigned int i=0;i<parameters.size();i++)
			{
				varMan.add(parameters[i].name);
				*varMan[parameters[i].name]=params[i].cast(parameters[i].value->type);
			}
			try
			{
				body->Exec();
			}
			catch(ControlException c)
			{
				if(c.type == ControlException::RETURN)
				{
					varMan.endScope();
					if(returntype == Value::ERROR)
						return c.value;
					else
						return c.value.cast(returntype);
				}
				else
					throw;
			}
			varMan.endScope();
			return Value::Value("0");
		}

		virtual void debug()
		{
			if(isExternal) cout << "extern ";
			cout << "function "<< name << " : " << returntype << endl;
			cout << "params ["<< endl;
			for(unsigned i=0;i<parameters.size();i++)
				cout << parameters[i].name << " : " << parameters[i].value->type << endl;
			cout << "] body ["<< endl;
			body->debug();
			cout << "]" << endl;
		}

		virtual Value::Type checkTypes()
		{
			Value::Type type=returntype;
			if(type == Value::ERROR)
				type = Value::INT;
			varMan.beginScope();
			for(unsigned int i=0;i<parameters.size();i++)
			{
				varMan.add(parameters[i].name);
				varMan[parameters[i].name]->type=parameters[i].value->type;
			}
			if( ! body->checkTypes() )
				type = Value::ERROR;
			varMan.endScope();
			return type;
		}

		virtual string getName(){return name;}

		virtual Value::Type getType()
		{
			if(returntype == Value::ERROR)
				return Value::INT;
			else
				return returntype;
		}

		bool isExtern()
		{
			return isExternal;
		}
	};

	class MessageFunction : public Function
	{
	public:
		Value::Value Call(vector<Value::Value> params)
		{
			for(unsigned int i=0;i<params.size();i++)
			{
				cout << params[i];
			}
			cout << endl;
			return Value::Value("0");
		}

		void debug()
		{
			cout << "function message : INT;" << endl;
		}

		Value::Type checkTypes()
		{
			return Value::INT;
		}

		string getName(){return string("message");}

		Value::Type getType()
		{
			return Value::INT;
		}
	};

	class RandFunction : public Function
	{
	public:
		Value::Value Call(vector<Value::Value> params)
		{
			Value::Value result;
			result.type=Value::INT;
			result.val=rand();
			return result;
		}

		void debug()
		{
			cout << "function rand : INT;" << endl;
		}

		Value::Type checkTypes()
		{
			return Value::INT;
		}

		string getName(){return string("rand");}

		Value::Type getType()
		{
			return Value::INT;
		}
	};

	class DbgFunction : public Function
	{
	public:
		Value::Value Call(vector<Value::Value> params)
		{
			varMan.debug();
			return Value::Value("0");
		}

		void debug()
		{
			cout << "function dbg : INT;" << endl;
		}

		Value::Type checkTypes()
		{
			return Value::INT;
		}

		string getName(){return string("dbg");}

		Value::Type getType()
		{
			return Value::INT;
		}
	};
}

class FunctionManager
{
	
	vector <DataStruct::Function*> functions;
	DataStruct::Function* extrn;
public:
	FunctionManager():extrn(NULL)
	{
		DataStruct::Function* function;
		function = new DataStruct::RandFunction;
		functions.push_back(function);
		function = new DataStruct::MessageFunction;
		functions.push_back(function);
		function = new DataStruct::DbgFunction;
		functions.push_back(function);
	}

	/**
	 * Pozwala na dostêp do funkcji.
	 * @param name Nazwa funkcji.
	 */
	DataStruct::Function* operator[](string name)
	{
			for(unsigned int i=0;i<functions.size();i++)
			{
				if(functions[i]->getName() == name)
					return functions[i];
			}
			//function not found
			error.error("Function does not exist: "+name);
			return NULL;
	}

	/**
	 * Dodaje funkcjê.
	 * @param function Funkcja.
	 */
	void add(DataStruct::Function* function)
	{		
		if(function->isExtern() && extrn==NULL)
			extrn = function;
		for(unsigned int i=0;i<functions.size();i++)
		{
			if(functions[i]->getName() == function->getName())
			{
				error.error("Function alredy exist: "+function->getName());
				return;
			}
		}
		functions.push_back(function);
	}

	bool check()
	{
		bool isOk=true;
		for(unsigned int i=0;i<functions.size();i++)
			if(functions[i]->checkTypes() == Value::ERROR)
				isOk = false;
		return isOk;
	}

	DataStruct::Function* getExtern()
	{
		return extrn;
	}
		
	/// Wyœwietla informacjê debuguj¹ce
	void debug()
	{
		for(unsigned int i=0;i<functions.size();i++)
		{
			functions[i]->debug();
		}
	}
};

extern FunctionManager functMan;