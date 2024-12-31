#pragma once
namespace fs = std::filesystem;
void readallfile(std::string path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        std::cout << "Ŀ¼�еķǿ��ļ�: " << path << "\n";
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.path())) {
                // ���ļ�������Ƿ�Ϊ��
                std::ifstream file(entry.path(), std::ios::ate); // ֱ�Ӷ�λ���ļ�ĩβ
                if (file.is_open() && file.tellg() > 0) { // �ļ��򿪳ɹ��ҷǿ�
                    std::cout << entry.path().filename() << '\n';
                }
            }
        }
    }
    else {
        std::cerr << "·�������ڻ���Ŀ¼: " << path << "\n";
    }
}