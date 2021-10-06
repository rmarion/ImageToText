from distutils.core import setup, Extension

import os

os.environ["CC"] = "gcc"
os.environ["CXX"] = "gcc"

cimagetotext = Extension('cimagetotext',
                         sources=['cimagetotext.cpp',
                                  'ImageToTextConverter.cpp'
                                  ],
                         language='c++',
                         libraries=['Magick++'],
                         extra_compile_args=[
                             '-std=c++14',
                             '`Magick++-config --cxxflags --cppflags --ldflags --libs`'
                         ]
                         )

setup(name='cimagetotext',
      version='0.1',
      description='Initial test package',
      ext_modules=[cimagetotext],
      )
