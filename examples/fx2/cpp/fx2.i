/* interface file for python/swig */
%module fx2
//%include "typemaps.i"
%include "cdata.i"
%apply (char* STRING, int LENGTH)  { (char* buf, int size) }

%{
#include "fx2.h"
%}

%include "fx2.h"
