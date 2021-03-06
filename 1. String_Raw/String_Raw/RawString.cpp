#include "RawString.h"
#include <cstdlib>

String::String() : String("")
{ }

String::String(const char* string) {
	mem_alloc = InputLength(string);
	this->string = (char*)std::malloc(sizeof(char) * (mem_alloc + 1));
	
	// Copy all memory positions. Add 1 to 'mem_alloc' to account for
	// 00 position that determines the end of the string
	for (unsigned int i = 0; i < mem_alloc; i++) 
		*(this->string + i) = *(string + i);
	*(this->string + mem_alloc) = 0;
	++mem_alloc;
}

String::String(const String &other) {
	mem_alloc = (&other)->mem_alloc;
	this->string = (char*)std::malloc(sizeof(char) * mem_alloc);

	for (unsigned int i = 0; i < mem_alloc; ++i)
		*(this->string + i) = *((&other)->string + i);
}

String::String(const String &a, const String &b) {
	mem_alloc = a.mem_alloc + b.mem_alloc - 1;
	this->string = (char*)std::malloc(sizeof(char) * mem_alloc);

	unsigned int i = 0;
	for (; i < a.mem_alloc - 1; ++i)
		*(this->string + i) = *(a.string + i);

	for (unsigned int j = 0; j < b.mem_alloc; ++j) {
		*(this->string + i) = *(b.string + j);
		++i;
	}
}

String::~String() {
	if (string != nullptr) std::free(this->string);
}


String & String::operator= (const char *string) {
	if (this->string != nullptr) std::free(this->string);
	
	mem_alloc = InputLength(string);
	this->string = (char*)std::malloc(sizeof(char) * (mem_alloc + 1));

	for (unsigned int i = 0; i < mem_alloc; i++)
		*(this->string + i) = *(string + i);
	*(this->string + mem_alloc) = 0;
	++mem_alloc;

	return *this;
}

String String::operator+ (const String &other) const {
	return String(*this, other);
}

bool String::operator== (const String &other) const {
	if (mem_alloc != other.mem_alloc) return false;

	for (unsigned int i = 0; i < mem_alloc; ++i)
	{
		if (*(string + i) != *(other.string + i)) return false;
	}

	return true;
}

void String::Clear() {
	if (string != nullptr) std::free(this->string);

	mem_alloc = 1;
	this->string = (char*)std::malloc(sizeof(char));
	*(this->string) = 0;
}

int String::InputLength(const char* string) {
	int len = 0;
	while (*(string + len) != 0)
		++len;
	return len;
}