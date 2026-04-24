# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

Single C file; compile with GCC (requires POSIX threads and semaphores — Linux/WSL/MinGW):

```
gcc hello.c -o hello -lpthread
./hello
```

On Windows with MSVC, pthreads and POSIX semaphores are not available natively — a POSIX compatibility layer (e.g., pthreads-win32) or WSL is needed.

## What the code does

`hello.c` is a POSIX threading demo. It:

1. Detects the number of online CPU cores via `sysconf(_SC_NPROCESSORS_ONLN)`.
2. Creates one thread per core, each calling `print_thread_id`.
3. Uses a semaphore initialized to `MAX_CONCURRENT` (= N cores) to throttle concurrent execution.
4. Each thread waits on the semaphore, prints its thread ID, then signals.

## Known issues

- `semaphore` is declared as a local variable in `main` but referenced in `print_thread_id`, which won't compile — it needs to be a global or passed via the thread argument.
- `print_thread_id` is used before its definition with no forward declaration; move it above `main` or add a prototype.
- VLAs (`pthread_t threads[N]`) require C99 or later; compile with `-std=c99` or `-std=c11`.
