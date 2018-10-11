#ifndef _RAW_STRING_
#define _RAW_STRING_

class String 
{
	char* string;
	int mem_alloc;

public:
	String();

	String(const char* string);

	String(const String &other);

	String(const String &a, const String &b);

	virtual ~String();

	String operator+ (const String other) const;

	bool operator== (const String &other) const;

	int Length() const;

	char* Value() const { return string; }

};


#endif // !_RAW_STRING_

