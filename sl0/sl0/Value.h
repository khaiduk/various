#pragma once
#include "stdafx.h"
#include "Error.h"

/**
 * Wartoœci.
 * Przestrzeñ nazw zawieraj¹ca struktury reprezentuj¹ce wartoœci - liczby,
 * znak, itp.
 */
namespace Value
{
	/// Typ wartoœci
	enum SimpleType { INT, BOOL, FLOAT, CHAR, ARRAY, ERROR };

	bool isTypename(string s);

	/// Typ wartoœci
	class Type
	{
	public:
		SimpleType t;
		Type* arrayType;
		Type():t(ERROR),arrayType(NULL){}
		Type(SimpleType type):t(type),arrayType(NULL){}
		bool operator==(const Type &other) const
		{
			return this->t == other.t;
		}
		bool operator==(const SimpleType &other) const
		{
			return this->t == other;
		}
		bool operator!=(const Type &other) const
		{
			return !(*this == other);
		}
		bool operator!=(const SimpleType &other) const
		{
			return !(*this == other);
		}
		friend ostream& operator<<(ostream & stream, Type& type)
		{
			switch(type.t)
			{
			case BOOL: stream << "BOOL"; break;
			case CHAR: stream << "CHAR"; break;
			case FLOAT:stream << "FLOAT"; break;
			case INT: stream << "INT"; break;
			case ARRAY:stream << "ARRAY OF " << *type.arrayType; break;
			default: stream << "#";
			}
			return stream;
		}
		static Type arrayOf(Type t)
		{
			Type type;
			type.t = ARRAY;
			type.arrayType = new Type;
			*type.arrayType = t;
			return type;
		}
	};

	Type StrToType(string s);

	/// Reprezentacja wartoœci
	class Value
	{
	public:
		/// Typ wartoœci
		Type type;
		/// Wartoœæ
		boost::any val;
		
		/**
		 * Konstruktor wartoœci.
		 * Domyœlnie zak³adam ¿e je¿eli nie uda siê rozpoznaæ wartoœci, to jest ona b³êdna (Value::ERROR).
		 */
		Value()
		{
			type=ERROR;
			val=0;
		}

		/**
		 * Konstruktor wartoœci w oparciu o typ.
		 * @param typ Typ wartoœci
		 */
		Value(Type typ)
		{
			type=typ;
			val=0;
			if(type == BOOL) val = bool(false);
			else if(type == CHAR) val = char(' ');
			else if(type == FLOAT) val = float(0.0);
			else if(type == INT) val = int(0);
			else if(type == ARRAY)
			{
				vector< Value* > arr;
				val = arr;
			}
			else val=0;
		}
		
		/**
		 * Konstruktor wartoœci w oparciu o ci¹g znaków.
		 * @param s Ci¹g z litera³em wartoœci
		 */
		Value(string s)
		{
			if(s[0]=='\'')
			{
				type = CHAR;
				val = s[1];
			}
			else if(s[0]=='"')
			{
				type = Type::arrayOf(CHAR);
				vector < Value* > arr;
				int siz = s.size()-1;
				for(int i=1;i<siz;i++)
				{
					Value* elem = new Value;
					elem->type = CHAR;
					elem->val = s[i];
					arr.push_back(elem);
				}
				val = arr;
			}
			else if(s=="true" || s=="false")
			{
				type = BOOL;
				val=bool(s=="true");
			}
			else if(s.find('.')!=string::npos)
			{
				type = FLOAT;
				val=boost::lexical_cast<float>(s);
			}
			else
			{
				type = INT;
				val=boost::lexical_cast<int>(s);
			}
		}

