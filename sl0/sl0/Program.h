#pragma once
#include "Functions.h"

namespace DataStruct
{
	/// Program
	class Program
	{
		vector <Function*> functions;

	public:
		/**
		 * Dodaje funkcjê.
		 * @param function Funkcja do dodania
		 */
		void addFunction(Function* function)
		{
			functions.push_back(function);
		}


		void Exec()
		{
			for(unsigned i=0;i<functions.size();i++)
				functMan.add(functions[i]);
			varMan.beginScope();
			Function* main = functMan.getExtern();
			if(main == NULL)
			{
				error.error("Extern function not found");
				return;
			}
			Value::Type typeSuccess = main->checkTypes();
			if(typeSuccess == Value::ERROR  || !error.isOk())
				error.error("Errors found");
			else
			{
				vector<Value::Value> params;
				try{
				main->Call(params);
				}
				catch(const char* w)
				{
					cout << w << endl;
					return;
				}
			}
			varMan.endScope();
		}

		void debug()
		{
			for(unsigned int i=0;i<functions.size();i++)
				functions[i]->debug();
		}
	};
}