#include "StdAfx.h"
#include "Parser.h"

DataStruct::Program* Parser::Program(Tokenizer &tokenizer)
{
	DataStruct::Program* program= new DataStruct::Program;
	Token a=tokenizer.peekToken();
	while(a.type!=Token::ERROR)
	{
			program->addFunction(Function(tokenizer));
		a=tokenizer.peekToken();
	}
	return program;
}

DataStruct::Function* Parser::Function(Tokenizer &tokenizer)
{
	bool isExtern=false;

	Token a=tokenizer.peekToken();
	if(a.val == "extern")
	{
		isExtern = true;
		tokenizer.getToken();
		a=tokenizer.peekToken();
	}
	if(a.type!=Token::IDENTIFIER || ( !Value::isTypename(a.val) && a.val!="void" ) )
		error.error("Expected typename");
	Value::Type returntype = TypeName(tokenizer);
	a = tokenizer.getToken();
	if(a.type!=Token::IDENTIFIER)
		error.error("Expected identifier - function name");
	string name=a.val;
	DataStruct::Function* function=new DataStruct::Function(a.val,returntype,isExtern);
	a = tokenizer.getToken();
	if(a.type == Token::OPERATOR && a.val!="(")
		error.error("Missing (");
	a = tokenizer.peekToken();
	if( !(a.type==Token::OPERATOR && a.val==")"))
	{
		if(a.type!=Token::IDENTIFIER || ! Value::isTypename(a.val))
			error.error("Expected typename");
		Value::Value type = TypeName(tokenizer);
		a = tokenizer.getToken();
		function->addParam(a.val, type);
		a = tokenizer.peekToken();
		while(a.val==",")
		{
			tokenizer.getToken(); //,
			a = tokenizer.peekToken();
			if(a.type!=Token::IDENTIFIER || !Value::isTypename(a.val))
				error.error("Expected typename");
			Value::Value type = TypeName(tokenizer);
			a = tokenizer.getToken();
			function->addParam(a.val, type);
			a = tokenizer.peekToken();
		}
	}
	tokenizer.getToken();// )
	DataStruct::Statement* body = Statement(tokenizer);
	function->addBody(body);
	return function;
}

