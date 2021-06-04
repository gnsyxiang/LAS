






all:
	gcc -g -O2 -pg -ftest-coverage -fprofile-arcs gcov_test.c -lm -o gcov_test

clean:
	rm -f gcov_test
	rm -f gcov_test.c.gcov
	rm -f gcov_test.gcda
	rm -f gcov_test.gcno
	rm -f gmon.out
