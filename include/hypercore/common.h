#ifndef HC_COMMON_H
#define HC_COMMON_H

/**
 * Much of this file has been inspired by `KHR/khrplatform.h` header file
 * provided by the hc Group
 */

#if defined(_WIN32)
#  define HC_EXPORT __declspec(dllimport)
#elif defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR) >= 303
#  define HC_EXPORT __attribute__((visibility("default")))
#  define HC_INLINE inline
#else
#  define HC_EXPORT
#  define HC_INLINE
#endif

#ifndef HC_ALIGNMENT
#  define HC_ALIGNMENT sizeof(unsigned long) /* platform word */
#endif

typedef int HCint;
typedef int HCsizei;
typedef void HCvoid;
typedef char HCchar;
typedef short HCshort;

typedef unsigned int HCuint;
typedef unsigned int HCenum;

typedef unsigned int HCbitfield;
typedef unsigned char HCBoolean;
typedef unsigned short HCushort;

// C99
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__)

#include <stdint.h>
typedef int32_t hc_int32_t;
typedef int64_t hc_int64_t;
typedef uint32_t hc_uint32_t;
typedef uint64_t hc_uint64_t;

#define HC_SUPPORT_INT64 1
#define HC_SUPPORT_FLOAT 1

#elif defined(_WIN32)

typedef __int32 hc_int32_t;
typedef __int64 hc_int64_t;
typedef unsigned __int32 hc_uint32_t;
typedef unsigned __int64 hc_uint64_t;

#define HC_SUPPORT_INT64 1
#define HC_SUPPORT_FLOAT 1

#else

#include <stdint.h>

typedef int32_t hc_int32_t;
typedef int64_t hc_int64_t;
typedef uint32_t hc_uint32_t;
typedef uint64_t hc_uint64_t;

#define HC_SUPPORT_INT64 1
#define HC_SUPPORT_FLOAT 1

#endif

typedef signed char hc_int8_t;
typedef unsigned char hc_uint8_t;
typedef signed short int hc_int16_t;
typedef unsigned short int hc_uint16_t;

#ifdef _WIN64
typedef signed long long int hc_intptr_t;
typedef signed long long int hc_ssize_t;
typedef unsigned long long int hc_uintptr_t;
typedef unsigned long long int hc_usize_t;
#else
typedef signed long int hc_intptr_t;
typedef signed long int hc_ssize_t;
typedef unsigned long int hc_uintptr_t;
typedef unsigned long int hc_usize_t;
#endif

#if HC_SUPPORT_FLOAT
typedef float hc_float_t;
#endif

#if HC_SUPPORT_INT64
typedef hc_uint64_t hc_utime_nanoseconds_t;
typedef hc_int64_t hc_stime_nanoseconds_t;
#endif

#ifndef HC_MAX_ENUM
#define HC_MAX_ENUM 0x7FFFFFFF
#endif

typedef enum {
    HC_FALSE = 0,
    HC_TRUE  = 1,
    HC_BOOLEAN_ENUM_FORCE_SIZE = HC_MAX_ENUM
} hc_boolean_enum_t;

/**
 * HC typedefs
 */

typedef hc_uint8_t HCubyte;
typedef hc_float_t HCfloat;
typedef hc_ssize_t HCsizeiptr;
typedef hc_intptr_t HCintptr;

typedef hc_int64_t HCint64;
typedef hc_uint64_t HCuint64;

#endif
