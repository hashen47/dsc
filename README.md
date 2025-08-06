# DSC

simple generic datastructure implementations for c

# Features
- assert
- array
- stack
- queue

# Build 

## Linux

prerequisites (make, gcc)
```console
    $ make clean
    $ make run
    $ make test   # this is not mandatory
``` 
- after you running above commands `so` folder have the shared library (`libds.so`)
- after you running above commands `static` folder have the static library (`libds.a`)

# How to
- [assert examples](./examples/assert_examples.c)
- [array examples](./examples/array_examples.c)
- [stack examples](./examples/stack_examples.c)
- [queue examples](./examples/queue_examples.c)

# Errors

## Internal Errors
- if error is internal (mean memory allocation, reallocation etc...), return empty values correspond to that.
    + as an example ARRAY_INIT is fail return *NULL*.
    + also if ARRAY_APPEND fails because of internal error return *false*.
- be careful when append, insert, replace values (because we don't check value type), so only append, insert or replace values in array initialize type.

## User Errors 
- as an example if you try to access index beyond the array size or try to access negative index, try to pop empty array, try to replace invalid index then ASSERT will happend.
- so keep this mind.
