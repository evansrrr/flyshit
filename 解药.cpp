#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main() {
    // 记录文件位置的文件路径
    fs::path record_file = "C:\\junk_files_record.txt";
    
    // 打开记录文件
    std::ifstream record(record_file);
    if (!record) {
        // 如果C盘根目录没有，尝试从临时目录读取
        record_file = fs::temp_directory_path() / "junk_files_record.txt";
        record.open(record_file);
        
        if (!record) {
            std::cerr << "无法找到记录文件，无法清理垃圾文件。" << std::endl;
            return 1;
        }
    }
    
    std::vector<std::string> file_paths;
    std::string line;
    
    // 读取所有记录的文件路径
    while (std::getline(record, line)) {
        file_paths.push_back(line);
    }
    record.close();
    
    int deleted_count = 0;
    int failed_count = 0;
    
    // 删除所有记录的文件
    for (const auto& filepath : file_paths) {
        try {
            if (fs::exists(filepath)) {
                fs::remove(filepath);
                deleted_count++;
            }
        } catch (...) {
            failed_count++;
        }
    }
    
    // 删除记录文件本身
    try {
        fs::remove(record_file);
    } catch (...) {
        // 忽略错误
    }
    
    std::cout << "清理完成: " << deleted_count << " 个文件已删除, " 
              << failed_count << " 个文件删除失败。" << std::endl;
    
    // 等待用户确认
    std::cout << "按任意键退出..." << std::endl;
    std::cin.get();
    
    return 0;
}
