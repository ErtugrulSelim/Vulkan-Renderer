#pragma once
#include "config.h"
#include "render_structs.h"

class Scene { 
	public:
		Scene();
		
		std::vector < glm::vec3> trianglePositions;

		void draw(vk::CommandBuffer cmd, vk::PipelineLayout layout);
};