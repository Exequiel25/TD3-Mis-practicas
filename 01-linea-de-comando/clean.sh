#!/usr/bin/env sh
echo "Limpiando..."

# Eliminar la carpeta "~/ejercicio_bash" del ejercicio 1
if [ -d ~/ejercicio_bash ]; then
    rm -r ~/ejercicio_bash
    echo "Carpeta ~/ejercicio_bash eliminada"
fi

# Eliminar la carpeta "~/ejercicio_bash_avanzado" del ejercicio 2
if [ -d ~/ejercicio_bash_avanzado ]; then
    rm -r ~/ejercicio_bash_avanzado
    echo "Carpeta ~/ejercicio_bash_avanzado eliminada"
fi

# Eliminar la carpeta "~/ejercicio_rutas" del ejercicio 3
if [ -d ~/ejercicio_rutas ]; then
    rm -r ~/ejercicio_rutas
    echo "Carpeta ~/ejercicio_rutas eliminada"
fi

# Eliminar el ejecutable de c "output" del ejercicio en manejo de flujo
if [ -f output ]; then
    rm output
    echo "Ejecutable 'output' eliminado"
fi

# Eliminar el archivo stdout creado en el 2do ejercicio de manejo de flujo
if [ -f stdout.txt ]; then
    rm stdout.txt
    echo "Archivo 'stdout' eliminado"
fi

# Eliminar el archivo error.txt creado en el 3er ejercicio de manejo de flujo
if [ -f error.txt ]; then
    rm error.txt
    echo "Archivo 'error.txt' eliminado"
fi