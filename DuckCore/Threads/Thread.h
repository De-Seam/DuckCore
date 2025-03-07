#pragma once

namespace DC
{
void SetCurrentThreadAsMainThread();

int GetThreadID();
bool IsMainThread();
}