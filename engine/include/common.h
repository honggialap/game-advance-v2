#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <box2d/box2d.h>

#include <json.hpp>
using nlohmann::json;

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include <thread>
#include <mutex>
#include <queue>
#include <tuple>
#include <map>
#include <sstream>
#include <cmath>

#include "define.h"

#endif // !__COMMON_H__