		///@{
		/// Pobiera wartoœc odpowiedniego typu, ewentualnie dokonuj¹c rzutowania
		int getInt(){
			if(type == INT)			return static_cast<int>(boost::any_cast<int>  (val));
			else if(type == BOOL)	return static_cast<int>(boost::any_cast<bool> (val));
			else if(type == FLOAT)	return static_cast<int>(boost::any_cast<float>(val));
			else if(type == CHAR)	return static_cast<int>(boost::any_cast<char> (val));
			else return 0;
		}
		bool getBool(){
			if(type == INT)			return static_cast<bool>(boost::any_cast<int>  (val)!=0);
			else if(type == BOOL)	return static_cast<bool>(boost::any_cast<bool> (val));
			else if(type == FLOAT)	return static_cast<bool>(boost::any_cast<float>(val)!=0.0);
			else if(type == CHAR)	return static_cast<bool>(boost::any_cast<char> (val)!='\0');
			else return false;
		}
		char getChar(){
			if(type == INT)			return static_cast<char>(boost::any_cast<int>  (val));
			else if(type == BOOL)	return static_cast<char>(boost::any_cast<bool> (val));
			else if(type == FLOAT)	return static_cast<char>(boost::any_cast<float>(val));
			else if(type == CHAR)	return static_cast<char>(boost::any_cast<char> (val));
			else return '\0';
		}
		float getFloat(){
			if(type == INT)			return static_cast<float>(boost::any_cast<int>  (val));
			else if(type == BOOL)	return static_cast<float>(boost::any_cast<bool> (val));
			else if(type == FLOAT)	return static_cast<float>(boost::any_cast<float>(val));
			else if(type == CHAR)	return static_cast<float>(boost::any_cast<char> (val));
			else return 0.0;
		}
		///@}

		/**
		 * Rzutuje wartoœæ na dany typ
		 * @param tgtType Typ docelowy
		 */

		Value cast(Type tgtType)
		{
			if(tgtType==INT)
			{
				val = getInt();
				type=INT;
			}
			else if(tgtType==BOOL)
			{
				val = getBool();
				type=BOOL;
			}
			else if(tgtType==CHAR)
			{
				val = getChar();
				type=CHAR;
			}
			else if(tgtType==FLOAT)
			{
				val = getFloat();
				type=FLOAT;
			}
			return *this;
		}
	
		friend ostream& operator<<(ostream & stream, Value& val)
		{
			if(val.type == BOOL)		stream << val.getBool();
			else if(val.type == CHAR)	stream << val.getChar();
			else if(val.type == FLOAT)	stream << val.getFloat();
			else if(val.type == INT)	stream << val.getInt();
			else if(val.type == ARRAY)
			{
				vector<Value*> arr = boost::any_cast< vector<Value*> >(val.val);
				for(unsigned int i=0;i<arr.size();i++)
					stream << *arr[i];
			}
			else stream << "???";
		return stream;
		}
	};
	
	/**
	 * Wykonuje dan¹ operacjê na dwóch wartoœciach.
	 * @param opName Nazwa operatora (np. "*", "&&")
	 * @param a Pierwsza wartoœæ
	 * @param b Druga wartoœæ
	 * @return Wynik dzia³ania; w przypadku niepowodzenia wartoœæ b³êdna (Value::ERROR)
	 */
	Value op(string opName, Value a, Value b);
	
	/**
	 * Wykonuje dan¹ operacjê na pojedynczej wartoœciach.
	 * @param opName Nazwa operatora (np. "!", "~")
	 * @param a Wartoœæ
	 * @return Wynik dzia³ania; w przypadku niepowodzenia wartoœæ b³êdna (Value::ERROR)
	 */
	Value op(string opName, Value a);
	
	/**
	 * Sprawdza zgodnoœæ typów.
	 * @param opName Nazwa operatora (np. "*", "&&")
	 * @param a Typ pierwszej wartoœci
	 * @param b Typ drugiej wartoœci
	 * @return Typ wyniku dzia³ania; w przypadku niepowodzenia typ b³êdny (Value::ERROR)
	 */
	Type checkTypes(string opName, Type a, Type b);

	/**
	 * Sprawdza zgodnoœæ typów.
	 * @param opName Nazwa operatora (np. "~", "!")
	 * @param a Typ wartoœci
	 * @return Typ wyniku dzia³ania; w przypadku niepowodzenia typ b³êdny (Value::ERROR)
	 */
	Type checkTypes(string opName, Type a);
}