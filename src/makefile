# # value for linux : make
# # value for windows : mingw32-make.exe
# MAKER = mingw32-make.exe
# # value for linux : rm
# # value for windows : dl
# RM = rm
# # value for linux : so
# # value for windows : dll
# SHAREDEXTENSIONS = so

FLAGS = -Wall
FPIC = -c -fpic

INCLUDE = "lua-5.1.5/src"

OBJECT = main.o ball.o pad.o score.o goal.o game.o
SRC = main.o ball/ball.o pad/pad.o score/score.o goal/goal.o game/game.o

ifeq ($(OS), Windows_NT)
	MAKER = mingw32-make.exe
	RM = del
	SHAREDEXTENSIONS = dll
	LUADLL = lua51.dll
else
	MAKER = make
	RM = rm
	SHAREDEXTENSIONS = so
	LUADLL=
endif 

all: $(SRC)
	gcc $(FLAGS) -shared -fpic $(LUADLL) $(OBJECT) -o main_c.$(SHAREDEXTENSIONS)

main.o : main.c
	gcc $(FLAGS) $(FPIC) -I$(INCLUDE) $<


%.o : %.c
	gcc $(FLAGS) $(FPIC) -O2 -I$(INCLUDE) $<
# gcc $(FLAGS) $(FPIC) -I$(INCLUDE) $<

clean:
	$(RM) *.o
	$(RM) main_c.dll

.PHONY : clean all