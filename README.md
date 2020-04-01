# SO-Proyecto
Proyeto SO


## Para compilar usando GCC no terminal:

```
gcc main.c -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c  -lcrypto -o main.bin
```

## Para compilar usando GCC no Zinjal:

* main.c Run-> Configure -> Extra arguments for compiler:

```
 -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c -lcrypto
```