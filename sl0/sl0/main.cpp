#include "stdafx.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "Program.h"
#include "Error.h"
/*
	TO DO

	obsluga blêdów z numerem linii
	tablice
	klasy (rekordy) (class|public|protected|private|static|synchronized|extends|super|final)
	ciagi znakow
	obsluga plikow
	obsluga zewnetrznych modu³ów
	funkcje matematyczne
	obsluga wyj¹tkow (try|throw|catch|finally)
*/

/**
 * @mainpage
 * Interpreter jêzyka SL/0 (Script Language 0).
 * Jêzyk SL/0 jest zaprojektowany jako prosty jêzyk, czêœciowo zgodny z
 * pochodz¹cym z gry CoLoBoT jêzykiem C-BOT; zbli¿ony sk³adni¹ do C++.
 * 
 * Przyk³adowe programy:
  @code
extern void Main()
{
	int i=0,max;
	float suma,num;
	input(max);
	suma=0;
	while(i<max)
	{
		input(num);
		suma+=num;
		++i;
	}
	message(suma/max);
}
------------------
extern void Main()
{
	//algorytm eukulidesa
	int a,b;
	if(rand() % 2 == 0)
	{
	//przez reszte z dzielenia
		int tmp;
		input(a,b);
		while (b != 0)
		{
			tmp = a % b;
			a = b;
			b = tmp;
		}
	}
	else
	{
	//przez odejmowanie odcinkow
		input(a,b);
		while (a != b)
		{
			if( a > b )
				a -= b;
			else
				b -= a;
		}
	}
	message(a);
}
@endcode

 */
int _tmain(int argc, _TCHAR* argv[])
{
	srand ( static_cast<unsigned int>(time(NULL)) );
	cout << "==SL/0==" << endl;

	string line("");
	string wholeCode("");

	while(!cin.eof())
	{
		getline(cin,line);
		wholeCode += line + "\n";
	}
	cin.clear();

	Tokenizer tokzer(wholeCode);
	
	/*Token a;
	a=tokzer.getToken();
	string typeName[]={	"IDENTIFIER ",
						"KEYWORD    ",
						"OPERATOR   ",
						"LITERAL    ",
						"ERROR      "};
	while(a.type!=Token::ERROR)
	{
		cout << typeName[a.type] << a.val << endl;
		a=tokzer.getToken();
	}//*/
	error.bindTokenizer(&tokzer);
	DataStruct::Program* program = Parser::Program(tokzer);
	error.bindTokenizer(NULL);
	//program->debug();
	cout << "+==================================+" << endl;
	program->Exec();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush cin
	cin.get();
	return 0;
}
