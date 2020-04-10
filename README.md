# SO-Proyecto
Proyeto SO


## Para compilar usando GCC en terminal:

```
gcc main.c -std=c99 `mysql_config --cflags --libs` fmd5.c basedados.c servidor.c lista.c -lcrypto -lm -o main.bin
```

## Para compilar usando GCC en Zinjal:

* (main.c) Run-> Configure -> Extra arguments for compiler:

```
-std=c99 `mysql_config --cflags --libs` fmd5.c basedados.c servidor.c lista.c -lcrypto -lm
```

## Ps.: Si obtiene errores al compilar en Zinjal:

* Debe borrar los .bin de la carpeta (Pasa de as veces no borrar):

```
rm *.bin
```
