#ifndef HC_TARGETS_CPU_H
#define HC_TARGETS_CPU_H

/**
 * Platform cpu defines
 *
 *  HC_CPU_ARM
 *  HC_CPU_X86
 *  HC_CPU_X86_64
 */

#if defined(__GNUC__)
  #if defined(__arm__)
    #define HC_CPU_ARM 1
    #define HC_CPU_X86 0
    #define HC_CPU_X86_64 0
  #elif defined(__i386__)
    #define HC_CPU_ARM 0
    #define HC_CPU_X86 1
    #define HC_CPU_X86_64 0
  #elif defined(__x86_64__)
    #define HC_CPU_ARM 0
    #define HC_CPU_X86 0
    #define HC_CPU_X86_64 1
  #else
    #error "Unsupported GNU compiler"
  #endif
#elif defined(_MSC_VER)
	#if defined(_M_ARM)
		#define HC_CPU_ARM 1
		#define HC_CPU_X86 0
		#define HC_CPU_X86_64 0
	#elif defined(_M_IX86)
		#define HC_CPU_ARM 0
		#define HC_CPU_X86 1
		#define HC_CPU_X86_64 0
	#elif defined(_M_X64)
		#define HC_CPU_ARM 0
		#define HC_CPU_X86 0
		#define HC_CPU_X86_64 1
	#else
		#error "Unsupported MSVC compiler"
	#endif
#else
  #error "Unsupported CPU architecture"
#endif

#endif
