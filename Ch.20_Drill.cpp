#include "std_lib_facilities.h"

// for Q 6
template<typename Iter1, typename Iter2>
Iter2 my_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	// f1 is the first
	// e1 is the last
	// f2 is the result
	while (f1 != e1)
	{
		*f2 = *f1;
		++f1;
		++f2;
	}

	return f2;
}



int main()
{



	// Q 1
	//int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };         // the normal C++ array does not have iterators

	array<int, 10> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// Q 2
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// Q 3
	list<int> l{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


	// Q 4 copying

	array<int, 10> a2 = a;

	//int a2[10];
	/*for(int i=0; i<10; i++)
	int a2 [i] = a[i];*/

	vector<int> v2 = v;

	list<int> l2 = l;


	// Q 5 increasing

		/*for(int i=0; i<10; i++)
		cout << a[i+2] << ' ' << endl;*/

	for (int& i : a)
		i += 2;

	/*for(int i=0; i<v.size(); i++)
		i+=3
	*/
	for (int& i : v)
		i += 3;


	for (int& i : l)
		i += 5;



	// Q 7

	my_copy(a.begin(), a.end(), v2.begin());
	if (a[0] != v2[0])
		cout << "array and vector are not the same!" << endl;

	my_copy(l.begin(), l.end(), a2.begin());
	if (*(l.begin()) != a2[0])
		cout << "list and array are not the same!" << endl;


	// Q 8

		// using find in vector
	auto v_result = find(begin(v), end(v), 3);
	if (v_result != end(v))
		cout << "Found 3 in the vector and it's position is :  " << distance(v.begin(), v_result) << endl; // I used distance to find the index of the number
	else
		cout << " 3 Not Found in the vector" << endl;


	// using find in list
	auto l_result = find(begin(l), end(l), 27);
	if (l_result != end(l))
		cout << "Found 27 in the list and it's position is :  " << distance(l.begin(), l_result) << endl;
	else
		cout << "27 Not Found in the list" << endl;






	return 0;
}