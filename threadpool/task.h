#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <cstring>
#include <sys/socket.h>

class CTask 
{
public:
    CTask(void (*p_task)(std::vector<void*>), std::vector<void*>args);

    ~CTask();

    void run();

private:
    static void (*process_task)(std::vector<void*>);

    std::vector<void*> m_args;
};