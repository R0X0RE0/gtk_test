# GTK Test
<br/>

### Note : This isn't really a huge project I'm working on, just a GTK playground for me. <br/>

## Compiling and Running on Linux <br/>

(might also work on MSYS2 on Windows or something I dunno)<br/>

Run this command
```
gcc -o gtk_test main.c `pkg-config --cflags --libs gtk4`
```

Now on Linux, to execute, run
```
./gtk_test
```

## KNOWN BUG :

- Submit Button doesn't work properly (really the only reason it's on GitHub in the first place lol)
