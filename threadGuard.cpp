#include "threadGuard.h"


ThreadGuard::~ThreadGuard()
{
    if (t_.joinable())
    {
        t_.detach();
    }
}
