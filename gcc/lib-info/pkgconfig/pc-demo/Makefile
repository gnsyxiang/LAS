





all:
	export PKG_CONFIG_PATH=./hello-dynamic/lib/ && \
	gcc hello-test.c `pkg-config --cflags --libs hello` -o main
