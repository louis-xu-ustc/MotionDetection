/**
    * File Name: src/diff2.c
    * Author: Louis Xu
    * Mail: louis_xu_ustc@163.com
    * Created Time: 01/26/16
*/

#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "diff2.h"
#include "print.h"

#define MD_DEFAULT_THRESHOLD 16

static int g_md_started_flag = 0;
static md_config_t g_config = {0};
static md_session_t g_ms = {
    .T = MD_DEFAULT_THRESHOLD,
};

int md_get_config(md_config_t *config)
{
    if (!config) {
        log_err("invalid config ptr!\n");
        return -1;
    }
    memcpy(config, &g_config, sizeof(md_config_t));
    return 0;
}

int md_set_config(md_config_t *config)
{
    if (!config) {
        log_err("invalid config ptr!\n");
        return -1;
    }
    memcpy(&g_config, config, sizeof(md_config_t));
    return 0;
}

int md_start_session(md_config_t *config)
{
    u32 w, h, p, size;
    void *q = NULL;

    if (config->width > MD_MAX_WIDTH || config->width < 0) {
        log_err("invalid config width!\n");
        return -1;
    }
    if (config->height > MD_MAX_HEIGHT || config->height < 0) {
        log_err("invalid config height!\n");
        return -1;
    }

    w = config->width;
    h = config->height;
    p = config->pitch;

    size = p * h;
    q = xmalloc(size*sizeof(md_pixel_t));
    g_ms.data = q;

    size = w * h;
    q = xmalloc(size*sizeof(u8));
    g_ms.fg = (u8 *)q;
    g_ms.count = 0;

    g_md_started_flag = 1;

    return 0;
}

int md_update_session(md_session_t *ms, const u8 *ptr)
{
    int i, j;
    u32 width = g_config.width;
    u32 height = g_config.height;
    u32 pitch = g_config.pitch;
    u32 size = width*height;
    u8 *fg = ms->fg;
    md_pixel_t *pixel = (md_pixel_t *)ms->data;
    u32 T = ms->T;
    const u8 *q = ptr;
    u32 diff;
    u32 max = 0;

    if (!ptr) {
        log_err("invalid data ptr!\n");
        return -1;
    }

    for (i = 0; i < height; i++, pixel+=pitch, q+=pitch) {
        for (j = 0; j < width; fg++) {
            if (ms->count) {
                diff = abs(*(q+j) - (pixel+j)->data);
                if (diff >= T) {
                    *fg = 1; 
                } else {
                    *fg = 0;
                }
                if (diff > max) {
                    max = diff;
                }
            }
            (pixel+j)->data = *(q+j);
        }
    }

    //TODO
    fg = ms->fg;
    if (max < 2*T) {
        for (i = 0; i < size; i++, fg++) {
           *fg = 0;
        }
    }

    if (!ms->count) {
        ms->count++;
    }

    return 0;
}

int md_stop_session(md_session_t *ms)
{
    if (!g_md_started_flag) {
        log_err("invalid session status!\n");
        return -1;
    }
    if (ms->data) {
        free(ms->data);
        ms->data = NULL;
    }
    if (ms->fg) {
        free(ms->fg);
        ms->fg = NULL;
    }
    g_md_started_flag = 0;

    return 0;
}

