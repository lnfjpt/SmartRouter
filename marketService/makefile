CXX=g++
CXXFLAGS=-g -Wall -std=c++11 -pthread
LDFLAGS=
BUILDDIR=build
TARGET=bin
EXE=sort
SRCEXT=cpp
SRCDIR=src
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LIB=
INC=-I include

all:	$(TARGET)
	mv $(EXE) $(TARGET)/$(EXE)

$(TARGET):	$(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXE) $(LIB)

$(BUILDDIR)/%.o:	$(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)

	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
	
clean:
		rm -rf $(BUILDDIR)/*
		rm -rf $(TARGET)/*
		rm -rf *stackdump*

debug:	
	echo "Sources: $(SOURCES) "
	echo "Objects: $(OBJECTS)"
	echo "Target:  $(TARGET)"
	echo "Buil Dir: $(BUILDDIR)"
