#include "GameController.h"

namespace Controller {

	GameController::GameController() {}
	GameController::~GameController() {}

	void GameController::gameLoop() {
		wParams.mFullscreen = false;
		wParams.mHeight = screenHeight;
		wParams.mWidth = screenWidth;
		wParams.mTitle = "Laboration 2";
		wParams.mPosX = 0;
		wParams.mPosY = 0;

		if (common.init(wParams)) {

			//Load all textures
			common.registerTextureResource("smoke", "image/particlesmoke.tga");
			common.registerTextureResource("spark", "image/spark.png");
			common.registerTextureResource("explosion", "image/explosion.png");
			common.registerTextureResource("ball", "image/ball.png"); 

			EventManager em;
			common.setEventProcessor(&em);

			Graphics *g = common.getGraphics();

			g->setViewport(0, 0, screenWidth, screenHeight);

			Renderer2D *renderer = g->createRenderer2D();

			float rot = 0.0f;

			HiResTimer timer;
			timer.restart();

			//Init and set program scale.
			View::SplitterSystem splitterSystem(common, Vec2(1.f, 1.f), Vec2(screenWidth, screenHeight));
			View::SmokeSystem smokeSystem(common, Vec2(1.f, 1.f), Vec2(screenWidth, screenHeight));
			View::AnimationSystem animationSystem(common, Vec2(1.f, 1.f), Vec2(screenWidth, screenHeight));
			View::Shockwave shockwave(common, Vec2(1.f, 1.f), Vec2(screenHeight, screenWidth));
			Model::BallSimulation ballSimulation(common, Vec2(1.f, 1.f), Vec2(screenHeight, screenWidth));
			View::BallView ballView(ballSimulation.getEmitter(), ballSimulation.getParams());

			const float TIME_STEP = 1.0 / 50.0f; //0.02
			float accumulator = 0.0f;

			while (gRunning) {

				common.getInputState(&inputState);
				if (inputState.isDown(Button::BUTTON_ESCAPE)) {
					gRunning = 0;
				}

				common.frame();
				timer.tick();

				g->clear(Color::White, true);

				accumulator += timer.getDeltaSeconds();

				while (accumulator >= TIME_STEP) {
					accumulator -= TIME_STEP;
					smokeSystem.UpdateEmitter(TIME_STEP);
					splitterSystem.UpdateEmitter(TIME_STEP);
					animationSystem.UpdateEmitter(TIME_STEP);
					shockwave.UpdateEmitter(TIME_STEP);
					ballView.UpdateEmitter(TIME_STEP);
				}

				renderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);

				splitterSystem.RenderEmitter(renderer);
				smokeSystem.RenderEmitter(renderer);
				animationSystem.RenderEmitter(renderer);
				shockwave.RenderEmitter(renderer);
				ballView.RenderEmitter(renderer);

				rot += timer.getDeltaSeconds() * 0.1f;

				renderer->end();

				g->present();
			}

		}
	}
}