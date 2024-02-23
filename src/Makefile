CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
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
tests:

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
	clang-format -n -style=Google view/*.cc view/*.h viewer_controller/*.cc viewer_controller/*.h viewer_model/*.cc viewer_model/*.h

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full -q  -s --track-origins=yes ./tests
