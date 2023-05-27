# computerenhance homework - 8086 MOV instructions.
Just some homework I did for the course at computerenhance.com\
My code here is fairly hacky, and shouldn't be used for anything other than an overview!

I finished the extra listing (40) just for fun, there is still one case I haven't dealt with, but I think that's fine.

The output from running this:
```asm
; Homework 0037
mov cx, bx

; Homework 0038
mov cx, bx
mov ch, ah
mov dx, bx
mov si, bx
mov bx, di
mov al, cl
mov ch, ch
mov bx, ax
mov bx, si
mov sp, di
mov bp, ax

; Homework 0039
mov si, bx
mov dh, al
mov cl, 12
mov ch, 244
mov cx, 12
mov cx, 65524
mov dx, 3948
mov dx, 61588
mov al, [bx + si]
mov bx, [bp + di]
mov dx, [bp]
mov ah, [bx + si + 4]
mov al, [bx + si + 4999]
mov [bx + di], cx
mov [bp + si], cl
mov [bp], ch

; Homework 0040
mov ax, [bx + di + 219]
mov [si + 65236], cx
mov dx, [bx + 224]
mov [bp + di], byte 7
mov [di + 901], word 347
mov bp, [5]
mov bx, [3458]
mov ax, [2555]
mov ax, [16]
mov [2554], ax
mov [15], ax
```
