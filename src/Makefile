CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

SRCS = reader.cpp generator.cpp Segment.cpp Chrom.cpp ChromPair.cpp Population.cpp Model.cpp AdmixModel.cpp

OBJS = reader.o generator.o Segment.o Chrom.o ChromPair.o Population.o Model.o AdmixModel.o

LIBS =

TARGET =	AdmixModel

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
