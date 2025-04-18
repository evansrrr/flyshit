// file_deleter.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// ���Ҽ�¼�ļ�
fs::path find_record_file() {
    fs::path primary = "C:\\ProgramData\\junk_files_record.txt";
    if (fs::exists(primary)) {
        return primary;
    }
    fs::path temp = fs::temp_directory_path() / "junk_files_record.txt";
    if (fs::exists(temp)) {
        return temp;
    }
    throw std::runtime_error("δ��Ԥ��λ���ҵ���¼�ļ���");
}

int main() {
    try {
        fs::path record_file = find_record_file();
        std::ifstream record(record_file);
        if (!record) {
            throw std::runtime_error("�޷��򿪼�¼�ļ�: " + record_file.string());
        }
        
        std::string line;
        while (std::getline(record, line)) {
            if (!line.empty()) {
                try {
                    if (fs::remove(line)) {
                        std::cout << "��ɾ��: " << line << std::endl;
                    } else {
                        std::cout << "�ļ�δ�ҵ�: " << line << std::endl;
                    }
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "ɾ���ļ����� " << line << ": " << e.what() << std::endl;
                }
            }
        }
        record.close();
        
        try {
            fs::remove(record_file);
            std::cout << "��ɾ����¼�ļ�: " << record_file << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cerr << "ɾ����¼�ļ�����: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
