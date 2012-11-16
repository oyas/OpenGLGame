LDLIBS  = -lglut -lGLU -lGL
OBJS    = Main.o assist.o
PROGRAM = a.out
LIBS_WIN      = -lopengl32 -lfreeglut -lglu32
PROGRAM_WIN   = a.exe

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -W -Wall $(OBJS) $(LDLIBS) -o $(PROGRAM)


win: $(PROGRAM_WIN)

$(PROGRAM_WIN): $(OBJS)
	$(CXX) -W -Wall $(OBJS) $(LIBS_WIN) $(WINR) -o $(PROGRAM_WIN)


clean:;	rm -f $(OBJS) $(PROGRAM)
