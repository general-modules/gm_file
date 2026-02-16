/**
 * @file      gm_file.c
 * @brief     文件模块源文件
 * @author    huenrong (sgyhy1028@outlook.com)
 * @date      2026-02-16 16:21:07
 *
 * @copyright Copyright (c) 2026 huenrong
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gm_file.h"

char *gm_file_exec_cmd(const char *cmd)
{
    if (cmd == NULL)
    {
        return NULL;
    }

    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    size_t total_len = 512; // 缓冲区总容量
    size_t used_len = 0;    // 缓冲区已使用容量
    char *result = (char *)malloc(total_len);
    if (result == NULL)
    {
        pclose(fp);

        return NULL;
    }
    result[0] = '\0';

    char read_data[512] = "";
    while (fgets(read_data, sizeof(read_data), fp) != NULL)
    {
        // 本次实际读取的长度
        size_t read_len = strlen(read_data);

        // 需要扩展缓冲区
        size_t need_len = used_len + read_len + 1;
        if (need_len > total_len)
        {
            size_t new_total_len = (total_len * 2 > need_len) ? total_len * 2 : need_len;
            char *new_result = (char *)realloc(result, new_total_len);
            if (new_result == NULL)
            {
                free(result);
                pclose(fp);

                return NULL;
            }
            result = new_result;
            total_len = new_total_len;
        }

        memcpy(result + used_len, read_data, read_len);
        used_len += read_len;
    }

    int ret = pclose(fp);
    if ((ret == -1) || (WIFEXITED(ret) == 0) || (WEXITSTATUS(ret) != 0))
    {
        free(result);

        return NULL;
    }
    result[used_len] = '\0';

    char *final_result = (char *)realloc(result, (used_len + 1));
    if (final_result != NULL)
    {
        result = final_result;
    }

    return result;
}

int gm_file_get_size(const char *file_name, size_t *file_size)
{
    if (file_name == NULL)
    {
        return -1;
    }

    if (file_size == NULL)
    {
        return -2;
    }

    struct stat file_stat = {0};
    if (stat(file_name, &file_stat) != 0)
    {
        return -3;
    }

    if (file_stat.st_size < 0)
    {
        return -4;
    }

    *file_size = (size_t)file_stat.st_size;

    return 0;
}

char *gm_file_read_content(const char *file_name)
{
    if (file_name == NULL)
    {
        return NULL;
    }

    size_t file_size = 0;
    if (gm_file_get_size(file_name, &file_size) != 0)
    {
        return NULL;
    }

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    char *file_content = (char *)malloc(file_size + 1);
    if (file_content == NULL)
    {
        fclose(fp);

        return NULL;
    }

    size_t ret = fread(file_content, 1, file_size, fp);
    fclose(fp);
    if (ret != file_size)
    {
        free(file_content);

        return NULL;
    }
    file_content[file_size] = '\0';

    return file_content;
}
