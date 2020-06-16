#include "ZLpch.h"
#include "EditorCameraControl.h"

namespace Zorlock
{
	static float m_ecam_lookspeedH = 2.0f;
	static float m_ecam_lookspeedV = 2.0f;
	static float m_ecam_zoomspeed = 2.0f;
	static float m_ecam_dragspeed = 2.0f;


	void EditorCameraControl::OnUpdate(Timestep ts)
	{
		/*
	             //Look around with Right Mouse
             if (Input.GetMouseButton(1))
             {
                 yaw += lookSpeedH * Input.GetAxis("Mouse X");
                 pitch -= lookSpeedV * Input.GetAxis("Mouse Y");
     
                 transform.eulerAngles = new Vector3(pitch, yaw, 0f);
             }
     
             //drag camera around with Middle Mouse
             if (Input.GetMouseButton(2))
             {
                 transform.Translate(-Input.GetAxisRaw("Mouse X") * Time.deltaTime * dragSpeed,   -Input.GetAxisRaw("Mouse Y") * Time.deltaTime * dragSpeed, 0);
             }
     
             //Zoom in and out with Mouse Wheel
             transform.Translate(0, 0, Input.GetAxis("Mouse ScrollWheel") * zoomSpeed, Space.Self);	
		
		
		*/


	}


}