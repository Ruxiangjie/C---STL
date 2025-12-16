#define _CRT_SECURE_NO_WARNINGS 1
#include"String.h"
namespace rxj
{
	void test()
	{
		/*string s1("hello world");
		cout << s1.c_str() << endl;
		for (auto ch:s1)
		{
			cout << ch <<"";
		}
		cout << endl;
		string::iterator it1 =  s1.begin();
		while (it1 != s1.end())
		{
			cout << *it1 << "";
			it1++;
		}
		cout << endl;
		string s2("I miss you");
		string::const_iterator it2 = s2.begin();
		while (it2 != s2.end())
		{
			cout << *it2 << "";
			it2++;
		}
		cout << endl;
		s2.push_back(' ');
		s2.push_back('I');
		s2.push_back('d');
		s2.push_back('a');
		s2.push_back('D');
		s2.push_back('u');
		cout << s2.c_str() << endl;
		s2 += "I want to play with you";
		cout << s2.c_str() << endl;
		s2 += '\0';
		s2 += '\0';
		s2 += '!';
		cout << s2 << endl;
		s2 += "yyyyyyyyyyyyyyyyyy";
		cout << s2 << endl;
		s2.insert(0,'x');
		cout << s2 << endl;
		s2.insert(0,"hello world i'm right?");
		cout << s2 << endl;
		s1.find("headsome");
		string s3 = s2;*/
		string s1;
		string s2;
		s2.getline(cin,s2);
		cout << s2 << endl;


	}
}
int main()
{
	rxj::test();
	return 0;
}