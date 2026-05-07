#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <regex>
#include <stdio.h>
#include <string>
#include <regex>
#include <vector>

using namespace std;

//! ?p<group> NON ESISTE IN C++

// typedef struct s_regex_list
// {
		// const regex	REGEX_STRUCT = regex(R"(^(\w+)\.*)");
		// const regex	REGEX_VECTOR = regex(R"(^(\w+)\.element\((\d*?)\)\.*)");
		// const regex	REGEX_ARRAY = regex(R"(^(\w+)\((\d*?)\)\.*)");
// } t_regex_list;

const regex	REGEX_STRUCT = regex(R"(^(\w+)\.*)");
const regex	REGEX_VECTOR = regex(R"(^(\w+)\.element\((\d*?)\)\.*)");
const regex	REGEX_ARRAY = regex(R"(^(\w+)\((\d*?)\)\.*)");


void	print_regex_vals()
{
	//TODO
}

vector<string> find_match_for_regex(string world_to_check, vector<regex> list_of_regex)
{
	vector<string>	matches_vec;
	try
	{
		// t_regex_list	regex_types;

		//smatch servirà per avere i risultati dei match
		smatch	found;
		string	tmp_world_check = world_to_check;

		while (!tmp_world_check.empty())
		{
			for (size_t i = 0; i < list_of_regex.size(); i++)
			{
				if (regex_search(tmp_world_check, found, list_of_regex[i]))
				{
					cout<<"entrato"<<endl;
					matches_vec.push_back(found[1]);
					tmp_world_check.erase(0, found[0].length());
					cout<<"pattern found "<<matches_vec.back()<<endl;
					break;
				}
			}
		}
	}
	catch (const regex_error &error)
	{
		cout<<"something went wrong "<<error.what()<<endl;
	}
	return	(matches_vec);
}


int main(void)
{
	string string_for_regex = "member.submember(2).subsubmember.element(4).finalmember";
	vector<regex>	list_of_regex = {REGEX_VECTOR, REGEX_ARRAY, REGEX_STRUCT};
	vector<string>	pattern_found;
	cout<<"size of regex_list "<<list_of_regex.size()<<endl;
	pattern_found = find_match_for_regex(string_for_regex, list_of_regex);

	return (0);
}