DataStruct::Statement* Parser::Statement(Tokenizer &tokenizer)
{
	Token a=tokenizer.peekToken();

	if(a.type==Token::OPERATOR && a.val=="{")
	{
		DataStruct::CompoundStatement* statement= new DataStruct::CompoundStatement;
		tokenizer.getToken();
		a=tokenizer.peekToken();
		while(!(a.type==Token::OPERATOR && a.val=="}") || a.Error() )
		{
			statement->addStatement(Statement(tokenizer));
			a=tokenizer.peekToken();
		}
		Token a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="}"))
			error.error("} missing");
		return statement;
	}

	else if(a.type==Token::IDENTIFIER && Value::isTypename(a.val))
	{
		DataStruct::DeclarationStatement* declaration = new DataStruct::DeclarationStatement;
		
		Value::Type varType = TypeName(tokenizer);

		while(true)
		{
			Value::Type thisType=varType;
			a=tokenizer.getToken();
			if(!(a.type==Token::IDENTIFIER))
			{
				error.error("Identifier expected");
				break;
			}
			string varId=a.val;
			a=tokenizer.getToken();
			while(a.val == "[")
			{
				a=tokenizer.getToken();
				if(a.type == Token::LITERAL)
					a=tokenizer.getToken();
				if(a.val!="]")
					error.error("expected ]");
				thisType = Value::Type::arrayOf(thisType);
				a=tokenizer.getToken();
			}
			if(a.val == "=")
			{
				declaration->addDeclaration(varId, thisType, Expression(tokenizer));
				a = tokenizer.getToken();

			}
			else
			{
				declaration->addDeclaration(varId, thisType);
			}
			if(a.val==";")
			{
				break;
			}
			else if(a.val==",")
			{
				continue;
			}
			else
			{
				error.error("Wrong varible declaration");
				break;
			}
		}
		return declaration;
	}

	else if(a.type==Token::KEYWORD && a.val=="if")
	{
		DataStruct::IfStatement* ifstatement;
		DataStruct::Expression* condition;
		DataStruct::Statement* ifTrue;
		DataStruct::Statement* ifFalse;
		tokenizer.getToken();
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="(") )
			error.error("( expected");
		condition=Expression(tokenizer);
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==")") )
			error.error("missing )");
		ifTrue=Statement(tokenizer);
		if(tokenizer.peekToken().val=="else")
		{
			tokenizer.getToken();
			ifFalse=Statement(tokenizer);
			ifstatement= new DataStruct::IfStatement(condition, ifTrue, ifFalse);
		}
		else
			ifstatement= new DataStruct::IfStatement(condition, ifTrue);
		return ifstatement;
	}

	else if(a.type==Token::KEYWORD && a.val=="switch")
	{
		DataStruct::SwitchStatement* switchstatement;
		DataStruct::Expression* condition;

		tokenizer.getToken();
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="(") )
			error.error("( expected");
		condition=Expression(tokenizer);
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==")") )
			error.error("missing )");
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="{") )
			error.error("missing {");

		switchstatement = new DataStruct::SwitchStatement( condition );

		a=tokenizer.peekToken();
		while(!(a.type==Token::OPERATOR && a.val=="}") || a.Error() )
		{
			if(a.val == "case")
			{
				tokenizer.getToken();
				DataStruct::Expression* literalExp = ExpressionPrimary(tokenizer);
				Value::Value value = literalExp->Eval();
				a = tokenizer.getToken();
				if(a.val != ":") error.error("missing :");
				switchstatement->addCase(value);
			}
			else if(a.val == "default")
			{
				tokenizer.getToken();
				a = tokenizer.getToken();
				if(a.val != ":") error.error("missing :");
				switchstatement->addDefault();
			}
			else
			{
				DataStruct::Statement* statem = Statement(tokenizer);
				switchstatement->addStatement(statem);
			}
			a=tokenizer.peekToken();
		}
		tokenizer.getToken();
		return switchstatement;
	}

	else if(a.type==Token::KEYWORD && a.val=="while")
	{
		DataStruct::Expression* condition;
		DataStruct::Statement* loop;
		tokenizer.getToken();
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="(") )
			error.error( "( expected" );
		condition=Expression(tokenizer);
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==")") )
			error.error( "missing )" );
		loop=Statement(tokenizer);
		DataStruct::WhileStatement* whilestatement= new DataStruct::WhileStatement(condition, loop);
		return whilestatement;
	}

	else if(a.type==Token::KEYWORD && a.val=="do")
	{
		DataStruct::Expression* condition;
		DataStruct::Statement* loop;

		tokenizer.getToken();

		loop = Statement(tokenizer);

		a=tokenizer.getToken();
		if(!(a.type==Token::KEYWORD && a.val=="while") )
			error.error( "while expected" );

		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="(") )
			error.error( "( expected" );

		condition=Expression(tokenizer);
		
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==")") )
			error.error( "missing )" );
		
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==";") )
			error.error( "missing ;" );

		DataStruct::DoWhileStatement* dowhilestatement= new DataStruct::DoWhileStatement(condition, loop);
		return dowhilestatement;
	}

	else if(a.type==Token::KEYWORD && a.val=="for")
	{
		DataStruct::Statement* init;
		DataStruct::Expression* condition;
		DataStruct::Expression* after;
		DataStruct::Statement* loop;
		tokenizer.getToken();
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val=="(") )
			error.error( "( expected" );
		init=Statement(tokenizer);

		condition=Expression(tokenizer);
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==";") )
			error.error( "missing ;" );
		
		after=Expression(tokenizer);
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==")") )
			error.error( "missing )" );

		loop=Statement(tokenizer);

		DataStruct::ForStatement* forstatement= new DataStruct::ForStatement(init, condition, after, loop);
		return forstatement;
	}
	
	else if(a.type==Token::KEYWORD && a.val=="break")
	{
		DataStruct::Statement* breakstatement=new DataStruct::BreakStatement;
		tokenizer.getToken();
		a = tokenizer.getToken();
		if(a.val != ";")
			error.error("missing ;");
		return breakstatement;
	}
	
	else if(a.type==Token::KEYWORD && a.val=="continue")
	{
		DataStruct::Statement* continuestatement=new DataStruct::ContinueStatement;
		tokenizer.getToken();
		a = tokenizer.getToken();
		if(a.val != ";")
			error.error("missing ;");
		return continuestatement;
	}

	else if(a.type==Token::KEYWORD && a.val=="return")
	{
		DataStruct::ReturnStatement* returnstatement;
		tokenizer.getToken();
		a = tokenizer.peekToken();
		if(a.val == ";")
		{
			tokenizer.getToken();
			returnstatement=new DataStruct::ReturnStatement();
		}
		else
		{
			DataStruct::Expression* expression=Expression(tokenizer);
			
			returnstatement=new DataStruct::ReturnStatement(expression);
			a=tokenizer.getToken();
			if(a.val != ";")
				error.error("missing ;");
		}
		return returnstatement;
	}

	else if(a.type==Token::OPERATOR && a.val==";")
	{
		DataStruct::Statement* nullstatement=new DataStruct::NullStatement;
		tokenizer.getToken();
		return nullstatement;
	}

	else 
	{
		DataStruct::ExpressionStatement* expressionstatement= new DataStruct::ExpressionStatement(Expression(tokenizer));
		a=tokenizer.getToken();
		if(!(a.type==Token::OPERATOR && a.val==";"))
			error.error( "; expected" );
		return expressionstatement;
	}

}

