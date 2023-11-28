/*
 * Copyright (c) 2009-2012, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __INTSET_H
#define __INTSET_H
#include <stdint.h>

/* 整数集合的数据结构 */
typedef struct intset {
    uint32_t encoding; /* 编码，该编码决定了contents数组的int类型，支持16位、32位、64位 */
    uint32_t length; /* 元素长度 */
    int8_t contents[]; /* 元素，元素的类型不是int8_t，而是根据encoding动态强制转换 */
} intset;

/* 初始化一个整数集合 */
intset *intsetNew(void);
/* 向整数集合中添加一个整数 */
intset *intsetAdd(intset *is, int64_t value, uint8_t *success);
/* 向整数集合中移除一个整数 */
intset *intsetRemove(intset *is, int64_t value, int *success);
/* 断言整数集合是否包含一个整数 */
uint8_t intsetFind(intset *is, int64_t value);
/* 随机返回一个整数 */
int64_t intsetRandom(intset *is);
/* 按位置获取一个整数 */
uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value);
/* 返回整数集合的长度 */
uint32_t intsetLen(const intset *is);
/* 返回整数集合的字节数 */
size_t intsetBlobLen(intset *is);
/* 验证整数集合完整性 */
int intsetValidateIntegrity(const unsigned char *is, size_t size, int deep);

#ifdef REDIS_TEST
int intsetTest(int argc, char *argv[], int accurate);
#endif

#endif // __INTSET_H
