LDLIBS  = -lglut -lGLU -lGL
OBJS    = Main.o assist.o Stage1.o
PROGRAM = a.out

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -W -Wall $(OBJS) $(LDLIBS) -o $(PROGRAM)


clean:;	rm -f $(OBJS) $(PROGRAM)
