#pragma once

// 미리 컴파일 된 헤더 (cpp 파일들은 무조건 미리 컴파일 된 헤더를 참조해야함)
#include <Windows.h>
#include <iostream>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::wstring;

#include <cassert>

// 라이브러리 참조 TransparentBlt
#pragma comment (lib, "Msimg32.lib")



#include "define.h"
#include "struct.h"