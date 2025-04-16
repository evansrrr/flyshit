#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main() {
    // ��¼�ļ�λ�õ��ļ�·��
    fs::path record_file = "C:\\junk_files_record.txt";
    
    // �򿪼�¼�ļ�
    std::ifstream record(record_file);
    if (!record) {
        // ���C�̸�Ŀ¼û�У����Դ���ʱĿ¼��ȡ
        record_file = fs::temp_directory_path() / "junk_files_record.txt";
        record.open(record_file);
        
        if (!record) {
            std::cerr << "�޷��ҵ���¼�ļ����޷����������ļ���" << std::endl;
            return 1;
        }
    }
    
    std::vector<std::string> file_paths;
    std::string line;
    
    // ��ȡ���м�¼���ļ�·��
    while (std::getline(record, line)) {
        file_paths.push_back(line);
    }
    record.close();
    
    int deleted_count = 0;
    int failed_count = 0;
    
    // ɾ�����м�¼���ļ�
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
    
    // ɾ����¼�ļ�����
    try {
        fs::remove(record_file);
    } catch (...) {
        // ���Դ���
    }
    
    std::cout << "�������: " << deleted_count << " ���ļ���ɾ��, " 
              << failed_count << " ���ļ�ɾ��ʧ�ܡ�" << std::endl;
    
    // �ȴ��û�ȷ��
    std::cout << "��������˳�..." << std::endl;
    std::cin.get();
    
    return 0;
}
