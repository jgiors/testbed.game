#ifndef PRECOMP_H
#define PRECOMP_H

#include <SFML/Graphics.hpp>

#define NOMINMAX    ///<Prevent Windows from defining min() and max() macros which conflict with std.
#include <Windows.h>

#include <debugapi.h>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <iostream>

#include <json/single_include/nlohmann/json.hpp>

#include <i3lib.h>

#include "initLogger.h"

#endif //PRECOMP_H
