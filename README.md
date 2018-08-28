# LLVM 6 Passes

A collection of mildly useful LLVM 6 passes.

## Setup

```sh
./setup.sh
./build.sh

# Run a simple pass
./run_printo.sh
```

**Note:** if you have enough RAM, kill `setup.sh` when it starts compiling,
`cd llvm_build/` and then `make -j $NUMBER_OF_PROCESSES`.

### How to add a pass

* Append `add_subdirectory(passes/passname)` to `CMakeLists.txt`
* Copy `passes/printo/*` to `passes/passname/` and rename what needs renaming
* `./build.sh` :)

## Passes

### Printo

Instrumentation pass that makes a program print its IR while it is executing.

Output:

```sh
  %call = tail call i32 @puts(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str, i64 0, i64 0))
Show me your character:
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !tbaa !2
  %call.i = tail call i32 @_IO_getc(%struct._IO_FILE* %0) #2
a  
  %sext.mask = and i32 %call.i, 255
  %cmp = icmp eq i32 %sext.mask, 80
  br i1 %cmp, label %if.then, label %if.else
  %call5 = tail call i32 @puts(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.2, i64 0, i64 0))
Looks like we got a non drinker here, sad
  br label %if.end
  ret i32 0
```

