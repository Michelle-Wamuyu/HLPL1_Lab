#include "std_lib_facilities.h"

// 3+4; 4-5; 2*3; 4/2;
const char number = '8';    
const char quit ='x';   //Change quit keyword from 'quit' to 'exit'(This caused errors)...Change Exit command from'q' to'x' 
const char print = '=';   
const char result = '='; //Change print command from ';' to '='
const char name = 'a';    
const char let = 'L'; 
const char sqrt_t = 's'; // Token for Square Root Function
const char pow_t = 'p';	// Token for Power Function
const string sqrt_s = "sqrt"; //Declaration keyword for Square Root Function
const string pow_s = "pow"; //Declaration keyword for Power Function
const string declkey = "#"; // Change Declaration keyword from 'Let' to '#'

double expression();
double term();
double primary();

class variable {
public:
	string name;
	double value;
};

vector<variable> var_table;

bool is_declared(string var)
{
	for (auto v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var)) error ("declared twice");
	var_table.push_back(variable{ var,val });
	return val;
}

double get_value(string val)
{
	for (auto v : var_table)
		if (v.name == val) return v.value;
	error("Variable not found");
}

void set_value(string var, double val)
{
	for (auto& v : var_table)
		if (v.name == var)
		{
			v.value = val;
			return;
		}
	error("Variable not defined");
}

class Token {
public:
    char kind;        
    double value;     
    string name;      
    Token(char ch)             : kind(ch), value(0)   {}
    Token(char ch, double val) : kind(ch), value(val) {}
    Token(char ch, string n)   : kind(ch), name(n)    {}
};

class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream(): full(false), buffer(0) {}

void Token_stream::putback(Token t) {
	if (full) error("Token_stream buffer is full");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	
	switch (ch) {
	case quit: //Change 'quit' to exit
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case 'pow': // power function
	case '==': // Changed to equivalency sign because the '=' sign is assigned as the print command
		return Token(ch);
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9': case '.':
	{
		cin.putback(ch);
		double val = 0;
		cin >> val;
		return Token( number , val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch; 
			cin.putback(ch);
			if (s == sqrt_s) return Token(sqrt_t); 
			if (s == declkey) return Token(let);
			if (s == pow_s) return Token(pow_t); 

			return Token(name, s);
		}
		error("Bad token");
	return 0;
	}
}


void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}

	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c ) return;
}

Token_stream ts;

void clean_up_mess()
{
	ts.ignore(print);
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("Variable name expected");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error ("= expected in declaration");

	double d = expression();
	define_name(var_name, d);
	return d;
}

// Square Root expression
double square_root()
{
	double d = expression(); 
	return sqrt(d);
}


double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	case pow_t: //Drill Question on Power Function
		return power_calculate();
	case sqrt_t: //Drill Question on Square Root Function
		return square_root();
	default:
		ts.putback(t);
		return expression();
	}
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	 case let:
        return declaration();
	case pow_t: //Drill Question
		return power_calculate();
	case sqrt_t: //Drill Question
		return square_root();
	default:
		ts.putback(t);
		return expression();
	}

}

void calculate()
{
	while (cin)
		try {
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;  //Drill Question 11 (Chapter 7)
		ts.putback(t);
		cout << result << statement() << endl;
	} catch (exception& e){
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	//Drill Question 4 and 5 (Chapter 6)
	cout << "Welcome to our simple calculator.\nPlease enter expression using floating-point numbers.\n";
	cout << "The calculator is able to compute simple arithmetic operations using the '+', '-', '/', '%', and '*' operators.\n ";
	cout << "The user is also able to assign values to variables, for example, 'Let x=9'\n ";
	cout << "To exit the program, type in 'x' and press enter\n";

	define_name("pi", 3.1415926535);

	define_name("k", 1000);//Drill question 6 (Chapter 7)
	
	calculate();

	return 0;
}catch(exception& e) {
	cerr << e.what() << endl;
	return 1;
}catch (...) {
	cerr << "some error\n";
	return 2;
}

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		Token t = ts.get();

		if (t.kind != ')') error(") expected!");

		return d;
	} // add a square root function here
	/*case "square_root":
		return "sqrt";*/
	case number:
		return t.value;
	case '-':
		return - primary();
	case '+':
		return primary();
	default:
		error("primary expected");
		return 0;
	}
}

double power_calculate() //create a Power Function
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case ',':
		{
			double base = expression();
			int exponent = narrow_cast<int>(left);
			return pow(left, base);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);        
			return left;
		}
	}
}

double term()
{
	double left = power_calculate();//Continuation of Power Function
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(term());
			if (i2 == 0) error("%: divide by zero");
			left = i1 % i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);        
			return left;
		}
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
			left /= primary(); // primary == 0?
			t = ts.get();
			break;
		case '%':
		{
			/*
			double d = primary();
			if (d == 0) error("Zero divider in %");
			left %= primary(); // % is not defined for double
			t = ts.get();
			break;
			*/
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error("Zero divider in %");
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;

		}
	}
}
double expression()
{
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;  //result


		}
	}

}
