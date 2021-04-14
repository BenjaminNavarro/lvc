#ifndef LLC_COMPILER_H
#define LLC_COMPILER_H

/// \macro LLC_GNUC_PREREQ
/// Extend the default __GNUC_PREREQ even if glibc's features.h isn't
/// available.
#ifndef LLC_GNUC_PREREQ
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
#define LLC_GNUC_PREREQ(maj, min, patch)                                       \
  ((__GNUC__ << 20) + (__GNUC_MINOR__ << 10) + __GNUC_PATCHLEVEL__ >=          \
   ((maj) << 20) + ((min) << 10) + (patch))
#elif defined(__GNUC__) && defined(__GNUC_MINOR__)
#define LLC_GNUC_PREREQ(maj, min, patch)                                       \
  ((__GNUC__ << 20) + (__GNUC_MINOR__ << 10) >= ((maj) << 20) + ((min) << 10))
#else
#define LLC_GNUC_PREREQ(maj, min, patch) 0
#endif
#endif

// Only use __has_cpp_attribute in C++ mode. GCC defines __has_cpp_attribute in
// C mode, but the :: in __has_cpp_attribute(scoped::attribute) is invalid.
#ifndef LLC_HAS_CPP_ATTRIBUTE
#if defined(__cplusplus) && defined(__has_cpp_attribute)
#define LLC_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define LLC_HAS_CPP_ATTRIBUTE(x) 0
#endif
#endif

#if __has_attribute(returns_nonnull) || LLC_GNUC_PREREQ(4, 9, 0)
#define LLC_ATTRIBUTE_RETURNS_NONNULL __attribute__((returns_nonnull))
#elif defined(_MSC_VER)
#define LLC_ATTRIBUTE_RETURNS_NONNULL _Ret_notnull_
#else
#define LLC_ATTRIBUTE_RETURNS_NONNULL
#endif

#ifdef __GNUC__
#define LLC_ATTRIBUTE_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
#define LLC_ATTRIBUTE_NORETURN __declspec(noreturn)
#else
#define LLC_ATTRIBUTE_NORETURN
#endif

/// \macro LLC_ATTRIBUTE_RETURNS_NOALIAS Used to mark a function as returning a
/// pointer that does not alias any other valid pointer.
#ifdef __GNUC__
#define LLC_ATTRIBUTE_RETURNS_NOALIAS __attribute__((__malloc__))
#elif defined(_MSC_VER)
#define LLC_ATTRIBUTE_RETURNS_NOALIAS __declspec(restrict)
#else
#define LLC_ATTRIBUTE_RETURNS_NOALIAS
#endif

#if __has_attribute(used) || LLC_GNUC_PREREQ(3, 1, 0)
#define LLC_ATTRIBUTE_USED __attribute__((__used__))
#else
#define LLC_ATTRIBUTE_USED
#endif

// Some compilers warn about unused functions. When a function is sometimes
// used or not depending on build settings (e.g. a function only called from
// within "assert"), this attribute can be used to suppress such warnings.
//
// However, it shouldn't be used for unused *variables*, as those have a much
// more portable solution:
//   (void)unused_var_name;
// Prefer cast-to-void wherever it is sufficient.
#if __has_attribute(unused) || LLC_GNUC_PREREQ(3, 1, 0)
#define LLC_ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define LLC_ATTRIBUTE_UNUSED
#endif

/// LLC_NODISCARD - Warn if a type or return value is discarded.

// Use the 'nodiscard' attribute in C++17 or newer mode.
#if defined(__cplusplus) && __cplusplus > 201402L &&                           \
    LLC_HAS_CPP_ATTRIBUTE(nodiscard)
#define LLC_NODISCARD [[nodiscard]]
#elif LLC_HAS_CPP_ATTRIBUTE(clang::warn_unused_result)
#define LLC_NODISCARD [[clang::warn_unused_result]]
// Clang in C++14 mode claims that it has the 'nodiscard' attribute, but also
// warns in the pedantic mode that 'nodiscard' is a C++17 extension (PR33518).
// Use the 'nodiscard' attribute in C++14 mode only with GCC.
// TODO: remove this workaround when PR33518 is resolved.
#elif defined(__GNUC__) && LLC_HAS_CPP_ATTRIBUTE(nodiscard)
#define LLC_NODISCARD [[nodiscard]]
#else
#define LLC_NODISCARD
#endif

/// LLC_GSL_OWNER - Apply this to owning classes like SmallVector to enable
/// lifetime warnings.
#if LLC_HAS_CPP_ATTRIBUTE(gsl::Owner)
#define LLC_GSL_OWNER [[gsl::Owner]]
#else
#define LLC_GSL_OWNER
#endif

#if __has_builtin(__builtin_expect) || LLC_GNUC_PREREQ(4, 0, 0)
#define LLC_LIKELY(EXPR) __builtin_expect((bool)(EXPR), true)
#define LLC_UNLIKELY(EXPR) __builtin_expect((bool)(EXPR), false)
#else
#define LLC_LIKELY(EXPR) (EXPR)
#define LLC_UNLIKELY(EXPR) (EXPR)
#endif

#endif