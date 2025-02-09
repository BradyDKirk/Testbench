#include "base.h"
#include "arena.c"

int main(int argc, char *argv[])
{
    Arena *arena = ArenaAlloc(KB(4));
    
    i32 *intArray = PushArray(arena, i32, 1020);
    
    ArenaRelease(arena);
    return 0;
}
