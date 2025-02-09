//--------------------------------------------------------------------------------------------------
//                                  Arena Implementation Exercises
//--------------------------------------------------------------------------------------------------
// Exercise #1: A Fixed-Capacity Arena
//  - Write an arena implementation
//  - This arena should operate on a fixed-capacity buffer, and not grow at all.
//  - It can obtain this buffer via malloc or equivalent.
//  - If the arena runs out of space, panic.
//--------------------------------------------------------------------------------------------------
// Exercise #2: The Chaining Upgrade
//  - Extend your arena implementation from Exercise #1 by allowing growth via chaining.
//  - It can obtain each new chunk via malloc or equivalent.
//  - It should require no API changes - optionally, you may use this step to remove the
//    capacity parameter in ArenaAlloc, or to extend ArenaAlloc's parameters to include
//    dynamic setting of the feature.
//--------------------------------------------------------------------------------------------------
// Exercise #3: Using the MMU
//  - Extend your arena implementation from Exercise #2 by allowing growth within a single
//    chunk via initial virtual address space reservation, with physical memory backing
//    pages only as necessary.
//  - Address space reservation cannot be done with malloc - it will require OS-specific APIS
//    like VirtualAlloc (Windows) or mmap (Linux).
//  - It should require no API changes - but you can also dynamically enable this feature.
//--------------------------------------------------------------------------------------------------
// Exercise #4: Humiliating std::vector
//  - Use your arena from #3 to implement a growing dynamic array which never relocates.
//--------------------------------------------------------------------------------------------------
// Exercise #5: Supporting Sub-Lifetimes
//  - Use your arena to implement a simple growing pool allocator, using a free list.
//  - This should be only for N known sizes, where N is small and statically known (like 1).
//--------------------------------------------------------------------------------------------------
// Exercise #6: Visualization & Debugging
//  - Extend your arena with optionally-enabled diagnostics logging, which - for each 
//    push & pop - logs timestamps, caller source code location, and arena allocation position.
//  - Use this logging in a visualizer.
//--------------------------------------------------------------------------------------------------
// Exercise #7: Convert Real Code
//  - Use your arena allocator, and bag of techniques, in an existing codebase which uses
//    non-arena, malloc/free style memory management - a suitable example may be a parsing
//    library, a compiler, or a game.
//  - Convert the whote thing, or a reasonable subset of it.
//  - Measure performance before and after.
//  - Measure LOC before and after, if you're able to entirely eliminate dependence on
//    malloc/free, in both usage/implementation code.
//--------------------------------------------------------------------------------------------------

// @TODO(Brady): Eventually this will be removed in favor for OS-specific headers
#include <stdlib.h>

typedef struct Arena Arena;
struct Arena
{
    u64 pos;
    u64 capacity;
};

// @TODO(Brady): Should this be aligned?
#define ARENA_HEADER_SIZE sizeof(Arena)

internal Arena *ArenaAlloc(u64 capacity)
{
    Arena *arena = malloc(capacity);
    arena->pos = ARENA_HEADER_SIZE;
    arena->capacity = capacity;
    
    return arena;
}

internal void ArenaRelease(Arena *arena)
{
    free(arena);
}

internal void ArenaSetAutoAlign(Arena *arena, u64 align)
{
    // @TODO(Brady): Implement this
}


internal u64 ArenaPos(Arena *arena)
{
    return arena->pos;
}


internal void *ArenaPush(Arena *arena, u64 size)
{
    Assert(arena->pos + size <= arena->capacity);
    
    void *memory = (u8 *)arena + arena->pos;
    arena->pos += size;
    
    return memory;
}

internal void *ArenaPushAligner(Arena *arena, u64 alignment)
{
    // @TODO(Brady): Implement this
    return (void *)0;
}

internal void *ArenaPushZero(Arena *arena, u64 size)
{
    void *memory = ArenaPush(arena, size);
    
    u8 *byte = (u8 *)memory;
    while (size--)
    {
        *byte++ = 0;
    }
    
    return memory;
}


internal void ArenaPopTo(Arena *arena, u64 pos)
{
    // @TODO(Brady): This needs to be a bit smarter; zero/poison memory?
    arena->pos = Maximum(ARENA_HEADER_SIZE, pos);
}

internal void ArenaPop(Arena *arena, u64 size)
{
    u64 currentPos = arena->pos;
    u64 newPos = currentPos;
    if (size < currentPos)
    {
        newPos = currentPos - size;
    }
    ArenaPopTo(arena, newPos);
}

internal void ArenaClear(Arena *arena)
{
    ArenaPopTo(arena, 0);
}

#define PushStruct(arena, type)           ArenaPush((arena), sizeof(type))
#define PushStructZero(arena, type)       ArenaPushZero((arena), sizeof(type))

#define PushArray(arena, type, count)     ArenaPush((arena), sizeof(type) * (count))
#define PushArrayZero(arena, type, count) ArenaPushZero((arena), sizeof(type) * (count))

#define PushSize(arena, size)             ArenaPush((arena), (size))
#define PushSizeZero(arena, size)         ArenaPushZero((arena), (size))
