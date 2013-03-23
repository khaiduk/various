#pragma once

#include "StdAfx.h"
#include "Value.h"
#include "Error.h"

struct Varible
{
	string name;
	Value::Value* value;
};

/**
 * Klasa menad¿era zmiennych.
 * Pozwala na przechowywanie zmiennych, kontoluj¹c ich zasiêg.
 */
class VaribleManager
{
	vector <Varible> vars;
	vector <unsigned int> scope;
	Value::Value err;
public:

	/**
	 * Pozwala na dostêp do zmiennej.
	 * @param name Nazwa zmiennej.
	 * @return WskaŸnik na wartoœæ zmiennej.
	 */
	/*Value::Value& operator[](string name)
	{
		if(name == "")
		{
			error.error("Must be l-value");
			return err;
		}
		else
		{
			for(int i=vars.size()-1;i>=0;i--)
			{
				if(vars[i].name == name)
					return *vars[i].value;
			}
			//var not found
			error.error("Varible does not exist: "+name);
			return err;
		}
	}//*/
	Value::Value* operator[](string name)
	{
		for(int i=vars.size()-1;i>=0;i--)
		{
			if(vars[i].name == name)
				return vars[i].value;
		}
		//var not found
		error.error("Varible does not exist: "+name);
		return NULL;
	}

	/**
	 * Sprawdza czy nazwa zmiennej jest poprawna i zmienna istnieje.
	 * @param name Nazwa zmiennej.
	 * @return Poprawnoœæ zmiennej.
	 */
	bool check(string name)
	{
		if(name == "")
		{
			error.error("Must be l-value");
			return false;
		}
		else
		{
			for(int i=static_cast<int>(vars.size())-1;i>=0;i--)
			{
				if(vars[i].name == name)
					return true;
			}
			error.error("Varible not found: "+name);
			return false;//var not found
		}
	}

	/**
	 * Dodaje zmienn¹.
	 * @param name Nazwa zmiennej.
	 */
	void add(string name)
	{
		int scopeFirst=scope[scope.size()-1];
		for(int i=static_cast<int>(vars.size())-1;i>=scopeFirst;i--)
		{
			if(vars[i].name == name)
			{
				error.error("Varible alredy exist in this scope: "+name);
				return;
			}
		}

		Varible newvar;
		newvar.name = name;
		newvar.value = new Value::Value();
		vars.push_back(newvar);
	}
		
	/// Wyœwietla informacjê debuguj¹ce
	void debug()
	{

		for(unsigned int i=0;i<vars.size();i++)
		{
			cout << "[ " << vars[i].name << " ("<< vars[i].value->type <<") ] = " << *vars[i].value << endl;
		}
	}
	
	/// Rozpocznij nowy zakres zmiennych
	void beginScope()
	{
		scope.push_back(vars.size());
	}

	/// Zakoñcz bie¿¹cy zakres zmiennych
	void endScope()
	{
		unsigned int toSize=scope[scope.size()-1];
		scope.pop_back();
		while(vars.size()>toSize)
			vars.pop_back();
	}
};
extern VaribleManager varMan;