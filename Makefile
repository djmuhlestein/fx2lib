



.PHONY: all docs

all:
	make -C lib

docs:
	doxygen docs/docs.conf

