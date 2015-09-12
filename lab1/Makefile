GSL_HOME=/opt/gsl/


CFLAGS = -I/$(GSL_HOME)/include/
LDFLAGS =  -L/$(GSL_HOME)/lib -lgsl -lgslcblas -lm 


OBJ= dokladnosc.o  interpolacja.o

all: dokladnosc  interpolacja

dokladnosc:dokladnosc.o
	$(CC) $(LDFLAGS) -o $@ $^


interpolacja:interpolacja.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o
