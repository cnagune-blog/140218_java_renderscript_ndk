include Makefile.common

###########################################################
# Rules
###########################################################
all: dir_check
	make -C src all

clean: test.clean
	make -C src clean

check: test

test: all test.test

test.test: test.all
	make -C test/unittest test

test.all:
	make -C test/unittest all

test.clean:
	make -C test/unittest clean

