CXX=g++
CXXFLAGS =	-O3 -g -Wall -fmessage-length=0

SRCS = Segment.cpp Chrom.cpp ChromPair.cpp Population.cpp Model.cpp AdmixModel.cpp generator.cpp

OBJS = $(SRCS:.cpp=.o)

LIBS =

TARGET = AdmixModel

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET) reader generator

reader:	reader.cpp
	$(CXX) $(CXXFLAGS) -o reader reader.cpp
	
generator: generator.cpp
	$(CXX) $(CXXFLAGS) -o generator generator.cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) reader reader.o generator generator.o
