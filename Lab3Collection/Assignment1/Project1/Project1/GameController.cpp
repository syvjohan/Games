#include "GameController.h"

namespace Controller {

	GameController::GameController() {}
	GameController::~GameController() {}

	void GameController::gameLoop() {
		//set program scale.
		View::Camera camera;
		camera.scale = Vec2(.5f, .5f);

		screenHeight *= camera.scale.y;
		screenWidth *= camera.scale.x;

		Vec2 boarder = Vec2((screenWidth / 2) - (boarderMargin * camera.scale.x), (screenHeight / 2) - (boarderMargin * camera.scale.y));
		Vec2 origin = Vec2(screenWidth / 2, screenHeight / 2);

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

			//Init
			View::SplitterSystem splitterSystem(common, camera.scale, Vec2(screenWidth, screenHeight));
			View::SmokeSystem smokeSystem(common, camera.scale, Vec2(screenWidth, screenHeight));
			View::AnimationSystem animationSystem(common, camera.scale, Vec2(screenWidth, screenHeight));
			View::Shockwave shockwave(common, camera.scale, Vec2(screenHeight, screenWidth));
			Model::BallSimulation ballSimulation(common, camera.scale, Vec2(screenWidth, screenHeight), boarderMargin);
			View::BallView ballView(ballSimulation.getEmitter(), ballSimulation.getParams());

			const float TIME_STEP = 1.0 / 60.0f; //0.02
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
					ballView.UpdateEmitter(TIME_STEP, boarderMargin);
				}

				renderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);

				splitterSystem.RenderEmitter(renderer);
				smokeSystem.RenderEmitter(renderer);
				animationSystem.RenderEmitter(renderer);
				shockwave.RenderEmitter(renderer);
				ballView.RenderEmitter(renderer);

				renderer->debugRect(origin, boarder, Color::Black);

				rot += timer.getDeltaSeconds() * 0.1f;

				renderer->end();

				g->present();
			}

		}
	}
}