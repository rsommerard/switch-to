#ifndef _SWITCH_TO_H
#define _SWITCH_TO_H

#define MAGIC 0xDEADBEEF

enum state_e
{
    CTX_FINISHED,
    CTX_RUNNING,
    CTX_INITIALIZED
};

typedef void (func_t)(void*);

struct ctx_s
{
    void* ctx_esp;
    void* ctx_ebp;
    func_t* ctx_f;
    void* ctx_args;
    void* ctx_stack;
    enum state_e ctx_state;
    int ctx_magic;
};

void switch_to_ctx(struct ctx_s *ctx);

int init_ctx(struct ctx_s* ctx, int stack_size, func_t f, void* args);

#endif
