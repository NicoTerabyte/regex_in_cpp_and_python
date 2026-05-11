# the header for the cython code

from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.unordered_map cimport unordered_map

cdef extern from "split_key.hpp":
	vector[unordered_map[string, string]] find_match_for_regex(string word_to_check)

