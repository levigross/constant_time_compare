from distutils.core import setup, Extension

ctc = Extension('constant_time_compare',
                sources=['src/constant_time_compare.c'], language='c')

setup(name='constant_time_compare',
      version='1.2',
      description='This package includes a secure constant time comparison function written in C',
      author='Levi Gross',
      author_email='yriv@yrivtebff.pbz'.decode('rot13'),
      url="https://github.com/levigross/constant_time_compare",
      platforms=['any'],
      ext_modules=[ctc])