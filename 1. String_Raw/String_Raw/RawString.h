#ifndef _RAW_STRING_
#define _RAW_STRING_

class String 
{
public:
	String();

	String(const char* string);

	String(const String &other);

	String(const String &a, const String &b);

	virtual ~String();

	String & operator= (const char *string);

	String operator+ (const String other) const;

	bool operator== (const String &other) const;

	inline int Length() const;

	char* Value() const { return string; }

	void Clear();

private:
	char* string;
	unsigned int mem_alloc;

	static int InputLength(const char* string);

};

int String::Length() const {
	if (mem_alloc == 0) return 0;

	return mem_alloc-1;
}


#endif // !_RAW_STRING_

