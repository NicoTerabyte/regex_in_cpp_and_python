# the header for the cython cod

from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "split_key.hpp":
	cdef cppclass t_match_data:
		string	struct_var
		string	index_var

cdef extern from "split_key.hpp":
	vector[t_match_data] find_match_for_regex(string word_to_check)

