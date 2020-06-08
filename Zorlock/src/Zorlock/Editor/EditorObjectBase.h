#pragma once

namespace Zorlock {

	class EditorObjectBase
	{
	public:
		template <class T, class A>
		static void Draw(A* go) {
			if (std::is_convertible<T*, EditorObjectBase*>::value)
			{
				T editor;
				EditorObjectBase::InspectorDraw(editor, go);
			}
		}

		template <class T, class A>
		static void InspectorDraw(T& ed, A* go) 
		{
			ed.Inspector(go);
		}

		virtual void Inspector(void* go) = 0;
	};

}