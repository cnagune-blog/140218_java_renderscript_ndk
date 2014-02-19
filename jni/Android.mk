LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_NEON := true
LOCAL_CFLAGS += -Wall
#LOCAL_LDLIBS := -llog -ljnigraphics
LOCAL_LDLIBS := -llog -ljnigraphics
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_MODULE    := Rs-jni
LOCAL_SRC_FILES := src/Rs-jni.c \
                   src/Allocation.c \
                   src/algorithm/Argb8888_To_Gray.c \
                   src/algorithm/Argb8888_To_Gray_Neon.c \
                   src/algorithm/Argb8888_To_Gray_Thread.c \
                   src/algorithm/Argb8888_To_Gray_Neon_Thread.c \
                   src/algorithm/Argb8888_To_Gray_Neon_Thread_Direct.c

include $(BUILD_SHARED_LIBRARY)

