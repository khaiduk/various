#include "StdAfx.h"
#include "Value.h"
Value::Type Value::StrToType(string s)
{
	Type type;
	if(s == "int")
		type = INT;
	else if(s == "float")
		type = FLOAT;
	else if(s == "bool")
		type = BOOL;
	else if(s == "char")
		type = CHAR;
	else if(s == "string")
	{
		type = ARRAY;
		Type* charType = new Type(CHAR);
		type.arrayType =charType;
	}
	else
		type = ERROR;
	return type;
}

bool Value::isTypename(string s)
{
	return ( s=="int" || s=="float" || s=="bool" || s=="char" || s == "string" );
}
Value::Value Value::op(string opName, Value a, Value b)
{
	Value result;
	result.type=ERROR;
	result.val=0;
	if(opName=="||" || opName=="&&")
	{
		if(a.type!=BOOL || b.type!=BOOL)
		{
			error.error("Wrong type - must be boolean");
			return result;
		}
		else
		{
			result.type=BOOL;
			if(opName=="||")
				result.val=a.getBool() || b.getBool();
			else if(opName=="&&")
				result.val=a.getBool() && b.getBool();
			return result;
		}
	}
	else if(opName=="|" || opName=="&" || opName=="^")
	{
		if(a.type != b.type)
		{
			error.error("must be same types");
			return result;
		}
		if(a.type==BOOL)
		{
			bool abool=a.getBool();
			bool bbool=b.getBool();

			result.type=BOOL;

			if(opName=="^")
				result.val=(abool && !bbool) || (!abool && bbool);
			else if(opName=="|")
				result.val=abool || bbool;
			else // &
				result.val=abool && bbool;

			return result;
		}
		else if(a.type==CHAR)
		{
			result.type=CHAR;
			if(opName=="^")
				result.val=static_cast<char>( a.getChar() ^ b.getChar() );
			else if(opName=="|")
				result.val=static_cast<char>( a.getChar() | b.getChar() );
			else // &
				result.val=static_cast<char>( a.getChar() & b.getChar() );
			return result;
		}
		else if(a.type==INT)
		{
			result.type=INT;
			if(opName=="^")
				result.val=a.getInt() ^ b.getInt();
			else if(opName=="|")
				result.val=a.getInt() | b.getInt();
			else // &
				result.val=a.getInt() & b.getInt();
			return result;
		}
	}
	else if(opName=="==" || opName=="!=" || opName=="<" || opName=="<=" || opName==">" || opName==">=")
	{
		result.type = BOOL;
		if(a.type == FLOAT || b.type == FLOAT)
		{
			if(opName=="==")
				result.val = ( a.getFloat() == b.getFloat() );
			else if(opName=="!=")
				result.val = ( a.getFloat() != b.getFloat() );
			else if(opName=="<")
				result.val = ( a.getFloat() <  b.getFloat() );
			else if(opName=="<=")
				result.val = ( a.getFloat() <= b.getFloat() );
			else if(opName==">")
				result.val = ( a.getFloat() >  b.getFloat() );
			else// >=
				result.val = ( a.getFloat() >= b.getFloat() );
		}
		else if(a.type == INT || b.type == INT)
		{
			if(opName=="==")
				result.val = ( a.getInt() == b.getInt() );
			else if(opName=="!=")
				result.val = ( a.getInt() != b.getInt() );
			else if(opName=="<")
				result.val = ( a.getInt() <  b.getInt() );
			else if(opName=="<=")
				result.val = ( a.getInt() <= b.getInt() );
			else if(opName==">")
				result.val = ( a.getInt() >  b.getInt() );
			else// >=
				result.val = ( a.getInt() >= b.getInt() );
		}
		else if(a.type == CHAR || b.type == CHAR)
		{
			if(opName=="==")
				result.val = ( a.getChar() == b.getChar() );
			else if(opName=="!=")
				result.val = ( a.getChar() != b.getChar() );
			else if(opName=="<")
				result.val = ( a.getChar() <  b.getChar() );
			else if(opName=="<=")
				result.val = ( a.getChar() <= b.getChar() );
			else if(opName==">")
				result.val = ( a.getChar() >  b.getChar() );
			else// >=
				result.val = ( a.getChar() >= b.getChar() );
		}
		else //bool
		{
			if(opName=="==")
				result.val = ( a.getBool() == b.getBool() );
			else if(opName=="!=")
				result.val = ( a.getBool() != b.getBool() );
			else if(opName=="<")
				result.val = ( a.getBool() <  b.getBool() );
			else if(opName=="<=")
				result.val = ( a.getBool() <= b.getBool() );
			else if(opName==">")
				result.val = ( a.getBool() >  b.getBool() );
			else// >=
				result.val = ( a.getBool() >= b.getBool() );
		}
		return result;
	}
	else if(opName=="+" || opName=="-" || opName=="*" || opName=="/")
	{
		if(a.type == FLOAT || b.type == FLOAT)
		{
			result.type = FLOAT;
			if(opName=="+")
				result.val = float( a.getFloat() + b.getFloat() );
			else if(opName=="-")
				result.val = float( a.getFloat() - b.getFloat() );
			else if(opName=="*")
				result.val = float( a.getFloat() * b.getFloat() );
			else// /
				if( b.getFloat() == 0)
				{
					error.error("Division by 0");
				}
				else
				result.val = float( a.getFloat() / b.getFloat() );
		}
		else if(a.type == INT || b.type == INT)
		{
			result.type = INT;
			if(opName=="+")
				result.val = int( a.getInt() + b.getInt() );
			else if(opName=="-")
				result.val = int( a.getInt() - b.getInt() );
			else if(opName=="*")
				result.val = int( a.getInt() * b.getInt() );
			else // /
				if( b.getInt() == 0)
				{
					error.error("Division by 0");
				}
				else
				result.val = int( a.getInt() / b.getInt() );
		}
		else if(a.type == CHAR || b.type == CHAR)
		{
			result.type = CHAR;
			if(opName=="+")
				result.val = char( a.getChar() + b.getChar() );
			else if(opName=="-")
				result.val = char( a.getChar() - b.getChar() );
			else if(opName=="*")
				result.val = char( a.getChar() * b.getChar() );
			else // /
				if( b.getChar() == 0)
				{
					error.error("Division by 0");
				}
				else
				result.val = char( a.getChar() / b.getChar() );
		}
		return result;
	}
	else if(opName=="**")
	{
		result.type = FLOAT;
		result.val = float(pow( a.getFloat() , b.getFloat() ));
		return result;
	}
	else if(opName=="%")
	{
		if(a.type == FLOAT || b.type == FLOAT)
		{
			return result;
		}
		if(a.type == BOOL || b.type == BOOL)
		{
			return result;
		}
		else if(a.type == INT || b.type == INT)
		{
			result.type = INT;
			result.val = int( a.getInt() % b.getInt() );
		}
		else if(a.type == CHAR || b.type == CHAR)
		{
			result.type = INT;
			result.val = int( a.getInt() % b.getInt() );
		}
		return result;
	}
	else if(opName=="<<" || opName==">>" || opName==">>>")
	{
		if(a.type == FLOAT || b.type == FLOAT)
		{
			return result;
		}
		if(a.type == BOOL || b.type == BOOL)
		{
			return result;
		}
		else if(a.type == INT || b.type == INT)
		{
			result.type = INT;
			if(opName=="<<")
				result.val = int( a.getInt() << b.getInt() );
			else if(opName==">>")
				result.val = int( a.getInt() >> b.getInt() );
			else// >>>
			{
				if(a.getInt()>=0)
					return op(">>", a, b);
				else
					result.val = int( signed ( unsigned(a.getInt()) >> (b.getInt()+1) ) );
			}
		}
		else if(a.type == CHAR || b.type == CHAR)
		{
			result.type = INT;
			if(opName=="<<")
				result.val = int( a.getInt() << b.getInt() );
			else if(opName==">>")
				result.val = int( a.getInt() >> b.getInt() );
			else// >>>
			{
				if(a.getInt()>=0)
					result.val = int( a.getInt() >> b.getInt() );
				else
					result.val = int( signed ( unsigned(a.getInt()) >> (b.getInt()+1) ) );
			}
		}
	}
	else error.error( "Operator unrecognized: " + opName);
	return result;
}


