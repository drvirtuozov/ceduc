build:
		clang --std=c11 -I$(CPATH) main.c $(CPATH)/ceduc/util/fmt.c \
			$(CPATH)/ceduc/util/sort.c $(CPATH)/ceduc/sort/bubble.c $(CPATH)/ceduc/data/dynarr.c