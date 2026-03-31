#ifndef XMALLOC_H
#define XMALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

extern void xmalloc_init();
extern void *xmalloc_hook(size_t size, const char* file, int line);
extern void xfree_hook(void *ptr, const char* file, int line);
extern void xmalloc_print() ;
extern void xmalloc_deinit();

#ifdef __cplusplus
}
#endif

//宏定义实现代码中调用malloc/free时调用我们目标函数
#define malloc(size)         xmalloc_hook(size, __FILE__, __LINE__)
#define free(p)              xfree_hook(p,  __FILE__, __LINE__)



#endif
