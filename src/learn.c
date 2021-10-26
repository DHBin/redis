#include <stdio.h>
#include "learn.h"
#include "quicklist.h"

/* 快速链表 */
void learn_quicklist();

int learn() {
    learn_quicklist();
    return 0;
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
}
