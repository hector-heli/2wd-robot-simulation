"""
Módulo de Control de Robot 2WD
Envía comandos de velocidad frontal y angular a la simulación en Unity
"""

import socket
import json
import time
from typing import Optional


class RobotController:
    """Controla el robot 2WD mediante conexión TCP a Unity"""
    
    def __init__(self, host: str = "localhost", port: int = 8080, timeout: float = 2.0):
        """
        Inicializa la conexión con el servidor Unity
        
        Args:
            host: Dirección IP del servidor (localhost = 127.0.0.1)
            port: Puerto del servidor (por defecto 8080)
            timeout: Timeout de conexión en segundos
        """
        self.host = host
        self.port = port
        self.timeout = timeout
        self.connected = False
        
    def send_command(self, linear_velocity: float, angular_velocity: float) -> bool:
        """
        Envía un comando de movimiento al robot
        
        Args:
            linear_velocity: Velocidad frontal (-1.0 a 1.0)
                            Negativo = atrás, Positivo = adelante
            angular_velocity: Velocidad angular (-1.0 a 1.0)
                             Negativo = girar izquierda, Positivo = girar derecha
        
        Returns:
            True si el comando se envió exitosamente, False en caso contrario
        """
        try:
            # Limitar valores a rango [-1, 1]
            linear_velocity = max(-1.0, min(1.0, linear_velocity))
            angular_velocity = max(-1.0, min(1.0, angular_velocity))
            
            # Crear comando en formato JSON
            command = {
                "linear": linear_velocity,
                "angular": angular_velocity
            }
            
            # Conectar y enviar
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                sock.settimeout(self.timeout)
                sock.connect((self.host, self.port))
                message = json.dumps(command).encode('utf-8')
                sock.sendall(message)
                self.connected = True
                return True
                
        except (socket.timeout, ConnectionRefusedError, OSError) as e:
            print(f"Error de conexión: {e}")
            self.connected = False
            return False
    
    def move_forward(self, speed: float = 0.8) -> bool:
        """Mueve el robot hacia adelante"""
        return self.send_command(speed, 0.0)
    
    def move_backward(self, speed: float = 0.8) -> bool:
        """Mueve el robot hacia atrás"""
        return self.send_command(-speed, 0.0)
    
    def turn_left(self, speed: float = 0.8) -> bool:
        """Gira el robot hacia la izquierda"""
        return self.send_command(0.0, -speed)
    
    def turn_right(self, speed: float = 0.8) -> bool:
        """Gira el robot hacia la derecha"""
        return self.send_command(0.0, speed)
    
    def move_forward_and_turn(self, linear: float = 0.8, angular: float = 0.5) -> bool:
        """
        Mueve el robot adelante y gira simultáneamente
        
        Args:
            linear: Velocidad frontal (0.0 a 1.0)
            angular: Velocidad de giro (-1.0 a 1.0)
        """
        return self.send_command(linear, angular)
    
    def stop(self) -> bool:
        """Detiene el robot"""
        return self.send_command(0.0, 0.0)


# Ejemplo de uso
if __name__ == "__main__":
    # Crear instancia del controlador
    robot = RobotController(host="localhost", port=8080)
    
    print("Iniciando control del robot...")
    print("Asegúrate de que Unity está ejecutando y el ControlMode está en 'Python'\n")
    
    try:
        # Ejemplo 1: Mover adelante
        print("1. Moviendo adelante...")
        robot.move_forward(0.8)
        time.sleep(2)
        
        # Ejemplo 2: Girar a la derecha
        print("2. Girando a la derecha...")
        robot.turn_right(0.6)
        time.sleep(2)
        
        # Ejemplo 3: Movimiento combinado
        print("3. Movimiento adelante y giro...")
        robot.move_forward_and_turn(0.7, 0.3)
        time.sleep(2)
        
        # Ejemplo 3a: Movimiento combinado con giro a la izquierda
        print("3a. Movimiento adelante y giro a la izquierda...")   
        robot.move_forward_and_turn(0.7, -0.3)
        time.sleep(2)
        
        # Ejemplo 4: Detener
        print("4. Deteniendo...")
        robot.stop()
        time.sleep(1)
        
        # Ejemplo 5: Mover atrás
        print("5. Moviendo atrás...")
        robot.move_backward(0.6)
        time.sleep(2)
        
        # Detener al final
        robot.stop()
        print("\n¡Robot detenido!")
        
    except KeyboardInterrupt:
        print("\nInterrupción del usuario")
        robot.stop()
