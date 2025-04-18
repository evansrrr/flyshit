// file_deleter.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// 查找记录文件
fs::path find_record_file() {
    fs::path primary = "C:\\ProgramData\\junk_files_record.txt";
    if (fs::exists(primary)) {
        return primary;
    }
    fs::path temp = fs::temp_directory_path() / "junk_files_record.txt";
    if (fs::exists(temp)) {
        return temp;
    }
    throw std::runtime_error("未在预期位置找到记录文件。");
}

int main() {
    try {
        fs::path record_file = find_record_file();
        std::ifstream record(record_file);
        if (!record) {
            throw std::runtime_error("无法打开记录文件: " + record_file.string());
        }
        
        std::string line;
        while (std::getline(record, line)) {
            if (!line.empty()) {
                try {
                    if (fs::remove(line)) {
                        std::cout << "已删除: " << line << std::endl;
                    } else {
                        std::cout << "文件未找到: " << line << std::endl;
                    }
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "删除文件出错 " << line << ": " << e.what() << std::endl;
                }
            }
        }
        record.close();
        
        try {
            fs::remove(record_file);
            std::cout << "已删除记录文件: " << record_file << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cerr << "删除记录文件出错: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
