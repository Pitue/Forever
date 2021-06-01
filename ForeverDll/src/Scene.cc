#include "../include/Scene.h"
#include "../include/Export/Engine.h"

namespace fr {
	Scene::Scene(Engine* engine) 
		: engine_{ engine }, running_{ true }, background_(engine, engine->Window().renderer_),
		objects_{ new std::vector<Drawable*> }, cam_{ nullptr } {}
	Scene::~Scene() {
		delete objects_;
	}

	void Scene::Background(Texture bck) {
		background_.Texture(bck);
		background_.Size(engine_->Window().Size());
		background_.Bind(cam_);
	}
	void Scene::Draw() {
		background_.Draw();
		for (size_t i = 0; i < objects_->size(); i++) objects_->at(i)->Draw();
	}
}
