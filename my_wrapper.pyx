# the implementer of the cython code

from my_wrapper cimport find_match_for_regex

def parse_string(string_to_check):
	# c++ works with bytes string, when using std::string
	byte_string = string_to_check.encode("utf-8")
	cdef list c_result = find_match_for_regex(byte_string)

	python_result = []
	for dictionary in c_result:
		retrieved_dict = {}
		for k, v in dictionary.items():
			retrieved_dict[k.decode("utf-8")] = v.decode("utf-8")
			python_result.append(retrieved_dict)

	return python_result
