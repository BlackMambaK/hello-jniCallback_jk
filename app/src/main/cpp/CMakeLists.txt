cmake_minimum_required(VERSION 3.4.1)

add_library(hello-jnicallback SHARED
            hello-jnicallback.c)


# Include libraries needed for hello-jnicallback lib
target_link_libraries(hello-jnicallback
                      android
                      log)

add_library(cpp_info SHARED
            LogHelper.cpp
            Info.cpp)

target_link_libraries(cpp_info
                      android
                      log)
