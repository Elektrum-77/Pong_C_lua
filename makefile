# # value for linux : make
# # value for windows : mingw32-make.exe
# MAKER = make
# # value for linux : rm
# # value for windows : dl
# RM = rm

PLATFORM = mingw

ifeq ($(OS), Windows_NT)
	MAKER = mingw32-make.exe
	CP = copy
	MV = move
	RM = del
	PATHSEP=\\
	ZIP = powershell Compress-Archive
else
	MAKER = make
	CP = cp
	MV = mv
	RM = rm
	PATHSEP=/
	ZIP = zip -9 -q
endif 

all : lua compiled_source love_file

lua :
	cd .$(PATHSEP)src$(PATHSEP)lua-5.1.5$(PATHSEP)src && $(MAKER) $(PLATFORM)

compiled_source :
	cd .$(PATHSEP)src && $(MAKER)
	$(CP) ".$(PATHSEP)src$(PATHSEP)main_c.*" .

love_file :
ifeq ($(OS), Windows_NT)
	$(RM) ".$(PATHSEP)main.lua"
	$(RM) ".$(PATHSEP)main_c.dll"
	$(RM) ".$(PATHSEP)lua51.dll"
	$(CP) ".$(PATHSEP)src$(PATHSEP)main.lua" .
	$(CP) ".$(PATHSEP)src$(PATHSEP)main_c.dll" .
	$(CP) ".$(PATHSEP)src$(PATHSEP)lua51.dll" .
else
	cd .$(PATHSEP)src && $(ZIP) Pong.love main.lua
	$(MV) ".$(PATHSEP)src$(PATHSEP)Pong.love" ".$(PATHSEP)Pong.love"
	.$(PATHSEP)love-11.4-x86_64.AppImage Pong.love
endif

clean :
	cd .$(PATHSEP)src$(PATHSEP)lua-5.1.5$(PATHSEP)src && $(MAKER) clean
	cd .$(PATHSEP)src && $(MAKER) clean
ifeq ($(OS), Windows_NT)
	$(RM) ".$(PATHSEP)main.lua"
	$(RM) ".$(PATHSEP)main_c.dll"
	$(RM) ".$(PATHSEP)lua51.dll"
	$(RM) ".$(PATHSEP)src$(PATHSEP)main_c.dll"
	$(RM) ".$(PATHSEP)src$(PATHSEP)lua51.dll"
else
	cd .$(PATHSEP)src && $(ZIP) Pong.love main.lua
	$(MV) ".$(PATHSEP)src$(PATHSEP)Pong.love" ".$(PATHSEP)Pong.love"
	.$(PATHSEP)love-11.4-x86_64.AppImage Pong.love
endif

.PHONY : clear all