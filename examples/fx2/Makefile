OBJS=fx2.o fx2_wrap.o
LIBS = -lusb-1.0
CPPFLAGS=-fpic -g -I/usr/include/python2.5

all: _fx2.so

_fx2.so: $(OBJS) 
	g++ -shared fx2.o fx2_wrap.o $(LIBS) -o _fx2.so

fx2_wrap.o: fx2_wrap.cpp

fx2_wrap.cpp: fx2.i fx2.h
	swig -python -c++ -o fx2_wrap.cpp fx2.i
	

clean:
	rm *.o *.so fx2_wrap.cpp fx2.py *.pyc
