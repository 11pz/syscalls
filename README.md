# syscalls
the simplest library for direct syscalls.
# usage
theres a simple example: syscall::Call<ULONG>("NtWriteVirtualMemory", GetCurrentProcess(), test, buffer, sizeof(buffer), NULL);
have fun!