Value::Value Value::op(string opName, Value a) //unary operator
{
	Value result;
	result.type=ERROR;
	result.val=0;

	if(opName=="+")
	{
		return a;
	}
	else if(opName=="-")
	{
		if(a.type == FLOAT)
		{
			result.type = FLOAT;
			result.val = float( -a.getFloat() );
		}
		else if(a.type == INT)
		{
			result.type = INT;
				result.val = int( -a.getInt() );
		}
		else if(a.type == CHAR)
		{
			result.type = CHAR;
				result.val = char( -a.getChar() );
		}
		return result;
	}
	else if(opName=="~")
	{
		if(a.type == INT)
		{
			result.type = INT;
				result.val = int( ~ a.getInt() );
		}
		else if(a.type == CHAR)
		{
			result.type = CHAR;
				result.val = char( ~ a.getChar() );
		}
		return result;
	}
	else if(opName=="!")
	{
		if(a.type == BOOL)
		{
			result.type = BOOL;
			result.val = bool( ! a.getBool() );
		}
		return result;
	}
	else if(opName=="sizeof")
	{
		if(a.type == ARRAY)
		{
			result.type = INT;
			vector < Value* > vec = boost::any_cast< vector < Value* > >(a.val);
			result.val = static_cast<int>(vec.size());
			return result;
		}
		else
		{
			result.type = INT;
			result.val = 0;
		}
		return result;
	}
	else error.error("Operator unrecognized: " + opName);
	return result;
}

