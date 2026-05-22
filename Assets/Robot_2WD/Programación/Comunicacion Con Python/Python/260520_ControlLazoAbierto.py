from pyArduino import *
import numpy as np
import time
import matplotlib.pyplot as plt

ts = 0.1
tf = 10
t = np.arange(0, tf, ts)
N = len(t)

#COMUNICACION SERIAL
port = 'COM6'
baudRate = 115200
arduino = serialArduino(port, baudRate)
arduino.readSerialStart()

# SEÑALES DEL PROCESO
pv = np.zeros(N)
cv = np.zeros(N)

for k in range(N):
    start_time = time.time()
    # print(k * ts)

    # Escalón
    if k * ts >= 3:
        cv[k] = 40
    else:
        cv[k] = 0

    arduino.sendData([cv[k]])
    pv[k] = arduino.rawData[0]

    elapsed_time = time.time() - start_time
    if ts - elapsed_time > 0:
        time.sleep(ts - elapsed_time)

arduino.sendData([0])
arduino.close()

# Guardar datos en un archivo
with open('respuestaLazoAbierto.npy', 'wb') as f:
    np.save(f, cv)
    np.save(f, pv)
    np.save(f, t)
    np.save(f, ts)
    
# Graficar resultados
plt.figure
plt.plot(t, pv, label='Señal de Proceso')
plt.plot(t, cv, label='Señal de Control')
plt.xlabel('Tiempo')
plt.ylabel('Valor')
plt.title('Respuesta del Sistema en Lazo Abierto')
plt.legend()
plt.grid(True)
plt.show()  