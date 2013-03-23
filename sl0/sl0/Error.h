#pragma once
#include "stdafx.h"
#include "Tokenizer.h"
/// Klasa obs�ugi b��d�w.
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

	/// Zg�asza b��d.
	void error(string txt)
	{
		if(tzer == NULL)
			cout <<"Error: " << txt << endl;
		else
			cout <<"Error: line: "<<tzer->linenum << " " << txt << endl;
		ok = false;
	}
	/// Zg�asza b��d krytyczny.
	void critical(string txt)
	{
		if(tzer == NULL)
			cout <<"Error: " << txt << endl;
		else
			cout <<"Error: line: "<<tzer->linenum << " " << txt << endl;
		ok = false;
		throw "Critical error";
	}
	/// Zg�asza ostrze�enie.
	void warning(string txt)
	{
		if(tzer == NULL)
			cout <<"Warning: " << txt << endl;
		else
			cout <<"Warning: line: "<<tzer->linenum << " " << txt << endl;
	}
	/// Sprawdza czy mo�na uruchuchomi�
	bool isOk(){ return ok; }
};

/// Obiekt do obs�ugi b��d�w.
extern Error error;
