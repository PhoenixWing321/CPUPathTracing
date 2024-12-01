#pragma once
#include <filesystem>
#include <iostream>

using std::cout;
using std::endl;

namespace fs = std::filesystem;

class Utility{
public:
    static  std::string path_models;
    static std::filesystem::path path_output;
};

std::string Utility::path_models="../../../models";
fs::path Utility::path_output=fs::absolute("../../../output");;