#include "RawString.h"

int main(void) {

	String a("hello");
	String b(a);
	String c = a + b;
	String d("hella");

	bool z = (a == b);
	bool y = (a == c);
	bool x = (a == d);

	int length = a.Length();
	char* value = a.Value();

	return 0;
}