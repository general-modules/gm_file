# gm_file

`gm_file` 模块提供文件操作相关接口。该模块以纯 C 语言实现，不依赖任何第三方库，具有良好的可移植性。

## 目录结构

```bash
gm_file/
├── build/             # 编译输出目录
├── CMakeLists.txt
├── examples/          # 示例代码
│   ├── CMakeLists.txt
│   └── example_file.c
├── gm_file/           # 模块核心源码
│   ├── CMakeLists.txt
│   ├── gm_file.c
│   └── gm_file.h
├── LICENSE
├── README.md
└── test_config.json   # 测试配置文件
```

## 编译与运行

### 编译

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

编译完成后，`build` 目录结构如下（仅说明关键文件）：

``` bash
build
├── examples
│   ├── example_file # 可执行文件
└── gm_file
    └── libgm_file.a # 静态库
```

### 运行示例

```bash
$ ./build/examples/example_file
```

注意：

- 这里需要在根目录执行，因为 `example_file.c` 中使用了相对路径引用 `test_config.json` 文件。

## 移植

### 方式一：使用源码

将 `gm_file` 目录下的源码文件复制到你的项目目录中，并在代码中包含 `gm_file.h` 头文件。
可参考 `gm_file/CMakeLists.txt` 中的写法，将其作为一个独立模块进行编译。

### 方式二：使用静态库

将生成的 `libgm_file.a` 和 `gm_file.h` 拷贝到你的项目中，包含 `gm_file.h` 头文件并链接 `libgm_file.a` 库即可。

## 注意事项

- 部分接口返回值为 `char *` 类型，需要由调用者自行释放内存
- 接口行为及返回值请以头文件注释为准

## 问题与建议

有任何问题或建议欢迎提交 [issue](https://github.com/general-modules/gm_file/issues) 进行讨论。
