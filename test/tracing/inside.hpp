#pragma once
#include <filesystem>
#include <iostream>

using std::cout;
using std::endl;

namespace fs = std::filesystem;

class Utility{
public:
    static  std::string path_models;
};
std::string Utility::path_models="../../models";