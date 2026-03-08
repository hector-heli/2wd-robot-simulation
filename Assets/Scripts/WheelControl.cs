using System.Linq;
using UnityEngine;

public class WheelControl : MonoBehaviour
{
    public Transform wheelModel;

//    [HideInInspector] public WheelCollider WheelCollider;
    public WheelCollider WheelCollider;

    // Create properties for the CarControl script
    // (You should enable/disable these via the 
    // Editor Inspector window)
    public bool steerable;
    public bool motorized;
    public enum WheelSide {
        Left,
        Right
    }

    public WheelSide wheelSide;

    int wheelIndex; // -1 for right, 1 for left
    Vector3 position;
    Quaternion rotation;

    // Start is called before the first frame update
    private void Start()
    {
        if (WheelCollider == null)
            WheelCollider = GetComponent<WheelCollider>();

        if (wheelModel != null)
            _wheelModelTransform = wheelModel.transform;
    }

    // Use LateUpdate so visual wheels update after physics
    void LateUpdate()
    {
        if (WheelCollider != null)
        {
            WheelCollider.GetWorldPose(out position, out rotation);
            if (wheelModel != null)
            {
                wheelIndex = wheelSide == WheelSide.Right ? 1 : -1;
                rotation *= Quaternion.Euler(0f, 90f*wheelIndex, 0f);
                wheelModel.rotation = rotation;
            }
        }
    }

    // Cached transform for performance
    private Transform _wheelModelTransform;
}