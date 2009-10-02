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
 version='0.2',
 ext_modules=[fx2_mod],
 scripts=['scripts/fx2load'],
 packages=['fx2load','fx2'],
 package_dir={'fx2':'cpp'}
)
