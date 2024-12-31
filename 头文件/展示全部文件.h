#pragma once
namespace fs = std::filesystem;
void readallfile(std::string path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        std::cout << "目录中的非空文件: " << path << "\n";
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.path())) {
                // 打开文件并检查是否为空
                std::ifstream file(entry.path(), std::ios::ate); // 直接定位到文件末尾
                if (file.is_open() && file.tellg() > 0) { // 文件打开成功且非空
                    std::cout << entry.path().filename() << '\n';
                }
            }
        }
    }
    else {
        std::cerr << "路径不存在或不是目录: " << path << "\n";
    }
}