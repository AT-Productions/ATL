section .data
    msg db 'Hello, World!',0x0D,0x0A, 0
    msg_len equ $ - msg

section .text
    extern GetStdHandle
    extern WriteFile
    extern ExitProcess
    global main

main:
    ; Get handle to stdout
    sub rsp, 28h             ; Shadow space for Win64 ABI
    mov rcx, -11                
    call GetStdHandle

    ; Write the message to stdout
    mov r9, rsp              ; lpNumberOfBytesWritten (address of buffer)
    mov r8d, msg_len         ; nNumberOfBytesToWrite
    mov rdx, msg             ; lpBuffer
    mov rcx, rax             ; hFile (stdout handle)
    call WriteFile

    ; Exit the process
    xor ecx, ecx             ; Exit code 0
    call ExitProcess
