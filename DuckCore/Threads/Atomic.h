#pragma once
// Std includes
#include <atomic>

namespace DC
{

template<typename taType>
using Atomic = std::atomic<taType>;

}