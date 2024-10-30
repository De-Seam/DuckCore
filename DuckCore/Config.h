#pragma once

// Change this depending on whether you're working with floats or doubles
using TransformType = float;

// Asserts
#ifdef _DEBUG
#define _ASSERTS
#define IF_ASSERTS(x) x
#else
#deifne IF_ASSERTS(x)
#endif