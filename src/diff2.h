/**
    * File Name: src/diff2.h
    * Author: Louis Xu
    * Mail: louis_xu_ustc@163.com
    * Created Time: 01/26/16
*/

#ifndef __DIFF2_H__
#define __DIFF2_H__

#include "basetype.h"

#define MD_MAX_WIDTH (1920)
#define MD_MAX_HEIGHT (1088)

typedef struct md_config_s
{
    u32 width;
    u32 height;
    u32 pitch;
} md_config_t;

typedef struct md_pixel_s
{
    u8 data;
} md_pixel_t;

typedef struct md_session_s
{
    u32 T;
    void *data;
    u8 *fg; //0:bg, 1:fg
    u32 count;
} md_session_t;

int md_get_config(md_config_t *config);
int md_set_config(md_config_t *config);
int md_start_session(md_config_t *config);
int md_update_session(md_session_t *ms, const u8 *ptr);
int md_stop_session(md_session_t *ms);

#endif
