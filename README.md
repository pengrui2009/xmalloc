基于自定义malloc，实现内存泄漏的定位代码：
1. C语言开发，兼容C++
2. Android、Linux、Windows系统均可兼容
3. 代码简洁，不额外依赖三方库

示例代码：
'''
#include <stdio.h>
#include "xmalloc.h"


int main(int argc, char *argv[]) {
    xmalloc_init();
    void *data_ptr = (void *)malloc(10);

    // xfree(data_ptr);
    xmalloc_print();

    xmalloc_deinit();
    return 0;
}
'''

编译运行输出:
'''
D:\workspace\xmalloc\build>.\xmalloc_test.exe
[file:D:/workspace/xmalloc/examples/xmalloc_test.c  line:7 ] ---->mem:000002200CC400C0  size:10
'''
