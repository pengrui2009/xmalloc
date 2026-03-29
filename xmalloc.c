#include "xmalloc.h"
#include <string.h>
#include <stdlib.h>

static xmalloc_block_list_t blockinfo;

void malloc_init() {
    
    INIT_LIST_HEAD(&blockinfo.list_idle);
    INIT_LIST_HEAD(&blockinfo.list_busy);
    for (int i=0; i<MEM_BLOCK_NODE_MAX; i++) {
        list_add(&blockinfo.nodepool[i].list, &blockinfo.list_idle);
    }
}

//实现目标函数
void *malloc_hook(size_t size, const char* file, int line)
{
    //这里还是通过文件的方式进行识别
    xmalloc_block_node_t *pnode;
    struct list_head *plist_busy;
    struct list_head *plist_idle;

    
    void *ptr =malloc(size);
    // char file_name_buff[MEM_FILE_LENGTH] = {0};
    // sprintf(file_name_buff, "./mem/%p.mem", ptr);
    //打开文件写入必要信息 使用前创建目录级别
    // FILE *fp = fopen(file_name_buff, "w");
    // fprintf(stdout, "[file:%s  line:%d ] ---->mem:%p  size:%lu \n",file, line, ptr, size);
    // fflush(fp); //刷新写入文件
    pthread_mutex_lock(&blockinfo.mutex);
    // printf("file:%s func:%s line:%d \n", __FILE__, __func__, __LINE__);
    plist_busy = &blockinfo.list_busy;
    plist_idle = &blockinfo.list_idle;
    if (list_empty(plist_idle)) {
        printf("list is empty.\n");
        return NULL;
    }
    pnode = list_first_entry(plist_idle, xmalloc_block_node_t, list);
    xmalloc_block_t *data_ptr = (xmalloc_block_t *)malloc(sizeof(xmalloc_block_t));

    data_ptr->ptr = ptr;
    data_ptr->size = size;
    strncpy(data_ptr->file, file, FILE_LENGTH);
    data_ptr->line = line;

    pnode->data_ptr = data_ptr;
    // xmalloc_block_node_t *node_ptr = (xmalloc_block_node_t *)malloc(sizeof(xmalloc_block_node_t));
    // data_ptr->ptr = ptr;
    // data_ptr->size = size;
    // data_ptr->file = file;
    // data_ptr->line = line;
    // mem_info_head->next = data_ptr;
    // printf("exec malloc [%p:%lu], file: %s, line:%d size:%lu\n", ptr, size, file, line, size );

    list_del(&pnode->list);
    list_add(&pnode->list, plist_busy);

    pthread_mutex_unlock(&blockinfo.mutex);

    return ptr;
}

void free_hook(void *ptr, const char* file, int line)
{
    int flag = 0;
    xmalloc_block_node_t *pnode;
    struct list_head *plist_busy;
    struct list_head *plist_idle;
    // char file_name_buff[MEM_FILE_LENGTH] = {0};
    // sprintf(stdout, "./mem/%p.mem", p);
    
    // if(unlink(file_name_buff) <0)
    // {
    //     printf("double free: %p, file: %s. line :%d \n", p, file, line);
    // }
    
    //这里的打印实际就没意义了
    pthread_mutex_lock(&blockinfo.mutex);

    // printf("exec free [%p], file: %s line:%d \n", ptr, file, line);
    free(ptr);

    plist_busy = &blockinfo.list_busy;
    plist_idle = &blockinfo.list_idle;
    list_for_each_entry(pnode, plist_busy, list) {
        if (pnode->data_ptr->ptr == ptr) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        list_del(&pnode->list);
        list_add(&pnode->list, plist_idle);
    }
    
    pthread_mutex_unlock(&blockinfo.mutex);
}

void malloc_print() 
{
    struct list_head *plist_busy;
    xmalloc_block_node_t *pnode;
    pthread_mutex_lock(&blockinfo.mutex);
    
    plist_busy = &blockinfo.list_busy;

    list_for_each_entry(pnode, plist_busy, list) {
        printf("[file:%s  line:%d ] ---->mem:%p  size:%lu \n", 
            pnode->data_ptr->file, pnode->data_ptr->line, pnode->data_ptr->ptr, pnode->data_ptr->size);
    }

    pthread_mutex_unlock(&blockinfo.mutex);
}


