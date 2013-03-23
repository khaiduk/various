#pragma once
#include "stdafx.h"
#include "Value.h"

/// Przestrze� nazw struktur danych.
namespace DataStruct
{

	/// Wyj�tek steruj�cy. (np. break, return)
	class ControlException
	{
	public:
		enum Type {BREAK, CONTINUE, RETURN};
		Type type;
		Value::Value value;
		
		ControlException(Type t): type(t){}
		ControlException(Type t, Value::Value val): type(t), value(val){}
	};
	/// Wyra�enie. 
	class Expression
	{
	public:
		/// Oblicza wyra�enie.
		virtual Value::Value Eval() = 0;

		/**
		 * Podaje wska�nik na warto�� wyra�enia je�li jest l-warto�ci�.
		 * W przypadku gdy wyra�enie nie jest l-warto�ci� zwraca NULL
		 * @return Wska�nik na warto��
		 */
		virtual Value::Value* Lvalue() = 0;

		/// Wy�wietla informacj� debuguj�ce
		virtual void debug()=0;
		
		/// Sprawdza zgodno�� typ�w
		virtual Value::Type checkTypes() { return Value::ERROR; }
	};
	
	/// Instrukcja. Wirtualna klasa na obiekt instrukcji.
	class Statement
	{
	public:
		/// Wykonuje dan� instrukcj�.
		virtual void Exec() = 0;

		/// Wy�wietla informacj� debuguj�ce
		virtual void debug()=0;

		/// Sprawdza zgodno�� typ�w
		virtual bool checkTypes() { return true; }
	};
}