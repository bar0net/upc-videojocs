#include "RawString.h"

int main(void) {

	String a("hello");
	String b(a);
	String c = a + b;
	String d("hella");
	String e;
	String f = d + e;

	bool z = (a == b);
	bool y = (a == c);
	bool x = (a == d);

	int length = a.Length();
	char* value = a.Value();

	return 0;
}