LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


ifeq ($(BUILD_WITH_CHAABI_SUPPORT),true)
LOCAL_C_INCLUDES = \
	$(TARGET_OUT_HEADERS)/chaabi
endif

LOCAL_SRC_FILES:= \
	bd_provisioning.c


ifeq ($(BUILD_WITH_CHAABI_SUPPORT),true)
LOCAL_CFLAGS:= -DBUILD_WITH_CHAABI_SUPPORT
LOCAL_STATIC_LIBRARIES := \
	CC6_UMIP_ACCESS CC6_ALL_BASIC_LIB
endif
LOCAL_CFLAGS += -m32
LOCAL_SHARED_LIBRARIES := \
	libc libcutils libcrypto

LOCAL_MODULE:= bd_prov
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

