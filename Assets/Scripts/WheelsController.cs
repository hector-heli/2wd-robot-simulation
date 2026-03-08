using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class WheelsController : MonoBehaviour
{
    public WheelCollider leftWheel;
    public WheelCollider rightWheel;
    public float maxMotorTorque = 150f;   // fuerza aplicada cuando se acelera
    public float maxBrakeTorque = 300f;   // fuerza de frenado

    public enum ControlMode
    {
        Keyboard,
        Python
    }

    public ControlMode controlMode = ControlMode.Keyboard;

    // Variables para comandos desde Python
    private float pythonLinearVelocity = 0f;  // Velocidad frontal (-1 a 1)
    private float pythonAngularVelocity = 0f; // Velocidad de rotación (-1 a 1)

    private TcpListener server;
    private Thread serverThread;
    private bool isRunning = true;

    void Start()
    {
        if (controlMode == ControlMode.Python)
        {
            StartServer();
        }
    }

    void OnDestroy()
    {
        isRunning = false;
        if (serverThread != null)
        {
            serverThread.Abort();
        }
    }

    private void StartServer()
    {
        server = new TcpListener(IPAddress.Any, 8080);
        server.Start();
        serverThread = new Thread(new ThreadStart(ListenForCommands));
        serverThread.Start();
    }

    private void ListenForCommands()
    {
        while (isRunning)
        {
            try
            {
                TcpClient client = server.AcceptTcpClient();
                NetworkStream stream = client.GetStream();
                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                // Parse JSON command: {"linear": 0.5, "angular": 0.2}
                try
                {
                    var command = JsonUtility.FromJson<CommandData>(message);
                    pythonLinearVelocity = Mathf.Clamp(command.linear, -1f, 1f);
                    pythonAngularVelocity = Mathf.Clamp(command.angular, -1f, 1f);
                }
                catch
                {
                    Debug.LogWarning("Invalid command format");
                }

                client.Close();
            }
            catch (Exception e)
            {
                Debug.LogError("Server error: " + e.Message);
            }
        }
    }

    [Serializable]
    private class CommandData
    {
        public float linear;
        public float angular;
    }

    // Update is called once per frame
    void Update()
    {
        (float v, float h) = GetInput();
        ApplyMovement(v, h);
        // Debug.Log($"Mode={controlMode}, V={v:F2}, H={h:F2} | Lspeed={leftWheel.rpm:F1}, Rspeed={rightWheel.rpm:F1}");
    }

    private (float, float) GetInput()
    {
        if (controlMode == ControlMode.Keyboard)
        {
            float v = Input.GetAxis("Vertical");   // W/S o flechas arriba/abajo
            float h = Input.GetAxis("Horizontal"); // A/D o flechas izquierda/derecha
            return (v, h);
        }
        else // Python
        {
            return (pythonLinearVelocity, pythonAngularVelocity);
        }
    }

    private void ApplyMovement(float v, float h)
    {
        // Aplicar torque a las ruedas para mover el vehículo
        float leftTorque  = (v + h) * maxMotorTorque;
        float rightTorque = (v - h) * maxMotorTorque;

        if(Mathf.Approximately(v, 0f) && Mathf.Approximately(h, 0f)){
            // Si no hay input, aplicar freno
            leftWheel.brakeTorque = maxBrakeTorque;
            rightWheel.brakeTorque = maxBrakeTorque;
            leftWheel.motorTorque = 0f;
            rightWheel.motorTorque = 0f;
        } else {
            // Si hay input, aplicar torque y quitar freno
            leftWheel.brakeTorque = 0f;
            rightWheel.brakeTorque = 0f;
            leftWheel.motorTorque = leftTorque;
            rightWheel.motorTorque = rightTorque;
        }
    }
}
