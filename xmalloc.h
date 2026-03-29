#ifndef XMALLOC_H
#define XMALLOC_H

#include "list.h"
#include <stdio.h>
#include <pthread.h>

#define FILE_LENGTH     128
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

//宏定义实现代码中调用malloc/free时调用我们目标函数
#define xmalloc(size)         malloc_hook(size, __FILE__, __LINE__)
#define xfree(p)                 free_hook(p,  __FILE__, __LINE__)

void malloc_init();
void *malloc_hook(size_t size, const char* file, int line);
void free_hook(void *ptr, const char* file, int line);
void malloc_print() ;

#endif