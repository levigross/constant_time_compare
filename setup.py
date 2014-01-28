from distutils.core import setup, Extension

ctc = Extension('constant_time_compare.src',
                sources=['src/constant_time_compare.c'], language='c')

setup(name='Constant Time Compare',
      version='1.0',
      description='This package includes a secure constant time comparison function written in C',
      author='Levi Gross',
      author_email='yriv@yrivtebff.pbz'.decode('rot13'),
      url="http://www.levigross.com/",
      ext_modules=[ctc])