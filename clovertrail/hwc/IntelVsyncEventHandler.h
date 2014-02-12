/*
 * Copyright © 2012 Intel Corporation
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Jackie Li <yaodong.li@intel.com>
 *
 */
#ifndef __INTEL_VSYNC_EVENT_HANDLER_H__
#define __INTEL_VSYNC_EVENT_HANDLER_H__

#include <utils/threads.h>

extern "C" int clock_nanosleep(clockid_t clock_id, int flags,
                           const struct timespec *request,
                           struct timespec *remain);

class IntelHWComposer;

class IntelVsyncEventHandler : public android::Thread
{
    enum {
        UEVENT_MSG_LEN = 4096,
    };
    enum {
	    VSYNC_SRC_MIPI = 0,
	    VSYNC_SRC_HDMI,
	    VSYNC_SRC_FAKE,
	    VSYNC_SRC_NUM,
    };
public:
    IntelVsyncEventHandler(IntelHWComposer *hwc, int fd);
    virtual ~IntelVsyncEventHandler();
    void setActiveVsyncs(uint32_t activeVsyncs);
private:
    virtual bool threadLoop();
    virtual android::status_t readyToRun();
    virtual void onFirstRef();
private:
    virtual void handleVsyncEvent(const char *msg, int msgLen);
private:
    mutable android::Mutex mLock;
    android::Condition mCondition;
    IntelHWComposer *mComposer;
    int mDrmFd;
    mutable nsecs_t mNextFakeVSync;
    nsecs_t mRefreshPeriod;
    char mUeventMessage[UEVENT_MSG_LEN];
    int mUeventFd;
    uint32_t mActiveVsyncs;
};

#endif /*__INTEL_VSYNC_EVENT_HANDLER_H__*/
