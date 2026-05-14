# the implementer of the cython code

from my_wrapper cimport find_match_for_regex, t_match_data
from libcpp.vector cimport vector

cpdef list parse_string(str string_to_check):
	# c++ works with bytes string, when using std::string
	byte_string = string_to_check.encode("utf-8")
	cdef vector[t_match_data] c_result = find_match_for_regex(byte_string)

	python_result = []

	cdef t_match_data item
	for i in range(c_result.size()):
		item = c_result[i]
		tmp_dict = {"struct": item.struct_var.decode("utf-8")}

		if not item.index_var.empty():
			tmp_dict["index"] = item.index_var.decode("utf-8")
		python_result.append(tmp_dict)

	return python_result
