/**
 * @file      gm_file.h
 * @brief     文件模块头文件
 * @author    huenrong (sgyhy1028@outlook.com)
 * @date      2026-02-16 16:21:14
 *
 * @copyright Copyright (c) 2026 huenrong
 *
 */

#ifndef __GM_FILE_H
#define __GM_FILE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define GM_FILE_VERSION_MAJOR 1
#define GM_FILE_VERSION_MINOR 1
#define GM_FILE_VERSION_PATCH 0

/**
 * @brief 执行命令并获取输出结果
 *
 * @note 1. 仅适用于返回文本结果的命令，不适用于返回二进制结果的命令
 *       2. 由调用者负责释放返回的内存
 *
 * @param[in] cmd: 待执行命令(cmd 必须是可信输入，防止命令注入)
 *
 * @return 成功: 命令结果
 * @return 失败: NULL
 */
char *gm_file_exec_cmd(const char *cmd);

/**
 * @brief 获取文件大小
 *
 * @note 仅适用于普通文件，不适用于 /sys， /proc 等特殊文件
 *
 * @param[in]  file_name: 文件名
 * @param[out] file_size: 文件大小(单位: 字节)
 *
 * @return 0 : 成功
 * @return <0: 失败
 */
int gm_file_get_size(const char *file_name, size_t *file_size);

/**
 * @brief 读取文件原始内容
 *
 * @note 1. 由调用者负责释放返回的内存
 *       2. 如果读取的是一个空文件, 返回的数据指向一个空字符串，而不是 NULL，但是 out_len 为 0
 *
 * @param[in]  file_name: 文件名
 * @param[in]  max_len  : 最大读取长度(单位: 字节, 0: 不限制)
 * @param[out] out_len  : 实际读取长度(单位: 字节, NULL: 不返回)
 *
 * @return 成功: 文件内容
 * @return 失败: NULL
 */
void *gm_file_read_raw(const char *file_name, const size_t max_len, size_t *out_len);

/**
 * @brief 读取文本文件内容
 *
 * @note 1. 由调用者负责释放返回的内存
 *       2. 返回的数据以 '\0' 结尾
 *       3. 如果读取的是一个空文件, 返回的数据指向一个空字符串，而不是 NULL，但是 out_len 为 0
 *
 * @param[in]  file_name: 文件名
 * @param[in]  max_len  : 最大读取长度(单位: 字节, 0: 不限制)
 * @param[out] out_len  : 实际读取长度(单位: 字节, NULL: 不返回)
 *
 * @return 成功: 文件内容
 * @return 失败: NULL
 */
char *gm_file_read_text(const char *file_name, const size_t max_len, size_t *out_len);

#ifdef __cplusplus
}
#endif

#endif // __GM_FILE_H
