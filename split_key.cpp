#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

#define REGEX_STRUCT = r(R'^(?P<struct>\w+)\.*');
#define REGEX_VECTOR = r(R'^(?P<struct>\w+)\.element\((?P<index>\d*?)\)\.*');
#define REGEX_ARRAY  = r(R'^(?P<struct>\w+)\((?P<index>\d*?)\)\.*');

void find_match_for_regex(string world_to_check)
{
	
}


int main(void)
{
	string string_for_regex = "member.submember(2).subsubmember.element(4).finalmember";

	cout<<"hello world"<<endl;
	return (0);
}



