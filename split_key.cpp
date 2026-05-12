#include "split_key.hpp"
#include <vector>

//! ?p<group> NON ESISTE IN C++


//TODO if possible, put this in .hpp
// OLD code
// const regex	REGEX_STRUCT = regex(R"(^(\w+)\.*)");
// const regex	REGEX_VECTOR = regex(R"(^(\w+)\.element\((\d*?)\)\.*)");
// const regex	REGEX_ARRAY = regex(R"(^(\w+)\((\d*?)\)\.*)");

const re2::RE2 REGEX_STRUCT(R"del(^(\w+)\.*)del");
const re2::RE2 REGEX_VECTOR(R"del(^(\w+)\.element\((\d*?)\)\.*)del");
const re2::RE2 REGEX_ARRAY(R"del(^(\w+)\((\d*?)\)\.*)del");



vector<t_match_data>	find_match_for_regex(string word_to_check)
{
	vector<t_match_data>	detailed_matches;
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
				//cout<<"Found vector pattern"<<endl;
				detailed_matches.push_back({struct_var, index_var});
			}
			else if ((RE2::Consume(&tmp_world_check, REGEX_ARRAY, &struct_var, &index_var)))
			{
				//cout<<"Found array pattern"<<endl;
				detailed_matches.push_back({struct_var, index_var});

			}
			else if ((RE2::Consume(&tmp_world_check, REGEX_STRUCT, &struct_var)))
			{
				//cout<<"Found struct pattern"<<endl;
				detailed_matches.push_back({struct_var, ""});
			}
			else
			{
				//cout<<"no match found exiting"<<endl;
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
// 	vector<t_match_data>	pattern_found;
// 	pattern_found = find_match_for_regex(string_for_regex);

// 	cout<<"retrieved data ["<<endl;
// 	for (size_t i = 0; i < pattern_found.size(); i++)
// 	{
// 		cout<<"{";
// 		cout<<"struct: "<<pattern_found[i].struct_var<<"  ";
// 		if (!pattern_found[i].index_var.empty())
// 			cout<<"index: "<<pattern_found[i].index_var;
// 		cout<<"}"<<endl;
// 	}
// 	cout<<"]"<<endl;
// 	return (0);
// }



