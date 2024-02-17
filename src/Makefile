CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOV_FLAG = -fprofile-arcs -ftest-coverage -fPIC -O0
GCOV_FLAG_TEST = --coverage
TEST_FLAG = -lcheck
LINUX_FLAG = -lm -lsubunit -lrt -lpthread
OPEN = open

ifeq ($(shell uname), Linux)
	TEST_FLAG += $(LINUX_FLAG)
endif

ifeq ($(shell uname), Linux)
	OPEN = xdg-open
endif

SOURCES_1 = core/parser.c core/transform.c
OBJECTS_1 = parser.o transform.o
SOURCES_2 = test/test.c
OBJECTS_2 = test.o

.PHONY: all
all: clean install gcov_report

.PHONY: install
install: clean
	mkdir build
	cd build; cmake ../
	cd build; make
	cd ..
	mv build/3D_Viewer .
	rm -R build
	./3D_Viewer

.PHONY: uninstall
uninstall: 
	-rm -rf 3D_Viewer

.PHONY: dvi
dvi:
	$(OPEN) instruction/docs.html

.PHONY: dist
dist: 
	-rm -rf 3D_Viewer.tar.gz
	tar -czvf 3D_Viewer.tar.gz 3D_Viewer

.PHONY: tests
tests: clean 
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(SOURCES_1) -lm
	$(CC) $(CFLAGS) -c $(SOURCES_2)
	$(CC) $(CFLAGS) $(GCOV_FLAG_TEST) -o tests $(OBJECTS_1) $(OBJECTS_2) $(TEST_FLAG)
	-rm -rf *.o
	./tests

.PHONY: gcov_report
gcov_report: clean tests
	gcovr -r . --html-details -o report_3d_viewer.html
	$(OPEN) report_3d_viewer.html
	
.PHONY: clean
clean:
	-rm -rf *.o *.a *.out *.gcda *.gcno *.css *.tar.gz *.html
	-rm -rf tests 3D_Viewer
	
.PHONY: style
style:
	clang-format -n -style=Google core/*.c core/*.h view/*.cpp view/*.h

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full -q  -s --track-origins=yes ./tests
