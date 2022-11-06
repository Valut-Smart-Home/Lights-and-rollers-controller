CFLAGS=-std=gnu++17 -I.
TARGET=test
SRCS=*/*.cc ../src/base/*.cc ../src/hwd_managment/*.cc ../src/inputRead/*.cc ../src/inputProcess/*.cc
GTESTLIB=-lgtest -lgtest_main
GTEST_OUTPUT="xml:/code/report.xml"

all:
	g++ ${CFLAGS} -o ${TARGET} ${SRCS} ${GTESTLIB}
	./${TARGET} --gtest_output=${GTEST_OUTPUT}
	rm ${TARGET}

sh:
	/bin/sh