# Cuestiones de repaso
## Por Mario García Márquez

### 2.
Una interrupción es una señal lanzada por un dispositivo de E/S notificando a la CPU que la
operación que estaba haciendo ha acabado. Una interrupción por software es un mecanismo de
comunicación entre un proceso y el sistema operativo para notificarle que necesita de su
intervención. Una excepción es una situación de error detectada por la CPU en tiempo de ejecución y
que requiere tratamiento por parte del sistema operativo.

Cuando se detecta una interrupción su tratamiento es prioritario:
    * Se almacena el estado de la ejecución del proceso en la PCB
    * Se pasa la CPU al modo supervisor
    * Se ejecuta el código del sistema operativo que realiza el tratamiento de esta.
    * Se devuelve el control al planificador del SO.

Las excepciones son un tipo de interrupción y su tratamiento normalmente consiste en terminar el
proceso que la ha lanzado.

### 3. 
En una arquitectura de modo dual el usuario pedirá servicio al SO y este entrará en modo kernel para
ejecutar el servicio solicitado si procede.

### 4.
En la e/s programa el sistema operativo deja determinado tiempo a cada operación de entrada y salida
cambiando entre estas periodicamente. En la e/s gestionadas por interrupciones es el dispositivo de
e/s el que le indica a la CPU cuando termina cada proceso evitando así un alto consumo de CPU en la
gestión de este dispositivo.

### 5.
Los procesos están formados por:
    * Las instrucciones de un programa para ser ejecutadas por el procesador.
    * El estado de ejecución del programa(los valores de los registros).
    * La memoria reservada por el programa y sus datos.
    * Otra información para su planificación que depende del SO.

Los procesos se dividen en pequeñas porciones llamadas páginas y cada proceso cuenta con su propia
tabla de paginación.

### 6.
La imagen de un proceso es el conjunto de las instrucciones y datos del programa.

### 7.
En ese caso el proceso pasa a un estado de bloqueado. En ese caso el planificador del sistema
operativo procede a bloquear el proceso y pasa a ejecutar otro hasta que puede satisfacer la llamada
del proceso original.

### 8.
Este proceso pasaría a estar preparado y el proceso bloqueado que esperaba a la interrupción pasará
a ejecutarse. Todo esto mediante el planificador del sistema operativo.

### 9.
Existe un proceso prioritario que se ejecuta con preferencia a todos los demás, cuando este proceso
solicita una operación de E/S, mientras se realiza el proceso pasa a bloquearse y cede el control a
un proceso en el background. Si este pide una operación de E/S se pasa el control a otro, etc. Todo
esto respetando una jerarquía de procesos.
