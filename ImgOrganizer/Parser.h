#pragma once
#include <string>
#include <set>
#include <filesystem>
#include <iostream>
 


class Parser {
	std::set<std::string> _args = { "-s" , "--similar" ,
		"-b", "--bit-exact",
		"-f", "--face", "--train-new-model", "--add-new-label", "--search-label",
		"-s", "--similar",
		"--search", "--people-count",
		"--orb"
	};
	std::set<std::string> _storing_args = { "--search", "--search-label", "--people-count" };
public:
	
	Parser(int argc, char** argv);
	std::string get_path();
	bool _valid_args();
	bool argExists(const std::string& option);
	char* getArg(const std::string& option);

private:
	char** _begin;
	int _size;

};




