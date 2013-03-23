#pragma once
#include "stdafx.h"
#include "Value.h"

/// Przestrzeñ nazw struktur danych.
namespace DataStruct
{

	/// Wyj¹tek steruj¹cy. (np. break, return)
	class ControlException
	{
	public:
		enum Type {BREAK, CONTINUE, RETURN};
		Type type;
		Value::Value value;
		
		ControlException(Type t): type(t){}
		ControlException(Type t, Value::Value val): type(t), value(val){}
	};
	/// Wyra¿enie. 
	class Expression
	{
	public:
		/// Oblicza wyra¿enie.
		virtual Value::Value Eval() = 0;

		/**
		 * Podaje wskaŸnik na wartoœæ wyra¿enia jeœli jest l-wartoœci¹.
		 * W przypadku gdy wyra¿enie nie jest l-wartoœci¹ zwraca NULL
		 * @return WskaŸnik na wartoœæ
		 */
		virtual Value::Value* Lvalue() = 0;

		/// Wyœwietla informacjê debuguj¹ce
		virtual void debug()=0;
		
		/// Sprawdza zgodnoœæ typów
		virtual Value::Type checkTypes() { return Value::ERROR; }
	};
	
	/// Instrukcja. Wirtualna klasa na obiekt instrukcji.
	class Statement
	{
	public:
		/// Wykonuje dan¹ instrukcjê.
		virtual void Exec() = 0;

		/// Wyœwietla informacjê debuguj¹ce
		virtual void debug()=0;

		/// Sprawdza zgodnoœæ typów
		virtual bool checkTypes() { return true; }
	};
}