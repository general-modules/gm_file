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

    // 不是普通文件
    if (S_ISREG(file_stat.st_mode) == 0)
    {
        return -4;
    }

    if (file_stat.st_size < 0)
    {
        return -5;
    }

    *file_size = (size_t)(file_stat.st_size);

    return 0;
}

void *gm_file_read_raw(const char *file_name, const size_t max_len, size_t *out_len)
{
    if (file_name == NULL)
    {
        return NULL;
    }

    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL)
    {
        return NULL;
    }

    size_t total_len = 512; // 缓冲区总容量
    size_t used_len = 0;    // 缓冲区已使用容量

    // 初始容量不能超过 max_len
    if ((max_len > 0) && (total_len > max_len))
    {
        total_len = max_len;
    }

    char *file_content = (char *)malloc(total_len);
    if (file_content == NULL)
    {
        fclose(fp);

        return NULL;
    }

    while (true)
    {
        // 已读取 max_len 字节
        if ((max_len > 0) && (used_len >= max_len))
        {
            break;
        }

        // 扩容
        if (used_len == total_len)
        {
            size_t new_total_len = total_len * 2;

            // 扩容后不能超过 max_len
            if ((max_len > 0) && (new_total_len > max_len))
            {
                new_total_len = max_len;
            }

            char *new_file_content = (char *)realloc(file_content, new_total_len);
            if (new_file_content == NULL)
            {
                free(file_content);
                fclose(fp);

                return NULL;
            }
            file_content = new_file_content;
            total_len = new_total_len;
        }

        size_t ret = fread(&file_content[used_len], 1, total_len - used_len, fp);
        if (ret == 0)
        {
            // 读取到文件末尾
            if (feof(fp))
            {
                break;
            }

            // 出现错误
            if (ferror(fp))
            {
                free(file_content);
                fclose(fp);

                return NULL;
            }

            // 未知错误
            free(file_content);
            fclose(fp);

            return NULL;
        }

        used_len += ret;
    }

    fclose(fp);

    // 如果读的是空文件返回一个合法 buffer，但 out_len 为 0
    size_t final_len = used_len == 0 ? 1 : used_len;
    char *final_file_content = (char *)realloc(file_content, final_len);
    if (final_file_content == NULL)
    {
        free(file_content);

        return NULL;
    }
    file_content = final_file_content;

    if (used_len == 0)
    {
        file_content[0] = 0;
    }

    if (out_len != NULL)
    {
        *out_len = used_len;
    }

    return file_content;
}

char *gm_file_read_text(const char *file_name, const size_t max_len, size_t *out_len)
{
    if (file_name == NULL)
    {
        return NULL;
    }

    size_t out_len_tmp = 0;
    char *read_data = (char *)gm_file_read_raw(file_name, max_len, &out_len_tmp);
    if (read_data == NULL)
    {
        return NULL;
    }

    // 截断到实际读取的长度
    char *tmp_data = (char *)realloc(read_data, out_len_tmp + 1);
    if (tmp_data == NULL)
    {
        free(read_data);

        return NULL;
    }
    read_data = tmp_data;
    read_data[out_len_tmp] = '\0';

    if (out_len != NULL)
    {
        *out_len = out_len_tmp;
    }

    return read_data;
}
