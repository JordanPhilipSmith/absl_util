#include "cc/status/status_macros.h"

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gtest/gtest.h"

namespace {

absl::Status Foo(absl::Status status) {
  return status;
}

absl::StatusOr<int> Bar(absl::Status status) {
  if (!status.ok()) {
    return status;
  }
  return 1;
}

absl::StatusOr<int> CallFoo(absl::Status status) {
  RETURN_IF_ERROR(Foo(status));
  return 1;
}

absl::StatusOr<int> CallBar(absl::Status status) {
  ASSIGN_OR_RETURN(const int value, Bar(status));
  return value;
}

TEST(ReturnIfErrorTest, ReturnsValue) {
  absl::StatusOr<int> value_or = CallFoo(absl::OkStatus());
  ASSERT_TRUE(value_or.ok());
  EXPECT_EQ(*value_or, 1);
}

TEST(ReturnIfErrorTest, ReturnsFailedPrecondition) {
  static constexpr char kMessage[] = "Error message";
  absl::StatusOr<int> value_or = CallFoo(absl::FailedPreconditionError(kMessage));
  const absl::Status& status = value_or.status();
  EXPECT_EQ(status.code(), absl::StatusCode::kFailedPrecondition);
  EXPECT_EQ(status.message(), kMessage);
}

TEST(AssignOrReturnTest, ReturnsValue) {
  absl::StatusOr<int> value_or = CallBar(absl::OkStatus());
  ASSERT_TRUE(value_or.ok());
  EXPECT_EQ(*value_or, 1);
}

TEST(AssignOrReturnTest, ReturnsFailedPrecondition) {
  static constexpr char kMessage[] = "Error message";
  absl::StatusOr<int> value_or = CallBar(absl::FailedPreconditionError(kMessage));
  const absl::Status& status = value_or.status();
  EXPECT_EQ(status.code(), absl::StatusCode::kFailedPrecondition);
  EXPECT_EQ(status.message(), kMessage);
}
  
}  // namespace
