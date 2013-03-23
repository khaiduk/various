#pragma once
#include "Tokenizer.h"
#include "Program.h"
#include "Functions.h"
#include "Statements.h"
#include "Expressions.h"
#include "Error.h"
#include "Value.h"

/**
 * Analizator sk�adniowy.
 * Przestrze� nazw zawieraj�ca funkcje analizatora sk�adniowego.
 * Funkcje s� wywo�ywane rekurencyjnie, zwracaj�c odpowienie struktury
 * danych (DataStuct).
 */
namespace Parser
{
	/**
	 * Analizuje program.
	 * Analizuje ca�y program, kt�ry mo�na wykona� lub zdebugowa�.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Program* Program(Tokenizer &tokenizer);

	/**
	 * Analizuje pojedyncz� instrukcj�.
	 * Analizuje pojedyncze instrukcje, np. instrukcj� warunkow�, p�tl� while,
	 * czy instukcj� wyra�eniow�.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Statement* Statement(Tokenizer &tokenizer);

	Value::Type Type(Tokenizer &tokenizer);

	/**
	 * Analizuje pojedyncz� funkcj�.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Function* Function(Tokenizer &tokenizer);


	/**
	 * Analizuje wyra�enie.
	 * Analizuje wyra�enie przypisania. Wywo�uje kolejne funkcje
	 * analizuj�ce wyra�enie.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Expression* Expression(Tokenizer &tokenizer);

	///@{
	/**
	 * Funkcja analizuj�ca wyra�enie.
	 * Analizuje wyra�enie arytmetyczne, wywo�uj�c kolejne funkcje 
	 * analizuj�ce wyra�enie zachowuj�c piorytet operator�w.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionLogOr(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionLogAnd(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionBitOr(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionBitXor(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionBitAnd(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionEqal(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionRelation(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionShift(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionAdd(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionMul(Tokenizer &tokenizer);
	DataStruct::Expression* ExpressionPow(Tokenizer &tokenizer);
	///@}

	/**
	 * Analizuje wyra�enie rzutowania
	 * Analizuje wyra�enie w postaci int(sth);
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionCast(Tokenizer &tokenizer);

	/**
	 * Analizuje wyra�enie unarne.
	 * Analizuje wyra�enie z operatorem unarnym (np. negacja, preinkrementacja).
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionUnary(Tokenizer &tokenizer);

	/**
	 * Analizuje wyra�enie postfiksowe (JESZCZE NIE GOTOWE).
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionPostfix(Tokenizer &tokenizer);
	
	/**
	 * Analizuje wyra�enia podstawowe.
	 * Podstaowym wyra�eniem jest litera�, zmienna, wywo�anie funkcji lub wyra�enie w nawiasach.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionPrimary(Tokenizer &tokenizer);
	
	/**
	 * Analizuje typ danych.
	 * Analizuje typ danych np. "int", "float", "char[]", itp.
	 * @param tokenizer Analizator sk�adniowy z kodem programu.
	 */
	Value::Type TypeName(Tokenizer &tokenizer);
};

