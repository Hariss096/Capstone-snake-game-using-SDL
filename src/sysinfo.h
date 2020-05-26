#ifndef SYSINFO_H
#define SYSINFO_H

#include <string>
#include <iostream>
#include "SDL.h"

class Sysinfo
{
public:
    // Constructor
    Sysinfo() : os(std::string()) {
        os = getOS();
    }

    // functions to get and print OS
    std::string getOS();
    void printOS();

private:
    std::string os;
};

std::string Sysinfo::getOS()
{
    const char *platform = SDL_GetPlatform();
    return platform;
};

void Sysinfo::printOS()
{
    SDL_Log("Current Operating system: %s", SDL_GetPlatform());
    SDL_Log("Number of logical CPU cores: %d", SDL_GetCPUCount());
}

#endif