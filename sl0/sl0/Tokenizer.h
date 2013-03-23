#pragma once

#include "stdafx.h"

/**
 * Reprezentacja Tokenu. Prosta struktura reprezentuj�ca pojedynczy
 * symbol leksykalny
 */
class Token
{
public:
	/// Typ tokenu.
	enum Type {IDENTIFIER, KEYWORD, OPERATOR, LITERAL, ERROR};
	Type type; ///< Typ tokenu. np. Identyfikator lub s�owo kluczowe.
	string val; ///< Zawarto�� tokenu, tak jak w kodzie �r�d�owym.

	/**
	 * Konstruktor Tokenu.
	 * Domy�lnie zak�adam �e je�eli nie uda si� rozpozna� tokenu, to jest on b��dny (Token::ERROR).
	 */
	Token():type(ERROR),val(""){}

	/// Sprawdzamy czy dany token jest b��dny
	bool Error(){return type==ERROR;} 
};

/**
 * Analizator sk�adniowy.
 * Obiekt tej klasy rozk�ada tekst kodu �r�d�owego na pojedyncze tokeny.
 * W�a�ciwie gotowy analizator leksykalny do C-BOT.
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
	void next(); // Pobiera nast�pny token

public:
	/**
	 * Konstruktor tokenizera.
	 * @param code Kod �r�d�owy do przetworzenia.
	 */
	Tokenizer(string code): input(code), pos(0), linenum(1)
	{
		next();
	}

	Token getToken();
	Token peekToken();

	friend class Error;
};

