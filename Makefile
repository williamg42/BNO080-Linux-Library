
CXX = g++
CXXFLAGS = -Wall
OBJS = i2c.o BNO080.o PracticalSocket.o
TARGET = testmain
I2CSRC = I2C/src/I2C.cpp

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)
i2c.o: $(I2CSRC) 
	$(CXX) $(CXXFLAGS) -c -o $@ $^
BNO080.o: src/BNO080.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
PracticalSocket.o: src/PracticalSocket.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
$(TARGET).o: src/$(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
$(TARGET): $(OBJS) $(TARGET).o
	$(CXX) $(CXXFLAGS) -o $@ $^
