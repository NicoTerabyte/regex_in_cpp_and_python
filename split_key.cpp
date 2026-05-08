#include "split_key.hpp"

//! ?p<group> NON ESISTE IN C++


//TODO if possible, put this in .hpp
const regex	REGEX_STRUCT = regex(R"(^(\w+)\.*)");
const regex	REGEX_VECTOR = regex(R"(^(\w+)\.element\((\d*?)\)\.*)");
const regex	REGEX_ARRAY = regex(R"(^(\w+)\((\d*?)\)\.*)");


void	build_dict(smatch found_match_array, vector<unordered_map<string, string>> &detailed_matches)
{
	unordered_map<string, string>	tmp_val;

	tmp_val.insert({"struct", found_match_array[1]});
	if (found_match_array.size() > 2)
		tmp_val.insert({"index", found_match_array[2]});

	detailed_matches.push_back(tmp_val);
}


vector<unordered_map<string, string>> find_match_for_regex(string world_to_check, vector<regex> list_of_regex)
{
	vector<unordered_map<string, string>>	detailed_matches;
	try
	{
		smatch	found;
		string	tmp_world_check = world_to_check;

		// check if the string is empty
		while (!tmp_world_check.empty())
		{
			bool	match_loop = false;

			for (size_t i = 0; i < list_of_regex.size(); i++)
			{
				if (regex_search(tmp_world_check, found, list_of_regex[i]))
				{
					cout<<"found full match with "<<found[0]<<" first element "<<found[1]<<endl;
					if (found.size() > 2)
						cout<<"it has an index"<<found[2]<<endl;
					build_dict(found, detailed_matches);
					tmp_world_check.erase(0, found[0].length());
					match_loop = true;
					break;
				}
			}
			if (match_loop != true)
			{
				cout<<"no match found from string: "<<tmp_world_check<<endl;
				break;
			}
		}
	}
	catch (const regex_error &error)
	{
		cout<<"something went wrong "<<error.what()<<endl;
	}
	return	(detailed_matches);
}


int main(void)
{
	string string_for_regex = "lacaca,member.submember(2).subsubmember.element(4).finalmember";
	vector<regex>	list_of_regex = {REGEX_VECTOR, REGEX_ARRAY, REGEX_STRUCT};
	vector<unordered_map<string, string>>	pattern_found;
	pattern_found = find_match_for_regex(string_for_regex, list_of_regex);

	cout<<"retrieved data ["<<endl;
	for (size_t i = 0; i < pattern_found.size(); i++)
	{
		cout<<"of cell "<<i<<" i print this dict:\n{";
		for (auto it = pattern_found[i].begin(); it != pattern_found[i].end(); it++)
		{
			cout<<"first key: "<<it->first<<" value: \""<<it->second<<"\" ";
		}
		cout<<"}"<<endl;
	}
	cout<<"]"<<endl;
	return (0);
}



