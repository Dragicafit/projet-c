CC = gcc
CFLAGS = -Wall -g -std=c11 -m64
LDLIBS = -lm
ALL = main
MAINS = $(addsuffix .o, $(ALL))
OBJ = projet2019.o $(MAINS)
DEPS = projet2019.h

all : $(ALL)

clean:
	rm -f $(ALL) $(OBJ)

$(OBJ): %.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ALL): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $(LIBS) $^ $(CFLAGS) $(LDFLAGS)