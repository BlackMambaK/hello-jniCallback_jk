//
// Created by jiangkun on 2017/8/11.
//

#include "Info.h"

static const char *kTAG = "Info";

#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))


void Info::log(const char *str) {
    LOGE("%s", str);
}

int Info::add(int a, int b) {
    return a + b;
}

Info::Info() {

}

