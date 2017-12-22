#ifndef HC_PLATFORM_H
#define HC_PLATFORM_H

#include "targets.h"

#if defined(HC_TARGET_OS_LINUX)
  #include "platform/linux.h"
#elif defined(HC_TARGET_OS_MACOS)
  #include "platform/macos.h"
#elif defined(HC_TARGET_OS_IOS)
  #include "platform/ios.h"
#elif defined(HC_TARGET_OS_WINDOWS)
  #include "platform/windows.h"
#elif defined(HC_TARGET_OS_ANDROID)
  #include "platform/android.h"
#else
  #error "Unsupported platform"
#endif

#endif