DataStruct::Expression* Parser::Expression(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionLogOr(tokenizer);
	Token a = tokenizer.peekToken();
	if(a.type==Token::OPERATOR && (a.val=="=" || a.val=="%=" || a.val=="^=" || a.val=="/=" || a.val=="*=" ||
									 a.val=="+=" || a.val=="-=" || a.val=="&=" || a.val=="|=" || a.val=="<<=" ||
									 a.val==">>=" || a.val==">>>=" ) )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = Expression(tokenizer);
		DataStruct::AssignmentExpression * assigment= new DataStruct::AssignmentExpression(left, right, a.val);
		return assigment;
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionLogOr(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionLogAnd(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && a.val=="||" )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionLogOr(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionLogAnd(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionBitOr(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;	
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && a.val=="&&" )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionBitOr(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionBitOr(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionBitXor(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;	
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && a.val=="|" )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionBitXor(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionBitXor(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionBitAnd(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && a.val=="^" )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionBitOr(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionBitAnd(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionEqal(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && a.val=="&" )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionEqal(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionEqal(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionRelation(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && ( a.val=="==" || a.val=="!=" ) )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionRelation(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionRelation(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionShift(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && ( a.val=="<" ||  a.val=="<=" || a.val==">" || a.val==">=" ) )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionShift(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionShift(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionAdd(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && ( a.val=="<<" || a.val==">>" || a.val==">>>" ) )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionAdd(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionAdd(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionMul(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && ( a.val=="+" || a.val=="-" ) )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionMul(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}

DataStruct::Expression* Parser::ExpressionMul(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionPow(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && ( a.val=="*" || a.val=="/" || a.val=="%" ) )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionPow(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;
}
DataStruct::Expression* Parser::ExpressionPow(Tokenizer &tokenizer)
{
	DataStruct::Expression* left = ExpressionCast(tokenizer);
	DataStruct::ArithmeticExpression* result = NULL;
	Token a = tokenizer.peekToken();
	while(a.type==Token::OPERATOR && a.val=="**" )
	{
		a=tokenizer.getToken();
		DataStruct::Expression* right = ExpressionCast(tokenizer);
		result=new DataStruct::ArithmeticExpression(left, right, a.val);
		left=result;
		a=tokenizer.peekToken();
	}
	return left;

}

DataStruct::Expression* Parser::ExpressionCast(Tokenizer &tokenizer)
{
	Token a = tokenizer.peekToken();
	if(a.type==Token::IDENTIFIER && Value::isTypename(a.val))
	{
		a = tokenizer.getToken();
		string typeName = a.val;
		a = tokenizer.getToken();
		if(a.val!="(")
			error.error( "( expected" );
		DataStruct::Expression* cast = new DataStruct::CastExpression(Expression(tokenizer), typeName);
		tokenizer.getToken();// )
		return cast;
	}
	return ExpressionUnary(tokenizer);
}

DataStruct::Expression* Parser::ExpressionUnary(Tokenizer &tokenizer)
{
	Token a=tokenizer.peekToken();
	if( a.type==Token::OPERATOR && ( a.val=="+" || a.val=="++" || a.val=="-" || a.val=="--" || a.val=="sizeof" || a.val=="!" || a.val=="~" ) )
	{
		a=tokenizer.getToken();
		DataStruct::UnaryExpression* unaryexpression = new DataStruct::UnaryExpression(ExpressionUnary(tokenizer),a.val);
		return unaryexpression;
	}
	else
		return ExpressionPostfix(tokenizer);
}

DataStruct::Expression* Parser::ExpressionPostfix(Tokenizer &tokenizer)
{
	DataStruct::Expression* expression=ExpressionPrimary(tokenizer);
	Token a=tokenizer.peekToken();
	while( a.type==Token::OPERATOR && ( a.val=="++" || a.val=="--" || a.val=="[") )
	{
		if(a.val=="++" || a.val=="--")
		{
			DataStruct::PostExpression* postfixexpression;
			a=tokenizer.getToken();
			if(a.val == "++")
				postfixexpression = new DataStruct::PostExpression(expression,a.val);
			else if(a.val == "--")
				postfixexpression = new DataStruct::PostExpression(expression,a.val);
			expression=postfixexpression;
		}
		else if(a.val == "[")
		{
			DataStruct::ArrayIndexExpression* accessexpression;
			a = tokenizer.getToken();
			DataStruct::Expression* key=Expression(tokenizer);
			a = tokenizer.getToken();
			if(a.val != "]")
				error.error("Expected ]");
			accessexpression = new DataStruct::ArrayIndexExpression(expression, key);
			expression = accessexpression;
		}
		a=tokenizer.peekToken();
	}
	return expression;
}

DataStruct::Expression* Parser::ExpressionPrimary(Tokenizer &tokenizer)
{
	Token a = tokenizer.getToken();
	if(a.type==Token::OPERATOR && a.val=="(")
	{
		DataStruct::Expression* expression = Expression(tokenizer);
		a = tokenizer.getToken();
		if( !(a.type==Token::OPERATOR && a.val==")"))
			error.error( "missing )" );
		return expression;
	}
	else if(a.type==Token::LITERAL)
	{
		DataStruct::LiteralExpression* lit = new DataStruct::LiteralExpression(a.val);
		return lit;
	}
	else if(a.type==Token::IDENTIFIER)
	{
		string id=a.val;
		a = tokenizer.peekToken();
		if(a.type == Token::OPERATOR && a.val=="(")//function
		{
			DataStruct::FunctionExpression* functexpression=new DataStruct::FunctionExpression(id);
			tokenizer.getToken();// (
			a = tokenizer.peekToken();
			if( !(a.type==Token::OPERATOR && a.val==")"))
			{
				functexpression->addParam(Expression(tokenizer));
				a = tokenizer.peekToken();
				while(a.val==",")
				{
					tokenizer.getToken();
					functexpression->addParam(Expression(tokenizer));
					a = tokenizer.peekToken();
				}
			}
			tokenizer.getToken();// )
			return functexpression;
		}
		else // varible
		{
			DataStruct::VarExpression* var=new DataStruct::VarExpression(id);
			return var;
		}
	}
	else
	{		
		error.error( "Cannot recognize expression: " + a.val );
		DataStruct::LiteralExpression* lit= new DataStruct::LiteralExpression("1");
		return lit;
	}
}

Value::Type Parser::TypeName(Tokenizer &tokenizer)
{
	Token a = tokenizer.getToken();
	Value::Type* type = new Value::Type();
	*type = Value::StrToType(a.val);	
	a = tokenizer.peekToken();
	while(a.val == "[")
	{
		tokenizer.getToken();
		a = tokenizer.getToken();
		if(a.val != "]")
			error.error("expected ]");
		Value::Type* arrayType = new Value::Type(Value::ARRAY);
		arrayType->arrayType =type;
		type = arrayType;
	}

	return *type;
}