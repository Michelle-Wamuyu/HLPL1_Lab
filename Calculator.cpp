#include "std_lib_facilities.h"

// 3+4; 4-5; 2*3; 4/2;

constexpr char number = '8'; //this is to show its number
constexpr char quit = 'x'; //we can't use x as a variable; this is exit command
constexpr char print = ';'; //we cant change the ; to an = since the = is already used under print later in the codefile!
constexpr char result = '=';
//constexpr char let = 'L';
constexpr char sq = 'S'; // Token for Square Root Function
constexpr char power = 'P'; // Token for Power Function
constexpr char name = 'a';
const string declkey = "#"; // Change Declaration keyword from 'Let' to '#'
const string squareroot = "sqrt";//Declaration keyword for Square Root Function
const string power_s = "pow"; //Declaration keyword for Power Function
const string quit_k = "exit"; //quit_k is the quit key 

double expression();
double term();
double primary();

class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;

bool is_declared(string var)
{
	for (auto v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var)) error("declared twice");
	var_table.push_back(Variable{ var,val });
	return val;
}

double get_value(string var)
{
	for (auto v : var_table)
		if (v.name == var) return v.value;
	error("Variable not found");
	return 0;
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
	Token() : kind(0) {}
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, string n) : kind(ch), name(n) {}
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

Token_stream::Token_stream() : full(false), buffer(0) {}

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
	case quit:
	case print:

	case '(':
	case ')':
	case '#':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ',':
	case '=':
		return Token(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5':
	case '6': case '7': case '8': case '9': case '.':
	{
		cin.putback(ch);
		double val = 0;
		cin >> val;
		return Token(number, val);
	}
	default:
	{
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.putback(ch);
			if (s == squareroot) return Token(sq);
			if (s == declkey) return Token('#');
			if (s == power_s) return Token(power);
			if (s == quit_k) return Token(quit);
			else if (is_declared(s))
				return Token(number, get_value(s));
			return Token(name, s);
		}

		error("Bad token");
		return 0;
	}
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
		if (ch == c) return;
}

Token_stream ts;

void clean_up_mess()
{
	ts.ignore(print);
}

double declaration() //decleration function
{
	Token t = ts.get();
	if (t.kind != name) error("variable name expected");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= expected in declaration");

	double d = expression();
	define_name(var_name, d);
	return d;
}

double square() //squareroot function
{

	double d = expression();
	if (d < 0)
		error("Entered number is negative!"); //catches neegative square root
	return sqrt(d);

}

double powerr() // power function
{
	Token t = ts.get();
	if (t.kind != '(') error(" ( is expected! "); // used to make sure there is an opening bracket
	double x = expression();
	Token t1 = ts.get();
	if (t1.kind != ',') error(" , is expected! ");// used to make sure there is a comma between both numbers
	double i = narrow_cast<int>(expression()); // makes second input an integer not a double
	Token t2 = ts.get();
	if (t2.kind != ')') error(" ) is expected! ");// used to make sure there is a closing bracket
	return pow(x, i);
}


double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '#':
		return declaration();
	case sq:
		return square();
	case power:
		return powerr();
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
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	cout << "Welcome to our simple Calculator. \nPlease enter expressions using floating-point numbers.\nThe calculator is able to compute simple arithmetic operations using the (,),%,/,*,-,+,=, sqrt(num), pow(num,num) . \nYou can print your calculation by entering a  ;.\nYou can also exit this calculator by entering an x or the word exit.\nPlease dont use x as an assignemt operator as its already used to quit the calculator. \n" << endl; // welcome message
	define_name("k", 1000); //Drill question 6 (Chapter 7) predefined k set to one-thousand
	define_name("pi", 3.1415926535);

	calculate();

	return 0;

}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Some error\n";
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
	}
	case number:
		return t.value;
	case '-':
		return -primary();
	case '+':
		return primary();

	default:
		error("primary expected");
		return 0;
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
			if (d==0) error("Zero divider in %");
			left = fmod(left, d);
			t = ts.get();
			break;
			*/
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error("Zero divider in %");
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
			return left;
		}
	}
}