#pragma once
#include "Tokenizer.h"
#include "Program.h"
#include "Functions.h"
#include "Statements.h"
#include "Expressions.h"
#include "Error.h"
#include "Value.h"

/**
 * Analizator sk³adniowy.
 * Przestrzeñ nazw zawieraj¹ca funkcje analizatora sk³adniowego.
 * Funkcje s¹ wywo³ywane rekurencyjnie, zwracaj¹c odpowienie struktury
 * danych (DataStuct).
 */
namespace Parser
{
	/**
	 * Analizuje program.
	 * Analizuje ca³y program, który mo¿na wykonaæ lub zdebugowaæ.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Program* Program(Tokenizer &tokenizer);

	/**
	 * Analizuje pojedyncz¹ instrukcjê.
	 * Analizuje pojedyncze instrukcje, np. instrukcjê warunkow¹, pêtlê while,
	 * czy instukcjê wyra¿eniow¹.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Statement* Statement(Tokenizer &tokenizer);

	Value::Type Type(Tokenizer &tokenizer);

	/**
	 * Analizuje pojedyncz¹ funkcjê.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Function* Function(Tokenizer &tokenizer);


	/**
	 * Analizuje wyra¿enie.
	 * Analizuje wyra¿enie przypisania. Wywo³uje kolejne funkcje
	 * analizuj¹ce wyra¿enie.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Expression* Expression(Tokenizer &tokenizer);

	///@{
	/**
	 * Funkcja analizuj¹ca wyra¿enie.
	 * Analizuje wyra¿enie arytmetyczne, wywo³uj¹c kolejne funkcje 
	 * analizuj¹ce wyra¿enie zachowuj¹c piorytet operatorów.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
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
	 * Analizuje wyra¿enie rzutowania
	 * Analizuje wyra¿enie w postaci int(sth);
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionCast(Tokenizer &tokenizer);

	/**
	 * Analizuje wyra¿enie unarne.
	 * Analizuje wyra¿enie z operatorem unarnym (np. negacja, preinkrementacja).
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionUnary(Tokenizer &tokenizer);

	/**
	 * Analizuje wyra¿enie postfiksowe (JESZCZE NIE GOTOWE).
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionPostfix(Tokenizer &tokenizer);
	
	/**
	 * Analizuje wyra¿enia podstawowe.
	 * Podstaowym wyra¿eniem jest litera³, zmienna, wywo³anie funkcji lub wyra¿enie w nawiasach.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	DataStruct::Expression* ExpressionPrimary(Tokenizer &tokenizer);
	
	/**
	 * Analizuje typ danych.
	 * Analizuje typ danych np. "int", "float", "char[]", itp.
	 * @param tokenizer Analizator sk³adniowy z kodem programu.
	 */
	Value::Type TypeName(Tokenizer &tokenizer);
};

