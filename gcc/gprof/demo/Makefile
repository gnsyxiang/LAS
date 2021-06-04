

TARGET := gprof_test
TARGET1 := bounce
TARGET2 := pro_sleep


all: $(TARGET) $(TARGET1) $(TARGET2)

$(TARGET):
	gcc -g -pg $(TARGET).c -lm -o $(TARGET)
	\
	./$(TARGET)
	gprof ./$(TARGET) | ./gprof2dot.py -n0 -e0 |dot -Tpng -o $(TARGET).png
	gprof -p -Q $(TARGET) gmon.out > $(TARGET)_profile.txt
	gprof -P -q $(TARGET) gmon.out > $(TARGET)_graph.txt

$(TARGET1):
	gcc -g -c $(TARGET1).c -pg
	gcc -o $(TARGET1) $(TARGET1).o -pg -lpthread
	gcc -shared -fPIC gprof-helper.c -o gprof-helper.so -lpthread -ldl
	\
	LD_PRELOAD=./gprof-helper.so ./$(TARGET1)
	gprof ./$(TARGET1) | ./gprof2dot.py -n0 -e0 | dot -Tpng -o $(TARGET1).png
	gprof -p -Q $(TARGET1) gmon.out > $(TARGET1)_profile.txt
	gprof -P -q $(TARGET1) gmon.out > $(TARGET1)_graph.txt

$(TARGET2):
	gcc -g -pg $(TARGET2).c -lc_p -o $(TARGET2)
	\
	./$(TARGET2)
	gprof ./$(TARGET2) | ./gprof2dot.py -n0 -e0 |dot -Tpng -o $(TARGET2).png
	gprof -p -Q $(TARGET2) gmon.out > $(TARGET2)_profile.txt
	gprof -P -q $(TARGET2) gmon.out > $(TARGET2)_graph.txt

clean:
	rm -f $(TARGET)
	rm -f $(TARGET1)
	rm -f gmon.out
	\
	rm -f *.o
	rm -f *.so
	rm -f *~
	rm -f *.txt
	rm -f *.png
