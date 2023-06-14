# IDIR =../include
# CC=gcc
# CFLAGS=-I$(IDIR)

# ODIR=obj
# LDIR =../lib

# LIBS=-lm

# _DEPS = hellomake.h
# DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# _OBJ = hellomake.o hellofunc.o 
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


# $(ODIR)/%.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# hellomake: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# .PHONY: clean

# clean:
# 	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

CC=g++
CFLAGS=-std=c++11 -Wall -Wextra
LDFLAGS=

TARGET = testDevice

$(TARGET): testDevice.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) testDevice.cpp

clean:
	rm -f $(TARGET)

