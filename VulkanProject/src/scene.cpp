#include "scene.h"
#include "render_structs.h"

Scene::Scene() {
    for (float x = -1.0f; x < 1.0f; x += 0.2f) {
        for (float y = -1.0f; y < 1.0f; y += 0.2f)
        {
            trianglePositions.push_back(glm::vec3(x, y, 0.0f));
        }
    }
}
void Scene::draw(vk::CommandBuffer cmd, vk::PipelineLayout layout) {

    vkUtil::ObjectData constants;
    static float time = 0.0f;
    time += 0.001f;

    for (const auto& pos : trianglePositions) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::rotate(model, time + pos.x, glm::vec3(0, 0, 1));
        float wave = sin(time * 3.0f + pos.x * 4.0f + pos.y * 4.0f);
		float currentScale = 1.0f + wave * 0.5f;

		model = glm::scale(model, glm::vec3(currentScale));
        constants.model = model;

        cmd.pushConstants(layout, vk::ShaderStageFlagBits::eVertex, 0, sizeof(vkUtil::ObjectData), &constants);
        cmd.draw(4, 1, 0, 0);
    }
};