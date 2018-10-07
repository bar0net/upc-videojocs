#ifndef _RAW_STRING_
#define _RAW_STRING_

class String 
{
	char* string;
	int mem_alloc;

public:
	String(const char* string);

	String(const String &other);

	String(const String &a, const String &b);

	~String();

	String operator+ (const String other) const;

	bool operator== (const String &other) const;

	int Length() {	return mem_alloc - 1; }

	char* Value() { return string; }

};


#endif // !_RAW_STRING_

