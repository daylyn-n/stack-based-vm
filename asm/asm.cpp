#include <iostream>
#include <fstream>
#include "lexer.h"

using ui32 = uint32_t;

using namespace std;

// functions
vector<ui32> compileToInstructions(string_ s);
bool isInteger(string s);
bool isPrimitive(string s);
ui32 mapToNumber(string s);

int main(int argc, char* argv[])
{
	// error checking
	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " <asm-filename>" << endl;
		exit(1);
	}
	// read input file
	ifstream infile;
	infile.open(argv[1]);
	if(!infile.is_open())
	{
		cout << "Error: could not read file: " << argv[1]  << endl;
		exit(1);
	}
	string line;
	string content;
	while(getline(infile, line))
	{
		content+= line + "\n";
	}
	infile.close();

	// parse the content into instruction
	Lexer lexer;
	string_ lexemes = lexer.lex(content);

	// compile to binary
	vector<ui32> instructions = compileToInstructions(lexemes);

	// write the instructions
	ofstream outfile;
	outfile.open("out.bin", ios::binary);
	for(ui32 i = 0; i < instructions.size(); i++)
		outfile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(ui32));
	outfile.close();
	return 0;

}

vector<ui32> compileToInstructions(string_ s)
{
	vector<ui32> instructions;
	for(ui32 i = 0; i < s.size() ;i++)
	{
		if(isInteger(s[i]))
		{
			instructions.push_back(stoi(s[i]));
		}
		else
		{
			ui32 instruction = mapToNumber(s[i]);
			if(instruction != -1) instructions.push_back(instruction);
			else cout << "Error: invalid instruction: " << s[i] << endl;
		}
	}
	instructions.push_back(0x40000000); // calls the STOP instruction at the end
	return instructions;
}

// helper functions for compiling to instructions
bool isInteger(string s)
{
	for(ui32 i = 0; i < s.length(); i++)
	{
		if(!isdigit(s[i])) return false;
	}
	return true;
}
ui32 mapToNumber(string s)
{
	if(s == "+") return 0x4000001;
	else if(s == "-") return 0x40000002;
	else if(s == "*") return 0x40000003;
	else if(s == "/") return 0x40000004;
	return -1;
}
