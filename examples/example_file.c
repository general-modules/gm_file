/**
 * @file      example_file.c
 * @brief     文件模块示例代码源文件
 * @author    huenrong (sgyhy1028@outlook.com)
 * @date      2026-02-16 16:21:22
 *
 * @copyright Copyright (c) 2026 huenrong
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "gm_file.h"

/**
 * @brief 程序入口
 *
 * @param[in] argc: 参数个数
 * @param[in] argv: 参数列表
 *
 * @return 成功: 0
 * @return 失败: 其它
 */
int main(int argc, char *argv[])
{
    const char *cmd = "pwd";
    printf("exec %s command\n", cmd);
    char *cmd_result = gm_file_exec_cmd(cmd);
    if (cmd_result == NULL)
    {
        printf("exec cmd failed. cmd: %s\n\n", cmd);
    }
    else
    {
        printf("exec %s cmd result: %s\n", cmd, cmd_result);
        free(cmd_result);
    }

    const char *test_file = "./test_config.json";
    printf("get file size. file: %s\n", test_file);
    size_t file_size = 0;
    int ret = gm_file_get_size(test_file, &file_size);
    if (ret != 0)
    {
        printf("get file size failed. file: %s, ret: %d\n\n", test_file, ret);
    }
    else
    {
        printf("get file size success. file: %s, size: %zu byte\n\n", test_file, file_size);
    }

    printf("read file content. file: %s\n", test_file);
    char *file_content = gm_file_read_content(test_file);
    if (file_content == NULL)
    {
        printf("read file content failed. file: %s\n", test_file);
    }
    else
    {
        printf("read file content success. file: %s, content: %s\n", test_file, file_content);
        free(file_content);
    }

    return 0;
}
