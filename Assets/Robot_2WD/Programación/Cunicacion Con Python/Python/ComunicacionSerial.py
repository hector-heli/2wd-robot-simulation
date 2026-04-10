import serial
import time
import threading
arduino = serial.Serial('COM8', 115200)
time.sleep(2)

bandera = threading.Event() 
bandera.set() 

def move_motors():
    while True:

            bandera.wait()
            velocidades = input("Ingrese las velocidades para los motores (separadas por una coma):")
            arduino.write(velocidades.encode('utf-8'))  # Enviar las velocidades al Arduino
            bandera.clear()
comunicacion = threading.Thread(target=move_motors)
comunicacion.start()

while True:
    
    
    
    if arduino.in_waiting > 0:
        texto_recibido = arduino.readline().decode('utf-8').rstrip()  
        print(f"Mensaje recibido del Arduino: {texto_recibido}\n") 
        bandera.set()

arduino.close() 