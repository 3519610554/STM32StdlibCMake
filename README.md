## 介绍

这是应该基于STM32L1系列的CMakeHAL移植到CMake标准库的工程与视频工程基本相似其他系列单片机移植和视频差不多一样

## 依赖项

- cmake
- make
- gcc-arm
- openocd

## vscode搭配插件

1. clangd(代码提示)
2. CMake Tools(可要可不要)
3. CMake Language Support(CMake语法提示)
4. Cortex-Debug(后续openocd断点调试需要)

## 如果不用CMake Tools怎么生成？

进入根目录 build 文件夹（如果没有就创建）

```bash
cd build
```

开始构建

```bash
cmake ..
```

构建成功直接开始编译

```bash
make
```

即可生成.bin文件
