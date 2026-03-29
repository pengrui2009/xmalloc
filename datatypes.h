#ifndef DATATYES_H
#define DATATYES_H

#include "list.h"
#include <stdio.h>
#include <pthread.h>

// 记录文件名信息
#define FILE_LENGTH     128
// 最大调用malloc次数的数量
#define MEM_BLOCK_NODE_MAX 3000

typedef struct _tag_xmalloc_block_t { 
    void *ptr;
    size_t size;
    char file[FILE_LENGTH];
    int line;
} xmalloc_block_t;

typedef struct _tag_xmalloc_block_node_t { 
    struct list_head list;
    xmalloc_block_t *data_ptr;
} xmalloc_block_node_t;

typedef struct _tag_xmalloc_block_list_t {
    struct list_head list_busy;
    struct list_head list_idle;
    pthread_mutex_t mutex;
    xmalloc_block_node_t nodepool[MEM_BLOCK_NODE_MAX];
} xmalloc_block_list_t;



#endif /* DATATYES_H */