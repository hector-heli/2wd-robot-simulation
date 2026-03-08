using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MovementControl : MonoBehaviour
{
    public float speed = .1f;
    public Rigidbody rb;
    public Vector3 movementInput;

    Quaternion rotation;

    public Transform RightWheelModel;
    public Transform LeftWheelModel;

    public WheelCollider RightWheelCollider;
    public WheelCollider LeftWheelCollider;



    void Awake()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    private void Update()
    {   
        movementInput = Vector3.zero;
        
        float vInput = (int) Input.GetAxis("Vertical");
        float hInput = (int) Input.GetAxis("Horizontal"); 
        // Debug.Log(vInput);
        // Debug.Log(hInput);

        if (Input.GetAxis("Vertical") != 0){
            movementInput.z = vInput;
            // RightWheelCollider.motorTorque = speed * vInput ;
            // LeftWheelCollider.motorTorque = speed * vInput ;

            RightWheelModel.transform.Rotate (0, 0, (25 * Time.deltaTime*vInput) );
            LeftWheelModel.transform.Rotate (0, 0, (25 * Time.deltaTime*-vInput) );
        } 
            
        else if (Input.GetAxis("Horizontal") != 0) movementInput.x = hInput;
        
    }
    
    protected void FixedUpdate() {
        Move(movementInput);
    }
    void Move (Vector3 direction){
        // rb.AddForce (direction.normalized * speed, ForceMode.Acceleration);
        rb.MovePosition(rb.position + direction.normalized * speed * Time.fixedDeltaTime);
    }
}
