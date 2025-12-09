#include "lexer.h"

string_ Lexer::lex(std::string s)
{
	string_ strlst;
	char lexeme[256]; // buffer;
	int i = 0;
	int j = 0;
	State state = State::START;
	int done = 0;
	int len = s.length();
	int balance = 0;
	while(i < len)
	{
		switch(state)
		{
			case State::START:
				if(myIsSpace_(s[i])) state =State::SKIP;
				else if(isGroup_(s[i]))
				{
					if(s[i] == '"')
					{
						lexeme[j] = s[i];
						i++;
						j++;
					}
					state =State::READBLOCK;
				}
				else if(s[i] == '/' && s[i+ 1] == '/')
			       	{
					i+=2;
					state =State::COMMENT;
				}
				else state =State::READCHAR;
				break;
			case State::READCHAR:
				if(myIsSpace_(s[i]))state = State::DUMP;
				else if(s[i] == '\\')
				{
					i+=2;

				}
				else if(isGroup_(s[i]))
				{
					if(s[i] == '"')
					{
						lexeme[j] = s[i];
						j++;
						i++;
					}
					state = State::READBLOCK;
				}
				else if(isSpecial_(s[i]))
				{
					if(j==0)
					{
						lexeme[j] = s[i];
						j++;
						i++;
					}
					state = State::DUMP;
				}
				else if(s[i] == '/' && s[i + 1] == '/')
				{
					i+=2;
					state = State::COMMENT;
				}
				else
				{
					lexeme[j] = s[i];
					j++;
					i++;
				}
				break;
			case State::READBLOCK:
				if(s[i] == begChar_ && s[i] != '"')
				{
					balance++;
					lexeme[j] = s[i];
					j++;
					i++;
				}
				else if(s[i] == endChar_ )
				{
					balance--;
					lexeme[j] == s[i];
					j++;
					i++;
					if(balance <= 0) state = State::DUMP;
				}
				else if(endChar_ == '"' && s[i] == '\\')
				{
					i+=2;
					// TODO: Fix this to actualy record chars
				}
				else
				{
					lexeme[j] = s[i];
					j++;
					i++;
				}
				break;
			case State::SKIP:
				if(myIsSpace_(s[i])) i++;
				else state = State::READCHAR;
				break;
			case State::DUMP:
				if(j > 0)
				{
					lexeme[j] = 0;
					strlst.push_back(lexeme);
					j = 0;
				}
				state = State::START;
				break;
			case State::COMMENT:
				if(s[i] != '\n')i++;
				else state = State::READCHAR;
				break;
			case State::END:
				i = len;
				break;
		}
	}
	if(j > 0)
	{
		lexeme[j] = 0;
		strlst.push_back(lexeme);
	}
	return strlst;
}

// create the private bool functions
// define the white space function
bool Lexer::myIsSpace_(char c)
{
	switch(c)
	{
		case '\n':
		case '\r':
		case '\t':
		case '\v':
		case '\f':
		case ' ':
			return true;
		default:
			return false;
	}
}
			
bool Lexer::isSpecial_(char c)
{
	begChar_ = c;
	switch(c)
	{
		case '"':
			endChar_ = '"';
			return true;
		case '(':
			endChar_ = '(';
			return true;
		case ')':
			endChar_ = ')';
			return true;
		default:
			return false;
	}
}	

bool Lexer::isGroup_(char c)
{
	switch(c)
	{
		case '[':
		case ']':
			return true;
		default:
			return false;
	}
}

