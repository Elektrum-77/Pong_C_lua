# value for linux : make
# value for windows : mingw32-make.exe
MAKER = mingw32-make.exe
# value for linux : rm
# value for windows : dl
RM = del

FLAGS = -Wall
FPIC = -c -fpic

INCLUDE = "../Fireworks_C_Lua/lua-5.1.5/src"

LUADLL = ../Fireworks_C_Lua/lua-5.1.5/src/lua51.dll

OBJECT = ball.o field.o main.o
SRC = ball.o field.o main.o

all: $(SRC)
	gcc $(FLAGS) -shared -fpic $(LUADLL) $(OBJECT) -o main_c.dll
	$(RM) *.o

main.o : main.c
	gcc $(FLAGS) $(FPIC) -I$(INCLUDE) $<


%.o : %.c
	gcc $(FLAGS) $(FPIC) -O2 -I$(INCLUDE) $<
# gcc $(FLAGS) $(FPIC) -I$(INCLUDE) $<

clear:
	$(RM) *.o
	$(RM) main_c.dll

.PHONY : clear all