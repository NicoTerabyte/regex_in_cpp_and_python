#include "split_key.hpp"

//! ?p<group> NON ESISTE IN C++


//TODO if possible, put this in .hpp
// OLD code
// const regex	REGEX_STRUCT = regex(R"(^(\w+)\.*)");
// const regex	REGEX_VECTOR = regex(R"(^(\w+)\.element\((\d*?)\)\.*)");
// const regex	REGEX_ARRAY = regex(R"(^(\w+)\((\d*?)\)\.*)");

const re2::RE2 REGEX_STRUCT(R"del(^(\w+)\.*)del");
const re2::RE2 REGEX_VECTOR(R"del(^(\w+)\.element\((\d*?)\)\.*)del");
const re2::RE2 REGEX_ARRAY(R"del(^(\w+)\((\d*?)\)\.*)del");

//ok
void	build_dict(string &struct_var, string &index_var, vector<unordered_map<string, string>> &detailed_matches)
{
	unordered_map<string, string>	tmp_val;
	//to redo with RE regex

	tmp_val.insert({"struct", struct_var});
	if (!index_var.empty())
		tmp_val.insert({"index", index_var});


	detailed_matches.push_back(tmp_val);
}


vector<unordered_map<string, string>> find_match_for_regex(string word_to_check)
{
	vector<unordered_map<string, string>>	detailed_matches;
	//? a special light string
	re2::StringPiece	tmp_world_check(word_to_check);

	try
	{

		// check if the string is empty
		while (!tmp_world_check.empty())
		{
			string	struct_var;
			string	index_var;
			// for clarity
			string	empty_index = "";
			if ((RE2::Consume(&tmp_world_check, REGEX_VECTOR, &struct_var, &index_var)))
			{
				cout<<"Found vector pattern"<<endl;
				build_dict(struct_var, index_var, detailed_matches);
			}
			else if ((RE2::Consume(&tmp_world_check, REGEX_ARRAY, &struct_var, &index_var)))
			{
				cout<<"Found array pattern"<<endl;
				build_dict(struct_var, index_var, detailed_matches);
			}
			else if ((RE2::Consume(&tmp_world_check, REGEX_STRUCT, &struct_var)))
			{
				cout<<"Found struct pattern"<<endl;
				build_dict(struct_var, empty_index, detailed_matches);
			}
			else
			{
				cout<<"no match found exiting"<<endl;
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


// int main(void)
// {
// 	string string_for_regex = "member.submember(2).subsubmember.element(4).finalmember";
// 	// vector<re2::RE2>	list_of_regex = {REGEX_VECTOR, REGEX_ARRAY, REGEX_STRUCT};
// 	vector<unordered_map<string, string>>	pattern_found;
// 	pattern_found = find_match_for_regex(string_for_regex);

// 	cout<<"retrieved data ["<<endl;
// 	for (size_t i = 0; i < pattern_found.size(); i++)
// 	{
// 		cout<<"of cell "<<i<<" i print this dict:\n{";
// 		for (auto it = pattern_found[i].begin(); it != pattern_found[i].end(); it++)
// 		{
// 			cout<<"first key: "<<it->first<<" value: \""<<it->second<<"\" ";
// 		}
// 		cout<<"}"<<endl;
// 	}
// 	cout<<"]"<<endl;
// 	return (0);
// }



