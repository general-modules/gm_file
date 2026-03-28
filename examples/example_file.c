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

    const char *bin_file_name = "./test_file.bin";
    printf("get bin file size. file: %s\n", bin_file_name);
    size_t bin_file_size = 0;
    int ret = gm_file_get_size(bin_file_name, &bin_file_size);
    if (ret != 0)
    {
        printf("get bin file size failed. file: %s, ret: %d\n\n", bin_file_name, ret);
    }
    else
    {
        printf("get bin file size success. file: %s, size: %zu byte\n\n", bin_file_name, bin_file_size);
    }

    printf("read bin file data. file: %s\n", bin_file_name);
    uint8_t *bin_file_data = (uint8_t *)gm_file_read_raw(bin_file_name, 0, NULL);
    if (bin_file_data == NULL)
    {
        printf("read bin file data failed. file: %s\n", bin_file_name);
    }
    else
    {
        printf("read bin file data success. file: %s, data: ", bin_file_name);
        for (size_t i = 0; i < bin_file_size; i++)
        {
            printf("0x%02x ", bin_file_data[i]);
        }
        printf("\n");
        free(bin_file_data);
    }

    printf("\n=============================================================\n\n");

    const char *text_file_name = "./test_file.json";
    printf("get text file size. file: %s\n", text_file_name);
    size_t text_file_size = 0;
    ret = gm_file_get_size(text_file_name, &text_file_size);
    if (ret != 0)
    {
        printf("get text file size failed. file: %s, ret: %d\n\n", text_file_name, ret);
    }
    else
    {
        printf("get text file size success. file: %s, size: %zu byte\n\n", text_file_name, text_file_size);
    }

    printf("read text file data. file: %s\n", text_file_name);
    char *text_file_data = gm_file_read_text(text_file_name, 0, NULL);
    if (text_file_data == NULL)
    {
        printf("read text file data failed. file: %s\n", text_file_name);
    }
    else
    {
        printf("read text file data success. file: %s, data: %s\n", text_file_name, text_file_data);
        free(text_file_data);
    }

    return 0;
}
