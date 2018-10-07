#include "RawString.h"
#include <cstdlib>

String::String(const char* string) {
	mem_alloc = 0;
	while (*(string + mem_alloc) != 0) 
		++mem_alloc;

	this->string = (char*)std::malloc(sizeof(char) * (mem_alloc + 1));
	
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
	std::free(this->string);
}

String String::operator+ (const String other) const {
	String s(*this, other);
	return s;
}

bool String::operator== (const String &other) const {
	if (mem_alloc != other.mem_alloc) return false;

	for (unsigned int i = 0; i < mem_alloc; ++i)
	{
		if (*(string + i) != *(other.string + i)) return false;
	}

	return true;
}