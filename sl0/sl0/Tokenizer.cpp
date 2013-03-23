#include "StdAfx.h"
#include "Tokenizer.h"

/**
 * Pobiera nastêpny token.
 * Zwraca nastêpny token.
 * @see peekToken()
 */
Token Tokenizer::getToken()
{
	Token curr=currentToken;// return current token and get next
	next();
	return curr;
}

/**
 * Podgl¹da nastêpny token.
 * Zwraca nastêpny token, ale w odró¿nieniu od getToken() token dalej mo¿na
 * odczyaæ w tokenizerze. Pozwala to na podgl¹d (lookahead) symbolu leksykalnego.
 * @see getToken()
 */
Token Tokenizer::peekToken()
{
	return currentToken;
}

void Tokenizer::next()
{	
	while(true)
	{
		bool noChanges=true;
		while(pos < input.length() && ( input[pos]==' ' || input[pos]=='\t' || input[pos]=='\n' ) )
		{
			if( input[pos]=='\n' ) linenum++;
			pos++;
			noChanges=false;
		} //skip whitespace
		while(pos < input.length() && input[pos]=='/' && input[pos+1]=='/')
		{
			while(pos < input.length() && input[pos]!='\n') pos++;
			linenum++;
			pos++;
			noChanges=false;
		} //skip comment //
		while(pos < input.length() && input[pos]=='/' && input[pos+1]=='*')
		{
			pos++;
			while(pos < input.length() && ( input[pos-1]!='*' || input[pos]!='/'))
			{
				if( input[pos]=='\n' ) linenum++;
				pos++;
			}
			pos++;
			noChanges=false;
		} //skip comment /* */
		if(noChanges) break;
	}
	currentToken.val="";
	currentToken.type=Token::ERROR;
	if(pos >= input.length()) return;

	if(input[pos]=='_' || isAlpha(input[pos]))
	{
		currentToken.type=Token::IDENTIFIER;

		while(input[pos]=='_' || isAlpha(input[pos]) || isNum(input[pos]))
		{
			currentToken.val+=input[pos];
			pos++;
		}
		
		if(currentToken.val=="and" || currentToken.val=="or" || currentToken.val=="not" || currentToken.val=="new" || currentToken.val=="sizeof")
		{
			currentToken.type=Token::OPERATOR;
			if(currentToken.val=="and") currentToken.val="&&";
			if(currentToken.val=="or") currentToken.val="||";
			if(currentToken.val=="not") currentToken.val="!";
		}
		else if(currentToken.val=="null" || currentToken.val=="nan" || currentToken.val=="true" || currentToken.val=="false")
			currentToken.type=Token::LITERAL;
		else if(currentToken.val=="if" ||	   currentToken.val=="else" ||    currentToken.val=="while" ||     currentToken.val=="do" ||
				currentToken.val=="for" ||	   currentToken.val=="break" ||   currentToken.val=="continue" ||  currentToken.val=="switch" ||
				currentToken.val=="case" ||    currentToken.val=="default" || currentToken.val=="try" ||       currentToken.val=="throw" ||
				currentToken.val=="catch" ||   currentToken.val=="finally" || currentToken.val=="return" ||    currentToken.val=="class" ||
				currentToken.val=="extends" || currentToken.val=="super" ||   currentToken.val=="public" ||    currentToken.val=="extern" ||
				currentToken.val=="final" ||   currentToken.val=="static" ||  currentToken.val=="protected" || currentToken.val=="private" ||
				currentToken.val=="synchronized")
			currentToken.type=Token::KEYWORD;
	}
	else if(isNum(input[pos]))
	{
		currentToken.type=Token::LITERAL;

		while(isNum(input[pos]))
		{
			currentToken.val+=input[pos];
			pos++;
		}
		if(input[pos] == '.') // eg. 0.5
		{
			currentToken.val+=input[pos++];
			while(isNum(input[pos]))
			{
				currentToken.val+=input[pos];
				pos++;
			}
		}
		if(input[pos] == 'e' || input[pos] == 'E') // eg. 10E+5
		{
			currentToken.val+=input[pos++];
			if(input[pos] == '+' || input[pos] == '-')
				currentToken.val+=input[pos++];
			while(isNum(input[pos]))
			{
				currentToken.val+=input[pos];
				pos++;
			}
		}
	}
	else if(input[pos] == '(' || input[pos] == ')' || input[pos] == '{' || input[pos] == '}' ||  
			input[pos] == ';' || input[pos] == ',' || input[pos] == '.' || input[pos] == '[' || 
			input[pos] == ']' || input[pos] == '?' || input[pos] == '~')
	{
		currentToken.type=Token::OPERATOR;
		currentToken.val+=input[pos++];
	}
	else if(input[pos] == ':')
	{
		currentToken.type=Token::OPERATOR;
		currentToken.val+=input[pos++]; // :
		if(input[pos] == ':')
			currentToken.val+=input[pos++]; // ::
	}
	else if(input[pos] == '=' || input[pos] == '!' || input[pos] == '%' || input[pos] == '^' || input[pos] == '/')
	{
		currentToken.type=Token::OPERATOR;
		currentToken.val+=input[pos++]; // eg. /
		if(input[pos] == '=')
			currentToken.val+=input[pos++]; // eg. /=
	}
	else if(input[pos] == '*' || input[pos] == '+' || input[pos] == '-' || input[pos] == '&' || input[pos] == '|')
	{
		currentToken.type=Token::OPERATOR;
		currentToken.val+=input[pos++]; // eg. *
		if(input[pos] == '=' || input[pos] == currentToken.val[0])
			currentToken.val+=input[pos++]; // eg. *= and **
	}
	else if(input[pos] == '<')
	{
		currentToken.type=Token::OPERATOR;
		currentToken.val+=input[pos++]; // <
		if(input[pos] == '=')
			currentToken.val+=input[pos++]; // <=
		else if(input[pos] == '<')
		{
			currentToken.val+=input[pos++]; // <<
			if(input[pos] == '=')
				currentToken.val+=input[pos++]; // <<=
		}
	}
	else if(input[pos] == '>')
	{
		currentToken.type=Token::OPERATOR;
		currentToken.val+=input[pos++]; // >
		if(input[pos] == '=')
			currentToken.val+=input[pos++];// >=
		else if(input[pos] == '>')
		{
			currentToken.val+=input[pos++]; // >>
			if(input[pos] == '=')
				currentToken.val+=input[pos++]; // >>=
			else if(input[pos]=='>')
			{
				currentToken.val+=input[pos++]; // >>>
				if(input[pos]=='=')
					currentToken.val+=input[pos++]; // >>>=
			}
		}
	}
	else if(input[pos] == '\'') // 'x' - char literal
	{
		currentToken.type=Token::LITERAL;
		currentToken.val+=input[pos++]; // '
		if(input[pos] == '\\')
		{
			pos++;
			switch(input[pos])
			{
			case '\\': currentToken.val+='\\'; break;
			case '\"': currentToken.val+='\"'; break;
			case '\'': currentToken.val+='\''; break;
			default:  currentToken.val+=input[pos++];
			}
			pos++;
		}
		else
		currentToken.val+=input[pos++];

		currentToken.val+=input[pos++];// '

	}
	else if(input[pos] == '\"') // "abcd" - string literal
	{
		currentToken.type=Token::LITERAL;
		currentToken.val+=input[pos++]; // "
		while(input[pos] != '\"')
		{
			if(input[pos] == '\\')
			{
				pos++;
				switch(input[pos])
				{
				case '\\': currentToken.val+='\\'; break;
				case '\"': currentToken.val+='\"'; break;
				case '\'': currentToken.val+='\''; break;
				default:  currentToken.val+=input[pos++];
				}
				pos++;
			}
			else
			currentToken.val+=input[pos++];
		}
		currentToken.val+=input[pos++];// "
	}
}