build:
		clang --std=c11 -g -I$(CPATH) main.c $(CPATH)/ceduc/util/*.c $(CPATH)/ceduc/sort/*.c $(CPATH)/ceduc/data/*.c