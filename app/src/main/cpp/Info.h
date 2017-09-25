//
// Created by jiangkun on 2017/8/11.
//

#ifndef HELLO_JNICALLBACK_INFO_H
#define HELLO_JNICALLBACK_INFO_H

#include <android/log.h>
#include <jni.h>
#include <string.h>


class Info {
public:
    Info();

    int add(int a, int b);

    static void log(const char *str);
};


#endif //HELLO_JNICALLBACK_INFO_H
