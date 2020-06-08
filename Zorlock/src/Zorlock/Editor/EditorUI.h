#pragma once

namespace Zorlock {

	

	class EditorUI
	{
	public:
		EditorUI();
		~EditorUI();
		void EditorUIDraw();
		void ProjectSelection();
		void ProjectsList();
		void MainEditor();
		void MainMenu();
		void AssetExplorer();
		void Inspector();
		void ToolBarTop();
		void ToolBarBottom();
		void GameObjectBlock();
		void TransformBlock();

		static EditorUI* Get();

		
	protected:
		
	};

	

}

#define ZLEDITORUI Zorlock::EditorUI