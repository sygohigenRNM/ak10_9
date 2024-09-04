CC = gcc
CPP = g++
CPPFLAGS = -Wall -Wextra -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/cpputest_build/lib -lCppUTest -lCppUTestExt

CAN_DIR = can
CAN_SRCS = $(CAN_DIR)/src/socketCAN.c
CPPFLAGS += -I$(CAN_DIR)/include

CONTROLLER_DIR = Tmotor/Controller
CONTROLLER_SRCS = $(CONTROLLER_DIR)/src/TmotorController.c
CPPFLAGS += -I$(CONTROLLER_DIR)/include

COMMUNICATION_DIR = Tmotor/Communication
COMMUNICATION_SRCS = $(COMMUNICATION_DIR)/src/TmotorCAN.c
CPPFLAGS += -I$(COMMUNICATION_DIR)/include

MOCKS_DIR = mocks
MOCKS_SRCS = $(MOCKS_DIR)/canSpy.c
CPPFLAGS += -I$(MOCKS_DIR)

UTILS_DIR = utils
CPPFLAGS += -I$(UTILS_DIR)

SRCS = 	$(CAN_SRCS) \
		$(CONTROLLER_SRCS) \
		$(COMMUNICATION_SRCS) \
		$(MOCKS_SRCS)

TEST_DIR = test
TEST_SRCS = $(TEST_DIR)/AK10_9Test.cpp\
			$(TEST_DIR)/CANTest.cpp

TARGET = tests

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

C_OBJS = $(SRCS:.c=.o)
CPP_OBJS = $(TEST_SRCS:.cpp=.o)

$(TARGET) : AllTests.cpp $(C_OBJS) $(CPP_OBJS)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LD_LIBRARIES)
	rm -rf $(C_OBJS) $(CPP_OBJS)

clean:
	rm -rf $(TARGET) $(C_OBJS) $(CPP_OBJS)

.PHONY: clean