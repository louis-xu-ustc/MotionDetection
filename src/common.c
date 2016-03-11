/**
    * File Name: src/common.c
    * Author: Louis Xu
    * Mail: louis_xu_ustc@163.com
    * Created Time: 01/25/16
*/

#include <stdlib.h>
#include <stdio.h>
#include "common.h"

void *xmalloc(size_t size)
{
    void *p =NULL;
    
    if (!size) {
        printf("size of malloc invalid!\n");
    }
    p = malloc(size);
    if (!p) {
        printf("malloc error!\n");
    }

    return p;
}

