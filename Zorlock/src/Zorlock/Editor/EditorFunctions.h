#pragma once

namespace Zorlock {

	class GameObject;
	class Transform;
	class EditorFunctions
	{
	public:
		static void CreateCube(std::string name, Ref<Transform> parent = nullptr);
		static void CreateCone(std::string name, Ref<Transform> parent = nullptr);
		static void CreateSphere(std::string name, Ref<Transform> parent = nullptr);
		static void CreateCylinder(std::string name, Ref<Transform> parent = nullptr);
		static void CreateQuad(std::string name, Ref<Transform> parent = nullptr);
		static void CreateLight(std::string name, Ref<Transform> parent = nullptr);



	};


}