CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
GCOV_FLAG = -fprofile-arcs -ftest-coverage -fPIC -O0
SOURCE_FILES = viewer_model/parser.cc viewer_model/transform.cc viewer_model/viewer_model.cc viewer_controller/viewer_controller.cc
TEST_FILES = ../tests/test.cc ../tests/test_amount.cc ../tests/test_parse.cc ../tests/test_transform.cc
TEST_FLAGS = -lgtest -pthread
LINUX_FLAG = -lm -lsubunit -lrt -lpthread
OPEN = open
GCOV_FLAG = -fprofile-arcs -ftest-coverage

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
	
.PHONY: clean
clean:
	-rm -rf *.o *.a *.out *.gcda *.gcno *.css *.tar.gz *.html
	-rm -rf test 3D_Viewer
	
.PHONY: style
style:
	clang-format -n -style=Google viewer_view/*.cc viewer_view/*.h viewer_controller/*.cc viewer_controller/*.h viewer_model/*.cc viewer_model/*.h

.PHONY: test
test:
	$(CC) $(CFLAGS) $(SOURCE_FILES) $(TEST_FILES) $(TEST_FLAGS) $(GCOV_FLAG) -o test
	./test

.PHONY: gcov_report
gcov_report: clean test
	gcovr -r . --html-details -o report_3d_viewer.html
	$(OPEN) report_3d_viewer.html

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full -q  -s --track-origins=yes ./test
