#include "GameController.h"

namespace Controller {

	GameController::GameController() {}
	GameController::~GameController() {}

	void GameController::gameLoop() {
		wParams.mFullscreen = false;
		wParams.mHeight = screenHeight;
		wParams.mWidth = screenWidth;
		wParams.mTitle = "Project";
		wParams.mPosX = 0;
		wParams.mPosY = 0;

		if (common.init(wParams)) {

			//Load all textures	
			common.registerSoundResource("soundExplosion", "sound/explosion.ogg");
			common.registerSoundResource("soundShoot", "sound/fire.ogg");

			common.registerTextureResource("shoot", "image/spark.png");
			common.registerTextureResource("plane", "image/plane.png");
			common.registerTextureResource("explosion", "image/explosion.png");

			common.registerTextureResource("asteroid1", "image/asteroid1.png");
			common.registerTextureResource("asteroid2", "image/asteroid2.png");
			common.registerTextureResource("asteroid3", "image/asteroid3.png");
			common.registerTextureResource("asteroid4", "image/asteroid4.png");
			common.registerTextureResource("asteroid5", "image/asteroid5.png");
			common.registerTextureResource("asteroid6", "image/asteroid6.png");

			common.registerFontResource("sans16", 16, "fonts/ARIAL.ttf");

			EventManager em;
			common.setEventProcessor(&em);

			Graphics *g = common.getGraphics();

			g->setViewport(0, 0, screenWidth, screenHeight);

			Renderer2D *renderer = g->createRenderer2D();

			HiResTimer timer;
			timer.restart();

			Model::ManagerModel model;
			View::ManagerView view(&common, &model);
			model.AddView(&view);
			int width, height;
			common.getGraphics()->getContextSize(&width, &height);
			model.Init(Vec2(width, height));

			ShowCursor(FALSE);

			while (gRunning) {

				timer.tick();

				// Process OS events.
				common.frame();

				InputState input;
				common.getInputState(&input);
				if (input.isDown(Button::BUTTON_ESCAPE)) {
					gRunning = 0;
				}

				view.OnUpdate(timer.getDeltaSeconds());
				model.OnUpdate(timer.getDeltaSeconds());

				g->clear(Color::Black, true);

				view.OnRender();

				g->present();			
			}
		}
	}
}