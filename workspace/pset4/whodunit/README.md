# Questions

## What's `stdint.h`?

Specifies Interger width. stdint.h is a header file.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

TODO

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE`: 1 Byte
`DWORD`: 4 Bytes
`LONG`: 4 bytes
`WORD`: 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes in a BMP file are the `BITMAPFILEHEADER` and the `BITMAPINFOHEADER`.
These files specify information (metadata) about the bitmap image.

## What's the difference between `bfSize` and `biSize`?

`bfsize` includes the size of the header files, while `bisize` is the size of the BMP excluding the header files.T

## What does it mean if `biHeight` is negative?

The Origin is changed to the upper left of the image.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` specifies the color depth.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

While opening a file for read, if the file doesn't exist, or if there are no more file descriptors, then `fopen` will return `NULL`.
While opening a file for write, if there are permission issues, or if there are no more file descriptors, then `fopen` will return `NULL`.

## Why is the third argument to `fread` always `1` in our code?

The number of triples we need to read is always one, as we are iterating through the bitmap values, and we only need to access one
color value at a time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

2 (check)

## What does `fseek` do?

`fseek` skips over padded triples in a bmp file, and seeks the next RGBtriple

## What is `SEEK_CUR`?

TODO
