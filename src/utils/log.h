#ifndef _GFX_LOG_
#define _GFX_LOG_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace gfxLog {
  
  template<typename FormatString, typename... Args>
  inline void info(const FormatString &fmt, const Args &...args)
  {
    spdlog::info(fmt, args...);
  }
}

#endif