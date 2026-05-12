from setuptools import setup, Extension
from Cython.Build import cythonize

#defining the extension module

#you will use the name given to the extension in the python files
ext = Extension(
	name="my_wrapper",
	sources=["my_wrapper.pyx", "split_key.cpp"],
	language="c++",
	libraries=["re2"],
	library_dirs=["."],
)

setup(ext_modules=cythonize(ext))
