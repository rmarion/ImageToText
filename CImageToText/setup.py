from distutils.core import setup, Extension

import os

os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"

cimagetotext = Extension('cimagetotext',
                         sources=['cimagetotext.cpp'
                                  ],
                         extra_compile_args=['-std=c++14']
                         )

setup(name='cimagetotext',
      version='0.1',
      description='Initial test package',
      ext_modules=[cimagetotext],
      )
