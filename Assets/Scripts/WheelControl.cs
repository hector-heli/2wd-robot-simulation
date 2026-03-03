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
        
    }

    // Cached transform for performance
    private Transform _wheelModelTransform;
}