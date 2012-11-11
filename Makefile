LDLIBS  = -lglut -lGLU -lGL
OBJS    = Main.o
PROGRAM = a.out

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -W -Wall $(OBJS) $(LDLIBS) -o $(PROGRAM)


clean:;	rm -f $(OBJS) $(PROGRAM)
