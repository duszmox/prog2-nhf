
PROG = main
PROG_O = $(PROG).o szo.o betu.o menu.o gameMenu.o statsMenu.o match.o # program object fajljai

# Rajzatablas valtozathoz torolje a kommentet a kovetkezo sorbol
PROG_H = szo.h betu.h menu.h statsMenu.h gameMenu.h match.h # program header fajljai

# Rajzatablas valtozathoz torolje a kommentet a kovetkezo sorbol

PROG_L =              # program libjei
MTRACE_O = memtrace.o # memtrace object fajl
MTRACE_H = memtrace.h # memtrace header fajlja

CXX = clang++ # a C fordito neve

#fordítasi opciok
CXXFLAGS = -pedantic -Wall -DMEMTRACE -Dnullptr=0 
CXXFLAGS += -g # es legyeb debug info is
LDFLAGS = -g # debug a linkelesnel is kell

# osszes object, osszes header osszes lib egyutt
OBJS = $(PROG_O) $(MTRACE_O)
HEADS = $(PROG_H) $(MTRACE_H)
LIBS = $(PROG_L) $(MEMCHK_L)

# Alapertelmezett cel 
.PHONY: all
all: $(PROG)

# Eloallitjuk az objektekbol a PROG-ot
$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

# Feltetelezzuk, hogy az osszes obj fugg az osszes headertol, ami nem feltetlenul igaz
$(OBJS): $(HEADS)

# Futtatas
.PHONY: run
run: $(PROG)
	./$(PROG)

# takaritas igeny szerint
.PHONY: clean
clean:
	rm -f $(OBJS) $(PROG)

faszom: 
	make clean
	make
	make run

