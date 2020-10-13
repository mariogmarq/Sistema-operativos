# Tema 2: Repaso de conceptos
## Por Mario García Márquez

## 1)
En este caso, al hacer P2 una llamada al sistema pidiendo leer desde un dispositivo de E/S el
sistema operativo pasa a bloqueado al proceso P2 hasta que el dispositivo de lectura haya terminado
su labor. Mientras P2 no está ejecutándose el planificador pondrá en estado de "Ejecutando" a otro
proceso, en este caso P1. P2 no será ejecutado hasta que su petición anterior haya sido cumplida y
P1 se detenga ya sea por solicitar también por solicitar recursos adicionales o por que finalice. 

El dispositivo de E/S lanzará una excepción cuando acabe notificando así al procesador de que ha
terminado la transmisión de datos. Este esquema supone que el SO no es de tiempo compartido en cuyo
caso una vez acabado la transmisión de datos el proceso P2 podría volver a ejecutarse sin que P1 se
solicitase leer/escribir o acabase, bastaría con que se le acabara su tiempo límite.

## 2)
Un hilo es una serie de instrucciones muy cortas que pueden ser ejecutadas por el sistema operativo.
La principal diferencia con un proceso es que los procesos en general son independientes mientras
que las hebras en gran medida comparten datos en común permitiendo en muchos sistemas operativos un
cambio más rápido entre hilos que entre procesos.

Dos hilos dentro de un mismo proceso comparten tanto datos como espacios de direcciones lo que
permite la velocidad de cambio ya mencionada.
