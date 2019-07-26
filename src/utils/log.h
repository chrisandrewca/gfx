#ifndef _GFX_LOG_
#define _GFX_LOG_

#include <iostream>

// TODO off/on
namespace gfxLog
{
template <typename Arg, typename... Args>
void cout(Arg &&arg, Args &&... args)
{
    std::cout << std::forward<Arg>(arg);
    ((std::cout << std::forward<Args>(args)), ...);
    std::cout << std::endl;
}
} // namespace gfxLog

#endif