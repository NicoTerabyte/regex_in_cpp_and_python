#ifndef SPLIT_KEY_HPP
#define SPLIT_KEY_HPP

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <re2/re2.h>
#include <re2/stringpiece.h>

struct	t_match_data
{
	std::string	struct_var;
	std::string	index_var;
};


using namespace std;
// void	add_data(string &struct_var, string &index_var, vector<t_match_data> &detailed_matches);

// vector<unordered_map<string, string>> find_match_for_regex(string word_to_check, vector<regex> list_of_regex);

vector<t_match_data>	find_match_for_regex(string word_to_check);

#endif

