using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WheelsController : MonoBehaviour
{
    public WheelCollider leftWheel;
    public WheelCollider rightWheel;
    public float maxMotorTorque = 150f;   // fuerza aplicada cuando se acelera
    public float maxBrakeTorque = 300f;   // fuerza de frenado
    // Update is called once per frame
    void Update(){
        float v = Input.GetAxis("Vertical");   // W/S o flechas arriba/abajo
        float h = Input.GetAxis("Horizontal"); // A/D o flechas izquierda/derecha

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
        Debug.Log($"V={v:F2}, H={h:F2} | Lspeed={leftWheel.rpm:F1}, Rspeed={rightWheel.rpm:F1}");
        
    }
}
