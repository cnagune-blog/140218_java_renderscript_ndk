BASE_DIR=..
include $(BASE_DIR)/Makefile.common


######################################################
# source directories
######################################################
DIRS= .\
	  algorithm


###########################################################
# Includes
###########################################################
LOCAL_INCLUDES= -I$(BASE_DIR)/src


###########################################################
# Libraries
###########################################################
LOCAL_LIBS=


###########################################################
# Sources
###########################################################
SRCS_CPP= $(foreach var, $(DIRS), $(wildcard $(var)/*.cpp))
SRCS_CC=  $(foreach var, $(DIRS), $(wildcard $(var)/*.c))
SRCS= $(SRCS_CPP) $(SRCS_CC)
EXCLUDE=./Rs-jni.o
OBJS= $(filter-out $(EXCLUDE), $(SRCS_CPP:%.cpp=%.o)) \
	$(filter-out $(EXCLUDE), $(SRCS_CC:%.c=%.o)) \


###########################################################
# GCOV
###########################################################
GCOV_GCDA = $(foreach var, $(DIRS), $(wildcard $(var)/*.gcda))
GCOV_GCNO = $(foreach var, $(DIRS), $(wildcard $(var)/*.gcno))
GCOV_GCOV = $(foreach var, $(DIRS), $(wildcard $(var)/*.gcov))


###########################################################
# Target
###########################################################
#TARGET=Vision
TARGET_SHARED=libRs-jni.so
TARGET_STATIC=libRs-jni.a


###########################################################
# Rules
###########################################################
all: $(TARGET_SHARED) $(TARGET_STATIC)
	cp $(TARGET_SHARED) $(OUTPUT_DIR)
	cp $(TARGET_STATIC) $(OUTPUT_DIR)

$(TARGET_SHARED): $(OBJS)
	$(LDSO) $(OBJS) $(LDFLAGS) -o $@

$(TARGET_STATIC): $(OBJS)
	$(AR) rcu $(TARGET_STATIC) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -c -O3 -o $@ $<

.c.o:
	$(CC) $(CXXFLAGS) $(INCLUDES) -fPIC -c -O3 -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET_SHARED) $(TARGET_STATIC) $(GCOV_GCDA) $(GCOV_GCNO) $(GCOV_GCOV)
	rm -f $(OUTPUT_DIR)/$(TARGET_SHARED)
	rm -f $(OUTPUT_DIR)/$(TARGET_STATIC)

