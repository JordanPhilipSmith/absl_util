#pragma once

// Macros for use with absl::Status and absl::StatusOr. This is a limited implementation of Google
// utilities. There is a more complete implementation in https://github.com/google/mediapipe.

// Examples:
//   absl::Status foo();
//   absl::Status foo_caller() {
//     RETURN_IF_ERROR(foo());
//     ...
//   }
//
//   absl::StatusOr<int> bar();
//   absl::Status bar_caller() {
//     ASSIGN_OR_RETURN(const int value, bar());
//     ...
//   }

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace absl_util::internal {

const absl::Status& ExtractStatus(const absl::Status& status) {
  return status;
}

template<class ValueT>
const absl::Status& ExtractStatus(const absl::StatusOr<ValueT>& status_or) {
  return status_or.status();
}
    
}  // namespace absl_util::internal

#ifndef CONCAT_INNER
#define CONCAT_INNER(a, b) a ## b
#endif  // CONCAT_INNER

#ifndef CONCAT
#define CONCAT(a, b) CONCAT_INNER(a, b)
#endif  // CONCAT

// This could be a problem if the macro is called twice on the same line (__LINE__).  __COUNTER__
// creates a truly unique name, but then the variable cannot be reused multiple times.
#ifndef UNIQUE_NAME
#define UNIQUE_NAME(base) CONCAT(base, __LINE__)
#endif  // UNIQUE_NAME

#ifndef RETURN_IF_ERROR
#define RETURN_IF_ERROR(a)                                                       \
  absl::Status UNIQUE_NAME(__status_) = ::absl_util::internal::ExtractStatus(a); \
  if (!UNIQUE_NAME(__status_).ok()) return UNIQUE_NAME(__status_)
#endif  // RETURN_IF_ERROR

#ifndef ASSIGN_OR_RETURN
#define ASSIGN_OR_RETURN(a, b)                 \
  auto UNIQUE_NAME(__status_or_) = (b);        \
  if (!UNIQUE_NAME(__status_or_).ok()) {       \
    return UNIQUE_NAME(__status_or_).status(); \
  }                                            \
  a = *std::move(UNIQUE_NAME(__status_or_))
#endif  // ASSIGN_OR_RETURN
