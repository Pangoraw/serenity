/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Assertions.h>
#include <AK/CheckedFormatString.h>

namespace AK {
template<typename... Parameters>
void warnln(CheckedFormatString<Parameters...>&& fmtstr, const Parameters&...);
}

namespace Test {
// Declare a helper so that we can call it from VERIFY in included headers
void current_test_case_did_fail();
}

#undef VERIFY
#define VERIFY(x)                                                                                    \
    do {                                                                                             \
        if (!(x)) {                                                                                  \
            ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: VERIFY({}) failed", __FILE__, __LINE__, #x); \
            ::Test::current_test_case_did_fail();                                                    \
        }                                                                                            \
    } while (false)

#undef VERIFY_NOT_REACHED
#define VERIFY_NOT_REACHED()                                                                           \
    do {                                                                                               \
        ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: VERIFY_NOT_REACHED() called", __FILE__, __LINE__); \
        ::abort();                                                                                     \
    } while (false)

#undef TODO
#define TODO()                                                                                   \
    do {                                                                                         \
        ::AK::warnln(stderr, "\033[31;1mFAIL\033[0m: {}:{}: TODO() called", __FILE__, __LINE__); \
        ::abort();                                                                               \
    } while (false)

#define EXPECT_EQ(a, b)                                                                                                                                                                      \
    do {                                                                                                                                                                                     \
        auto lhs = (a);                                                                                                                                                                      \
        auto rhs = (b);                                                                                                                                                                      \
        if (lhs != rhs) {                                                                                                                                                                    \
            ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: EXPECT_EQ({}, {}) failed with lhs={} and rhs={}", __FILE__, __LINE__, #a, #b, FormatIfSupported { lhs }, FormatIfSupported { rhs }); \
            ::Test::current_test_case_did_fail();                                                                                                                                            \
        }                                                                                                                                                                                    \
    } while (false)

// If you're stuck and `EXPECT_EQ` seems to refuse to print anything useful,
// try this: It'll spit out a nice compiler error telling you why it doesn't print.
#define EXPECT_EQ_FORCE(a, b)                                                                                                                    \
    do {                                                                                                                                         \
        auto lhs = (a);                                                                                                                          \
        auto rhs = (b);                                                                                                                          \
        if (lhs != rhs) {                                                                                                                        \
            ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: EXPECT_EQ({}, {}) failed with lhs={} and rhs={}", __FILE__, __LINE__, #a, #b, lhs, rhs); \
            ::Test::current_test_case_did_fail();                                                                                                \
        }                                                                                                                                        \
    } while (false)

#define EXPECT(x)                                                                                    \
    do {                                                                                             \
        if (!(x)) {                                                                                  \
            ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: EXPECT({}) failed", __FILE__, __LINE__, #x); \
            ::Test::current_test_case_did_fail();                                                    \
        }                                                                                            \
    } while (false)

#define EXPECT_APPROXIMATE(a, b)                                                                                \
    do {                                                                                                        \
        auto expect_close_lhs = a;                                                                              \
        auto expect_close_rhs = b;                                                                              \
        auto expect_close_diff = static_cast<double>(expect_close_lhs) - static_cast<double>(expect_close_rhs); \
        if (fabs(expect_close_diff) > 0.0000005) {                                                              \
            ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: EXPECT_APPROXIMATE({}, {})"                             \
                         " failed with lhs={}, rhs={}, (lhs-rhs)={}",                                           \
                __FILE__, __LINE__, #a, #b, expect_close_lhs, expect_close_rhs, expect_close_diff);             \
            ::Test::current_test_case_did_fail();                                                               \
        }                                                                                                       \
    } while (false)

#define FAIL(message)                                                                  \
    do {                                                                               \
        ::AK::warnln("\033[31;1mFAIL\033[0m: {}:{}: {}", __FILE__, __LINE__, message); \
        ::Test::current_test_case_did_fail();                                          \
    } while (false)
