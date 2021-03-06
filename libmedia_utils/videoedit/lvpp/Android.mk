#
# Copyright (C) 2011 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= liblvpp_intel

LOCAL_COPY_HEADERS_TO := videoeditornv12

LOCAL_COPY_HEADERS := VideoEditorToolsNV12.h

LOCAL_SRC_FILES:=          \
    VideoEditorToolsNV12.c

LOCAL_MODULE_TAGS := optional


LOCAL_SHARED_LIBRARIES :=     \
    libcutils                 \
    libutils                  \
    libvideoeditor_osal      \


LOCAL_C_INCLUDES += \
    $(call include-path-for, osal) \
    $(call include-path-for, vss-common) \
    $(call include-path-for, vss-mcs) \
    $(call include-path-for, vss) \
    $(call include-path-for, vss-stagefrightshells) \
    $(call include-path-for, lvpp)


LOCAL_SHARED_LIBRARIES += libdl

# All of the shared libraries we link against.
LOCAL_LDLIBS := \
    -lpthread -ldl

include $(BUILD_STATIC_LIBRARY)

