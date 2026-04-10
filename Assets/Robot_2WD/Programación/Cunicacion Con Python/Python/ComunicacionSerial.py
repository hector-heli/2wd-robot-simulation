import serial
import time
import threading

arduino = serial.Serial('COM8', 115200, timeout=0.1)
time.sleep(2)
arduino.reset_input_buffer()

bandera = threading.Event() 
bandera.set() 

def move_motors():
    while True:
        bandera.wait()
        velocidades = input("")
        arduino.write((velocidades + '\n').encode()) 
        bandera.clear()


comunicacion = threading.Thread(target=move_motors, daemon=True)
comunicacion.start()
print("\n")
while True: 
    if arduino.in_waiting > 0:
        try:
            linea = arduino.readline().decode('utf-8', errors='ignore').rstrip()
            if linea:
                rpm_R,rpm_L,IR_R,IR_L,sonar, ts = linea.split(',')
                
                
                print(f"RPM recibidas: {rpm_L}, {rpm_R} Sensor de piso: {IR_L}, {IR_R} Sonar: {sonar}  ts: {ts}    ", end='\r')
                bandera.set()
        except:
            pass