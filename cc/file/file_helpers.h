#pragma once

// File I/O helper utilities.

#include <string>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"

namespace file {

// Read the entire contents of a file.
// Parameters:
//   filename - Filename from which to read.
//   output - Receives the contents of the file.
//   read_as_binary - If true, read as binary.
// Returns status on error.
absl::Status GetContents(absl::string_view filename, std::string* output,
                         bool read_as_binary = true);

// Write the entire contents of a file.
// Parameters:
//   filename - Filename from which to read.
//   buffer - Buffer to write to the file.
// Returns status on error.
absl::Status SetContents(absl::string_view filename, absl::string_view buffer);

}  // namespace file
