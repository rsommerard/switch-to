#include "switch_to.h"
#include <assert.h>
#include <stdlib.h>

struct ctx_s* ctx_current = NULL;

void switch_to_ctx(struct ctx_s *ctx)
{
    if(ctx_current)
    {
        asm("mov %%esp, %0" "\n\t" "mov %%ebp, %1"
            : "=r" (ctx_current->ctx_esp), "=r" (ctx_current->ctx_ebp));
    }
    
    ctx_current = ctx;
    
    assert(ctx_current->ctx_state != CTX_FINISHED);
    
    asm("mov %0, %%esp" "\n\t" "mov %1, %%ebp" 
        :
        : "r" (ctx_current->ctx_esp), "r" (ctx_current->ctx_ebp));
    
    if(ctx_current->ctx_state == CTX_INITIALIZED)
    {
        ctx_current->ctx_state = CTX_RUNNING;
        ctx_current->ctx_f(ctx_current->ctx_args);
        ctx_current->ctx_state = CTX_FINISHED;
        while(1);
    }
    else
    {
        return;
    }
}

int init_ctx(struct ctx_s* ctx, int stack_size, func_t f, void* args)
{
    ctx->ctx_stack = (void*)malloc(stack_size);
    ctx->ctx_f = f;
    ctx->ctx_args = args;
    ctx->ctx_state = CTX_INITIALIZED;
    ctx->ctx_ebp = (char*)(ctx->ctx_stack) + stack_size - sizeof(void*);
    ctx->ctx_esp = ctx->ctx_ebp;
    ctx->ctx_magic = MAGIC;
    
    return 0;
}
