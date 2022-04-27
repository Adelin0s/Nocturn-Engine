#ifndef PLATFORM_H
#define PLATFORM_H

#define NOCTURN_CPP17V 201703L

#if __cplusplus >= NOCTURN_CPP17V
/** @def NODISCARD
 *  @brief Marks a function as "NODISCARD" meaning that result must be captured and should not be discarded.
 */
#define NODISCARD [[nodiscard]]
#else
#define NODISCARD
#endif

/**
 *  @def FORCEINLINE
 *  @brief Force a function to be inline
 */
#ifndef FORCE_INLINE
#define FORCE_INLINE __forceinline
#endif

#if __cplusplus >= NOCTURN_CPP17V
/** @def MAYBEUNUSED
 *  @brief Marks a function as "MAYBEUNUSED" meaning that result may be unused.
 */
#define MAYBEUNUSED [[maybe_unused]]
#else
#define MAYBEUNUSED
#endif

#if __cplusplus >= NOCTURN_CPP17V
/** @def NORETURN
 *  @brief Marks a function as "NORETURN" meaning that the function will never finish, or terminate the application.
 */
#define NORETURN [[noreturn]]
#else
#define NORETURN
#endif

/** @def NOCTURN_PURE
 *  @brief Marks a function as pure virtual.
 */
#define NOCTURN_PURE = 0

/** @def NOCTURN_IMPURE
 *  @brief Marks a function as overridable but default implemented.
 */
#define NOCTURN_IMPURE \
	{}

/** @def VIRTUAL
 *  @brief Marks a function as virtual
 */
#define VIRTUAL virtual

#endif