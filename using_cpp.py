# importing the cython code we made
import my_wrapper
import time

string_to_check = "member.submember(2).subsubmember.element(4).finalmember.secret_member(7)"


i = 0
print("using C++ code to get results")


start = time.time()
while i < 1000:
	parsed_data = my_wrapper.parse_string(string_to_check)
	i+=1
# time.sleep(1)
end = time.time()

print("retrieved data {}".format(parsed_data))
print("time of execution c++: {}".format(end-start))
