import re
import time

REGEX_STRUCT = r'^(?P<struct>\w+)\.*'
REGEX_VECTOR = r'^(?P<struct>\w+)\.element\((?P<index>\d*?)\)\.*'
REGEX_ARRAY  = r'^(?P<struct>\w+)\((?P<index>\d*?)\)\.*'

def regex_for_keys(string_to_check):
	REGEX_LIST = [REGEX_VECTOR, REGEX_ARRAY, REGEX_STRUCT]
	list_of_groups = []
	tmp_word_to_check = string_to_check
	limit_of_repetition = 0

	while tmp_word_to_check and limit_of_repetition < 3:
		tmp_word_to_check = tmp_word_to_check.lstrip('.')
		try:
			for regex_pattern in REGEX_LIST:
				found = re.search(pattern=regex_pattern, string=tmp_word_to_check)
				if found is not None:
					# print("something got found")
					list_of_groups.append(found.groupdict())
					tmp_word_to_check = tmp_word_to_check[found.end():]

					#i reset it so it won't break the while
					limit_of_repetition = 0
					break
				elif limit_of_repetition < 3: #? if one of th
					# print("nothing found next pattern")
					limit_of_repetition += 1

		except Exception as e:
			print("bad: {}".format(e))
	if limit_of_repetition > 100:
		print("too many tries done while checking for a pattern")
	return list_of_groups


if __name__ == "__main__":
	print("all good")
	string_for_regex = "member.submember(2).subsubmember.element(4).finalmember.secret_member(7)"

	start = time.time()
	i = 0
	while i < 1000:
		dict_of_patterns = regex_for_keys(string_for_regex)
		i+=1

	# time.sleep(1)
	end = time.time()
	print(dict_of_patterns)
	print("time of execution python: {}".format(end-start))
