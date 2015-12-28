#include "GameController.h"

namespace Controller {

	GameController::GameController() {}
	GameController::~GameController() {}

	void GameController::gameLoop() {
		//set program scale.
		View::Camera camera;
		camera.scale = Vec2(1.f, 1.f);

		screenHeight *= camera.scale.y;
		screenWidth *= camera.scale.x;

		Vec2 boarder = Vec2((screenWidth / 2) - (boarderMargin * camera.scale.x), (screenHeight / 2) - (boarderMargin * camera.scale.y));
		Vec2 origin = Vec2(screenWidth / 2, screenHeight / 2);

		wParams.mFullscreen = false;
		wParams.mHeight = screenHeight;
		wParams.mWidth = screenWidth;
		wParams.mTitle = "Project";
		wParams.mPosX = 0;
		wParams.mPosY = 0;

		if (common.init(wParams)) {

			//Load all textures	
			common.registerTextureResource("plane", "image/plane.png");
			common.registerTextureResource("shoot", "image/spark.png");
			common.registerTextureResource("asteroid1", "image/asteroid1.png");
			common.registerTextureResource("asteroid3", "image/asteroid3.png");

			EventManager em;
			common.setEventProcessor(&em);

			Graphics *g = common.getGraphics();

			g->setViewport(0, 0, screenWidth, screenHeight);

			Renderer2D *renderer = g->createRenderer2D();

			float rot = 0.0f;

			HiResTimer timer;
			timer.restart();

			View::PlaneSystem planeSystem(common, camera.scale, Vec2(screenWidth, screenHeight), boarderMargin);
			View::ShootSystem shootSystem(common, camera.scale, Vec2(screenWidth - boarderMargin, screenHeight - boarderMargin));
			View::AsteroidSystem asteroidSystem(common, camera.scale, Vec2(screenWidth - boarderMargin, screenHeight - boarderMargin));

			const float TIME_STEP = 1.0 / 60.0f;
			float accumulator = 0.0f;

			float accumulatorKeyPress = 0.0f;
			float oldAccumulatorKeyPress = 0.0f;

			float frames = 0, oldFrames = 0;
			float frameTimer = 0.0f;

			ShowCursor(FALSE);

			while (gRunning) {
				common.frame();
				timer.tick();

				g->clear(Color::White, true);

				accumulator += timer.getDeltaSeconds();

				common.getInputState(&inputState);
				if (inputState.isDown(Button::BUTTON_ESCAPE)) {
					gRunning = 0;
				}

				if (inputState.isDown(Button::BUTTON_A)) {
					planeSystem.Move(3);
				} 
				
				if (inputState.isDown(Button::BUTTON_W)) {
					planeSystem.Move(1);
				} 
				
				if (inputState.isDown(Button::BUTTON_D)) {
					planeSystem.Move(4);
				} 
				
				if (inputState.isDown(Button::BUTTON_S)) {
					planeSystem.Move(2);
				} 
				
				//setting timer for key pressing.
				accumulatorKeyPress += timer.getDeltaSeconds();

				if (accumulatorKeyPress - oldAccumulatorKeyPress > .5f) {
					if (inputState.isDown(Button::BUTTON_SPACE)) {
						oldAccumulatorKeyPress = accumulatorKeyPress;

						shootSystem.AddShoot(planeSystem.GetFirePosition());
					}
				}

				while (accumulator >= TIME_STEP) {
					accumulator -= TIME_STEP;

					planeSystem.UpdateEmitter(TIME_STEP, boarderMargin);
					shootSystem.UpdateEmitter(TIME_STEP);
					asteroidSystem.UpdateAnimation(TIME_STEP);
				}

				renderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);

				planeSystem.RenderEmitter(renderer);
				shootSystem.RenderEmitter(renderer);
				asteroidSystem.RenderAnimation(renderer);

				//boarder
				renderer->debugRect(origin, boarder, Color::Black);

				renderer->end();

				g->present();
			}
		}
	}
}