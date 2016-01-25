/**
    * File Name: src/common.c
    * Author: Louis Xu
    * Mail: louis_xu_ustc@163.com
    * Created Time: 01/25/16
*/

#include <stdlib.h>
#include "common.h"
#include "print.h"

int xmalloc(size_t size, void *p)
{
    int ret = 0;
    
    p = malloc(size);
    if (!p) {
        log_err("malloc error!\n");
        ret = -1;
    }

    return ret;
}

