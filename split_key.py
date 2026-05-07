import re


REGEX_STRUCT = r'^(?P<struct>\w+)\.*'
REGEX_VECTOR = r'^(?P<struct>\w+)\.element\((?P<index>\d*?)\)\.*'
REGEX_ARRAY  = r'^(?P<struct>\w+)\((?P<index>\d*?)\)\.*'

def regex_for_keys(string_to_check):
	REGEX_LIST = [REGEX_VECTOR, REGEX_ARRAY, REGEX_STRUCT]
	list_of_groups = []
	word_to_check = string_to_check

	while word_to_check:
		word_to_check = word_to_check.lstrip('.')
		try:
			for regex_pattern in REGEX_LIST:
				found = re.match(pattern=regex_pattern, string=word_to_check)
				if found is not None:
					print("something got found")
					list_of_groups.append(found.groupdict())
					word_to_check = word_to_check[found.end():]
					break
				else:
					print("nothing found next pattern")
		except Exception as e:
			print("bad: {}".format(e))
	return list_of_groups


if __name__ == "__main__":
	print("all good")
	string_for_regex = "member.submember(2).subsubmember.element(4).finalmember"
	dict_of_patterns = regex_for_keys(string_for_regex)
	print(dict_of_patterns)