Value::Type Value::checkTypes(string opName, Type a, Type b)
{
	Type result;
	result=ERROR;
	if(opName=="||" || opName=="&&")
	{
		if(a!=BOOL || b!=BOOL)
		{
			error.error ("Wrong type - must be boolean");
			return result;
		}
		else
		{
			result=BOOL;
			return result;
		}
	}
	else if(opName=="|" || opName=="&" || opName=="^")
	{
		if(a != b)
		{
			error.error("must be same types");
			return result;
		}
		else if(a == FLOAT)
		{
			error.error("must not be float");
			return result;
		}
		else
		{
			result=a;
			return result;
		}
	}
	else if(opName=="==" || opName=="!=" || opName=="<" || opName=="<=" || opName==">" || opName==">=")
	{
		result = BOOL;
		return result;
	}
	else if(opName=="+" || opName=="-" || opName=="*" || opName=="/")
	{
		if(a == BOOL || b == BOOL)
		{
			error.error("must not be boolean");
			return  result;
		}
		else if(a == FLOAT || b == FLOAT )
		{
			result = FLOAT;
		}
		else if(a == INT || b == INT)
		{
			result = INT;
		}
		else if(a == CHAR || b == CHAR)
		{
			result = CHAR;
		}
		return result;
	}
	else if(opName=="**")
	{
		result = FLOAT;
		return result;
	}
	else if(opName=="%")
	{
		if(a == FLOAT || b == FLOAT)
		{
			error.error("must not be float");
			return result;
		}
		else if(a == BOOL || b == BOOL)
		{
			error.error("must not be boolean");
			return result;
		}
		else if(a == INT || b == INT)
		{
			result = INT;
			return result;
		}
		else if(a == CHAR || b == CHAR)
		{
			result = INT;
			return result;
		}
		return result;
	}
	else if(opName=="<<" || opName==">>" || opName==">>>")
	{
		if(a == FLOAT || b == FLOAT)
		{
			error.error("must not be float");
			return result;
		}
		else if(a == BOOL || b == BOOL)
		{
			error.error("must not be boolean");
			return result;
		}
		else if(a == INT || b == INT)
		{
			result = INT;
		}
		else if(a == CHAR || b == CHAR)
		{
			result = INT;
		}
		return result;
	}
	else if(opName == "[]")
	{
		if(a != ARRAY)
			error.error("Must be an array");
		else
		{
			return *a.arrayType;
		}
	}
	else error.error("Operator unrecognized: " + opName);
	return result;
}

Value::Type Value::checkTypes(string opName, Type a)
{
	Type result;
	result=ERROR;

	if(opName=="+")
	{
		return a;
	}
	else if(opName=="-")
	{
		if(a == BOOL)
		{
			error.error("must not be boolean");
			return result;
		}
		else
			return a;
	}
	else if(opName=="~")
	{
		if(a == FLOAT)
		{
			error.error("must not be float");
			return result;
		}
		else if(a == BOOL)
		{
			error.error("must not be boolean");
			return result;
		}
		else
			return a;
	}
	else if(opName=="!")
	{
		if(a != BOOL)
		{
			error.error("must not be boolean");
			return result;
		}
		else
			return a;
	}
	else if(opName=="sizeof")
	{
		result = INT;
		return result;
	}
	else error.error("Operator unrecognized: " + opName);
	return result;
}