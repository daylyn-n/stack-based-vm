#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <cstdint>

using u8 = uint8_t;
using string_ = std::vector<std::string>;

enum class State : u8
{
	// lexer is a finite state machine
	START,
	READCHAR,
	READBLOCK,
	SKIP,
	DUMP,
	COMMENT,
	END
};

class Lexer
{
	private:
	bool myIsSpace_(char c);
	bool isSpecial_(char c);
	bool isGroup_(char c);
	char endChar_, begChar_;
	public:
	string_ lex (std::string s);	
};

#endif
