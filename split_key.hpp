#ifndef SPLIT_KEY_HPP
#define SPLIT_KEY_HPP


#include <cstddef>
#include <iostream>
#include <ostream>
#include <regex>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_map>
#include <re2/re2.h>
#include <re2/stringpiece.h>

using namespace std;
void	build_dict(smatch found_match_array, vector<unordered_map<string, string>> &detailed_matches);
// vector<unordered_map<string, string>> find_match_for_regex(string word_to_check, vector<regex> list_of_regex);

vector<unordered_map<string, string>> find_match_for_regex(string word_to_check);

#endif

