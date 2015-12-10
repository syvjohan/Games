#ifndef FRAMEWORKDEFS_H
#define FRAMEWORKDEFS_H

typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef bool boolean;
typedef unsigned char u8;
typedef char s8;
typedef unsigned long long usize;

#ifndef NULL
#define NULL 0
#endif

// Make a platform based conditional for this
#if 1
#define FRAMEWORK_USE_MOVE_SEMANTICS
#endif

#ifndef MAX
#define MAX(A, B) (A > B ? A : B)
#define MIN(A, B) (A < B ? A : B)
#endif

#endif // !FRAMEWORKDEFS_H
