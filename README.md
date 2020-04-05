# SO-Proyecto
Proyeto SO


## Para compilar usando GCC no terminal:

```
gcc main.c -std=c99 `mysql_config --cflags --libs` fmd5.c basedados.c servidor.c lista.c -lcrypto -lm -o main.bin
```

## Para compilar usando GCC no Zinjal:

* (main.c) Run-> Configure -> Extra arguments for compiler:

```
-std=c99 `mysql_config --cflags --libs` fmd5.c basedados.c servidor.c lista.c -lcrypto -lm
```


