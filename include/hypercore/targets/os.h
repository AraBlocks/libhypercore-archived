#ifndef HC_TARGETS_OS_H
#define HC_TARGETS_OS_H

/**
 * Target platform defines:
 *
 *   HC_TARGET_OS_IOS
 *   HC_TARGET_OS_MACOS
 *   HC_TARGET_OS_LINUX
 *   HC_TARGET_OS_WINDOWS
 *   HC_TARGET_OS_ANDROID
 */

#if defined(__linux__)
  #define HC_TARGET_OS_IOS 0
  #define HC_TARGET_OS_MACOS 0
  #define HC_TARGET_OS_LINUX 1
  #define HC_TARGET_OS_WINDOWS 0
  #define HC_TARGET_OS_ANDROID 0
#elif defined(__APPLE__)
  #include "TargetConditionals.h"
  #if defined(TARGET_OS_MAC) && (TARGET_OS_MAC || defined(__MACH__))
    #define HC_TARGET_OS_IOS 0
    #define HC_TARGET_OS_MACOS 1
    #define HC_TARGET_OS_LINUX 0
    #define HC_TARGET_OS_WINDOWS 0
    #define HC_TARGET_OS_ANDROID 0
  #elif defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
    #define HC_TARGET_OS_IOS 1
    #define HC_TARGET_OS_MACOS 0
    #define HC_TARGET_OS_LINUX 0
    #define HC_TARGET_OS_WINDOWS 0
    #define HC_TARGET_OS_ANDROID 0
  #elif defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
    #define HC_TARGET_OS_IOS 1
    #define HC_TARGET_OS_MACOS 0
    #define HC_TARGET_OS_LINUX 0
    #define HC_TARGET_OS_WINDOWS 0
    #define HC_TARGET_OS_ANDROID 0
  #endif
#elif defined(__ANDROID__)
  #define HC_TARGET_OS_IOS 0
  #define HC_TARGET_OS_MACOS 0
  #define HC_TARGET_OS_LINUX 0
  #define HC_TARGET_OS_WINDOWS 0
  #define HC_TARGET_OS_ANDROID 1
#elif defined(__WINDOWS__)
  #if defined(_WIN64)
    #define HC_TARGET_OS_IOS 0
    #define HC_TARGET_OS_MACOS 0
    #define HC_TARGET_OS_LINUX 0
    #define HC_TARGET_OS_WINDOWS 1
    #define HC_TARGET_OS_ANDROID 0
  #endif
#else
  #define HC_TARGET_OS_IOS 0
  #define HC_TARGET_OS_MACOS 0
  #define HC_TARGET_OS_LINUX 0
  #define HC_TARGET_OS_WINDOWS 0
  #define HC_TARGET_OS_ANDROID 0
#endif

#endif
