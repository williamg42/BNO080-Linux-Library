
CXX = g++
CXXFLAGS = -Wall
OBJS = i2c.o BNO080.o PracticalSocket.o
TARGET = testmain
I2CSRC = I2C/src/I2C.cpp

i2c.o: $(I2CSRC) 
	$(CXX) $(CXXFLAGS) -c -o $@ $^
src/%.o: src/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^
$(TARGET.o): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
$(TARGET): $(OBJS) $(TARGET).o
	$(CXX) $(CXXFLAGS) -o $@ $^
