from distutils.core import setup, Extension

fx2_mod = Extension (
 '_fx2',
 sources=['cpp/fx2.cpp', 'cpp/fx2.i'],
 swig_opts=['-c++'],
 include_dirs = ['/usr/include/python2.5'],
 libraries = ['usb-1.0']
)


setup(
 name='fx2',
 version='0.1',
 ext_modules=[fx2_mod],
 packages=['fx2load', 'fx2'],
 package_dir={'fx2load':'py','fx2':'cpp'}
)
