#pragma once
#include "stdafx.h"
#include "Tokenizer.h"
/// Klasa obs³ugi b³êdów.
class Error
{
	bool ok;
	Tokenizer* tzer;
public:
	Error():ok(true),tzer(NULL){}
	~Error(){}

	/// Podpina tokenizer
	void bindTokenizer(Tokenizer* tokenizer)
	{
		tzer = tokenizer;
	}

	/// Zg³asza b³¹d.
	void error(string txt)
	{
		if(tzer == NULL)
			cout <<"Error: " << txt << endl;
		else
			cout <<"Error: line: "<<tzer->linenum << " " << txt << endl;
		ok = false;
	}
	/// Zg³asza b³¹d krytyczny.
	void critical(string txt)
	{
		if(tzer == NULL)
			cout <<"Error: " << txt << endl;
		else
			cout <<"Error: line: "<<tzer->linenum << " " << txt << endl;
		ok = false;
		throw "Critical error";
	}
	/// Zg³asza ostrze¿enie.
	void warning(string txt)
	{
		if(tzer == NULL)
			cout <<"Warning: " << txt << endl;
		else
			cout <<"Warning: line: "<<tzer->linenum << " " << txt << endl;
	}
	/// Sprawdza czy mo¿na uruchuchomiæ
	bool isOk(){ return ok; }
};

/// Obiekt do obs³ugi b³êdów.
extern Error error;
