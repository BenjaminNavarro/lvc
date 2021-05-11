
#include "lvc/Testing/Support/SupportHelpers.h"

#include "lvc/ADT/SmallString.h"
#include "lvc/ADT/Twine.h"
#include "lvc/Support/Error.h"
#include "lvc/Support/FileSystem.h"
#include "lvc/Support/MemoryBuffer.h"
#include "lvc/Support/Path.h"

#include "gtest/gtest.h"

using namespace lvc;
using namespace lvc::unittest;

static std::pair<bool, SmallString<128>> findSrcDirMap(StringRef Argv0) {
  SmallString<128> BaseDir = lvc::sys::path::parent_path(Argv0);

  lvc::sys::fs::make_absolute(BaseDir);

  SmallString<128> PathInSameDir = BaseDir;
  lvc::sys::path::append(PathInSameDir, "llvm.srcdir.txt");

  if (lvc::sys::fs::is_regular_file(PathInSameDir))
    return std::make_pair(true, std::move(PathInSameDir));

  SmallString<128> PathInParentDir = lvc::sys::path::parent_path(BaseDir);

  lvc::sys::path::append(PathInParentDir, "llvm.srcdir.txt");
  if (lvc::sys::fs::is_regular_file(PathInParentDir))
    return std::make_pair(true, std::move(PathInParentDir));

  return std::pair<bool, SmallString<128>>(false, {});
}

SmallString<128> lvc::unittest::getInputFileDirectory(const char *Argv0) {
  bool Found = false;
  SmallString<128> InputFilePath;
  std::tie(Found, InputFilePath) = findSrcDirMap(Argv0);

  EXPECT_TRUE(Found) << "Unit test source directory file does not exist.";

  auto File = MemoryBuffer::getFile(InputFilePath);

  EXPECT_TRUE(static_cast<bool>(File))
      << "Could not open unit test source directory file.";

  InputFilePath.clear();
  InputFilePath.append((*File)->getBuffer().trim());
  lvc::sys::path::append(InputFilePath, "Inputs");
  lvc::sys::path::native(InputFilePath);
  return InputFilePath;
}
