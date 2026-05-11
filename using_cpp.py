# importing the cython code we made
import my_wrapper

string_to_check = "member.submember(2).subsubmember.element(4).finalmember.secret_member(7)"

print("using C++ code to get results")
parsed_data = my_wrapper.parse	_string(string_to_check)

print("retrieved data {}".format(parsed_data))
