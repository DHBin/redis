#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "learn.h"
#include "quicklist.h"
#include "ziplist.h"
#include "sds.h"
#include "server.h"

void learn_sds();

/* 压缩链表 */
void learn_ziplist();

/* 快速链表 */
void learn_quicklist();

/* 跳跃表 */
void learn_zsl();

// =========util=========
void println();
void randomStr(char* str, size_t len);
// =========util=========

int learn() {
//    learn_sds();
//    learn_ziplist();
    learn_quicklist();
//    learn_zsl();
    return 0;
}

void learn_sds() {
    sds s = sdsnew("dhb");
    printf("sds: %s\n", s);
    println();
}

void learn_ziplist() {
    /* 创建一个ziplist */
    unsigned char *zl = ziplistNew();
    char *s = "dhbh";
    zl = ziplistPush(zl, (void *) s, 5, ZIPLIST_HEAD);
    char *ss = malloc(254);
    /* 长度大于等于254的情况 */
    zl = ziplistPush(zl, (void *) ss, 254, ZIPLIST_HEAD);

    unsigned int len = ziplistLen(zl);
    printf("ziplist len: %d\n", len);

    unsigned char *p = ziplistIndex(zl, -1);
    while (p != NULL) {
        unsigned char *vstr;
        unsigned int vlen;
        long long vlong;
        ziplistGet(p, &vstr, &vlen, &vlong);
        if (vstr) {
            printf("len : %d value: %s\n", vlen, vstr);
        } else {
            printf("len : %d value: %lld\n", vlen, vlong);
        }
        p = ziplistPrev(zl, p);
    }

    println();
}

void learn_quicklist() {
    quicklist *list = quicklistCreate();
    quicklistPushHead(list, "hello", 6);
    quicklistPushHead(list, "xxx", 4);
    quicklistPushHead(list, "xxxx", 5);

    unsigned long count = quicklistCount(list);
    printf("快速链表的长度：%lu\n", count);
    /* 快速链表迭代器 */
    quicklistIter *li = quicklistGetIterator(list, AL_START_HEAD);
    quicklistEntry entry;
    /* 遍历，取节点 */
    while (quicklistNext(li, &entry)) {
        printf("str: %s\n", entry.value);
    }
    println();
}

void learn_zsl() {

    zskiplist *zsl = zslCreate();
    for(int i = 2; i < 1000; i++) {
        char str[i];
        randomStr(str, i);
        zslInsert(zsl, i, sdsnew(str));
    }
//    zslInsert(zsl, 10, sdsnew("10"));
//    zslInsert(zsl, 17, sdsnew("17"));
//    zslInsert(zsl, 500, sdsnew("500"));
//    zslInsert(zsl, 11, sdsnew("11"));
//    zslInsert(zsl, 1, sdsnew("1"));
//    zslInsert(zsl, 600, sdsnew("600"));



    zrangespec range;
    range.max = 985;
    range.min = 500;
    range.minex = 1;
    range.maxex = 0;
    zskiplistNode *node = zslFirstInRange(zsl, &range);
    zskiplistNode *node1 = zslLastInRange(zsl, &range);

    println();
}

void randomStr(char* str, size_t len) {
    char* chars = "abcdefghijklmnopqrstuvwxyz";
    int position = 0;
    str[len--] = '\0';
    while(len--) {
        position = random() & 25;
        str[len] = chars[position];
    }
}

void println() {
    printf("====================\n");
}
