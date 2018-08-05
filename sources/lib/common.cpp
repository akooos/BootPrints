#include "common.h"

namespace BootPrints{
  extern const char app_name[]     = "BootPrints";
  extern const char org_name[]     = "BlueBlur";
  extern const char org_domain[]   = "Software Development";
  extern const char version[]      = STRINGIFY(APP_VERSION);
  extern const char build_date[]   = __DATE__;
  extern const char build_time[]   = __TIME__;
  extern const char compiler[]     = COMPILER;
  extern const char sccs_version[] = STRINGIFY(GIT_COMMIT_HASH);
}
