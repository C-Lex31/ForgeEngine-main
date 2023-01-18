#pragma once

#include "scene_2d.h"

namespace Forge {

	class SceneSerializer {
	public:

		SceneSerializer(const FRef<Scene2d>& scene);

		void Serialize(const FString& Filepath);

		void SerializeRuntime(const FString& Filepath);

		bool Deserialize(const FString& Filepath);

		void DeserializeRuntime(const FString& Filepath);

	private:
		FRef<Scene2d> m_Scene;

	};
}