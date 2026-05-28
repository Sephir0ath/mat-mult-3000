# mat-mult-3000
-
Implementación de distintos algoritmos de multiplicación de matrices, incluyendo el algoritmo clásico, el algoritmo de Strassen y un enfoque híbrido que combina ambos métodos. La versión híbrida aplica recursivamente el algoritmo de Strassen hasta que las submatrices alcanzan un tamaño _n_, momento en el cual cambia al algoritmo clásico de multiplicación de matrices.

## Compilación
Si se quiere hacer tests es necesario descargar este [repositorio](https://github.com/leonardlover/uhr)  y modificar el código para ejecutar los métodos que están en el archivo de `matrixmultiplication.cpp`.

Para el main se puede ejecutar el makefile como:
```bash
make
```
Pero también se puede hacer: 
```bash
g++ main.cpp -o exec
```

Ahora para la búsqueda del mejor _n_<sub>0</sub> (valor en donde el algoritmo híbrido empieza a utilizar el algoritmo de multiplicación clásica) se puede compilar de la siguiente manera:
```bash
g++ -std=c++11 -O3 findn0.cpp -o findn0
```

## Ejecución
```bash
./exec
```
Esto va a comprobar las instancias de ejemplo dentro de la carpeta de `instances`.

Y para ejecutar el archivo de findn0:
```bash
./findn0 <output.csv> <val>
```

siendo _val_ la máxima potencia de dos para realizar la búsqueda del _n_<sub>0</sub> 
## Colaboradores ✨
* [Juan Felipe Raysz Muñoz](https://github.com/Sephir0ath)
* [Oliver Isaías Peñailillo Sanzana](https://github.com/pyrrss)
* [Francisca Nuñez Larenas](https://github.com/sshiro0)
