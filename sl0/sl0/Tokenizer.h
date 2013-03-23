#pragma once

#include "stdafx.h"

/**
 * Reprezentacja Tokenu. Prosta struktura reprezentuj¹ca pojedynczy
 * symbol leksykalny
 */
class Token
{
public:
	/// Typ tokenu.
	enum Type {IDENTIFIER, KEYWORD, OPERATOR, LITERAL, ERROR};
	Type type; ///< Typ tokenu. np. Identyfikator lub s³owo kluczowe.
	string val; ///< Zawartoœæ tokenu, tak jak w kodzie Ÿród³owym.

	/**
	 * Konstruktor Tokenu.
	 * Domyœlnie zak³adam ¿e je¿eli nie uda siê rozpoznaæ tokenu, to jest on b³êdny (Token::ERROR).
	 */
	Token():type(ERROR),val(""){}

	/// Sprawdzamy czy dany token jest b³êdny
	bool Error(){return type==ERROR;} 
};

/**
 * Analizator sk³adniowy.
 * Obiekt tej klasy rozk³ada tekst kodu Ÿród³owego na pojedyncze tokeny.
 * W³aœciwie gotowy analizator leksykalny do C-BOT.
 */
class Tokenizer
{
private:
	string input;
	size_t pos;
	int linenum;
	Token currentToken;
	bool isAlpha(char a){ return ( a>='a' && a<='z' ) || ( a>='A' && a<='Z' ); }
	bool isNum(char a)	{ return a>='0' && a<='9'; }
	void next(); // Pobiera nastêpny token

public:
	/**
	 * Konstruktor tokenizera.
	 * @param code Kod Ÿród³owy do przetworzenia.
	 */
	Tokenizer(string code): input(code), pos(0), linenum(1)
	{
		next();
	}

	Token getToken();
	Token peekToken();

	friend class Error;
};

