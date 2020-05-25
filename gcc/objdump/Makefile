



all:
	gcc -g -Wstrict-prototypes -Wall -Wunused -o test test.c

objdump:
	objdump -j .text -d -Sl test > objdump-test.S
	objdump -j .text -d -Sl test --prefix-addresses > objdump-test_1.S

clean:
	rm -rf test *.S
