# Flyshit（飞翔）

当学生不好好做题怎么办？懒得敲代码？训练摸鱼？

这是一个使用 `C++17` 标准编写的程序，如果你运行他，那就会在你的电脑里到处拉翔💩

新发布的版本包含 `clash-verge` 伪装，基础功能版参考旧版本。

## 使用方法一

1. 克隆项目到本地：
    ```bash
    git clone https://github.com/evansrrr/flyshit.git
    ```
2. 进入项目目录：
    ```bash
    cd flyshit
    ```
3. 编译并运行程序：
    ```bash
    g++ ".\gen.cpp" ".\resource.o" -o ".\gen.exe" -std=c++17 -static -mwindows -I"URL\mingw64\include" -I"URL\mingw64\x86_64-w64-mingw32\include" -I"URL\mingw64\lib\gcc\x86_64-w64-mingw32\14.2.0\include" -I"URL\mingw64\lib\gcc\x86_64-w64-mingw32\14.2.0\include\c++" -L"URL\mingw64\lib" -L"URL\mingw64\x86_64-w64-mingw32\lib"

    ./gen.exe
    ```

*文件使用MingGW64编译*

如需编译资源文件：

```bash
URL\mingw64\bin\windres.exe resource.rc -O coff -o resource.o
```

## 使用方法二

1. 下载发行包：

    [最新版本发行包](https://github.com/evansrrr/flyshit/releases/latest)

2. 解压并运行 `clash-verge.exe`

## 运行结果

顺利的话，你的Windows会在几秒钟内变成一个大茅坑，这取决于生成的文件数量和大小，你可以在gen.cpp中修改。

同时，自带的 `Clash Verge` 会弹出窗口进行伪装。

解药是 `restore.exe`，当然你也可以自己编译。

而且作者还很贴心的塞了一个订阅进去，但是生死未卜。

**经过实测，在生成1000个文件后删除时会出现某几个文件夹清理不全的问题**，~~所以100个就够千万别玩脱了~~ 这是因为作者纯辣鸡，如果有佬欢迎pr！

另外**千万别乱删文件**，万一删掉了记录文件（默认是 `C:\\ProgramData\\junk_files_record.txt`）就寄了。

多次运行生成程序应该不会出问题，记录采用追加式，可一次性删除所有生成文件（理论上是这样）

## 声明

妥善使用，仅供娱乐

使用此程序造成的后果与作者无关

## 许可证

本项目采用 [GNU General Public License v3.0 许可证](LICENSE)。


# Flyshit

The students aren't doing their job? Be lazy coding?

This is a program using `C++17` standard，if you run it，it will shit in your computer everywhere💩

New versions include `clash-verge` to cheat，the basic edition is provided in the older versions.

## How to use

1. Clone the repo：
    ```bash
    git clone https://github.com/evansrrr/flyshit.git
    ```
2. Switch to the project directory：
    ```bash
    cd flyshit
    ```
3. Compile and run：
    ```bash
    g++ ".\gen.cpp" ".\resource.o" -o ".\gen.exe" -std=c++17 -static -mwindows -I"URL\mingw64\include" -I"URL\mingw64\x86_64-w64-mingw32\include" -I"URL\mingw64\lib\gcc\x86_64-w64-mingw32\14.2.0\include" -I"URL\mingw64\lib\gcc\x86_64-w64-mingw32\14.2.0\include\c++" -L"URL\mingw64\lib" -L"URL\mingw64\x86_64-w64-mingw32\lib"

    ./gen.exe
    ```

*Compiled with MingGW64*

If you need to re-compile the resource files：

```bash
URL\mingw64\bin\windres.exe resource.rc -O coff -o resource.o
```

## Quickstart

1. Download Release：

    [The latest Release](https://github.com/evansrrr/flyshit/releases/latest)

2. Unzip files and run `clash-verge.exe`

## Afterwards

Your Windows will turn into a big shitpool in a moment if the program runs smoothly，it depends on the amount and size of files generated，which can be set in gen.cpp.

And the `Clash Verge` window will turn up to cheat.

To terminate this joke, run `restore.exe`. Of course you can compile it yourself.

ps: even a profile is also added.

**The delete program may ignore some of the files generated if the amount reaches 1000**，~~so 100 is very enough~~ because the author is rubbish. Welcome your pr!

And **don't delete files you are not familiar with**, especially the recording file (default is `C:\\ProgramData\\junk_files_record.txt`).

The recording file uses appends and so you can repeat running the generating program（at least theoretically）

## Announcement

Please use this program carefully, the author isn't responsible to every result caused by using it.

## LICENSE

This project uses [GNU General Public License v3.0](LICENSE)。