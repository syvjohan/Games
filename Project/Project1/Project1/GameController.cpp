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
			common.registerTextureResource("background_menu", "image/space_background_menu.png");

			common.registerFontResource("sans16", 16, "fonts/ARIAL.ttf");
			common.registerFontResource("lobsterBold", 30, "fonts/LobsterTWo-Bold.otf");

			EventManager em;
			common.setEventProcessor(&em);

			Graphics *g = common.getGraphics();

			g->setViewport(0, 0, screenWidth, screenHeight);

			Renderer2D *renderer = g->createRenderer2D();

			HiResTimer timer;
			timer.restart();

			Model::MenuModel menuModel;
			View::MenuView menuView(&common, &menuModel);
			menuModel.AddView(&menuView);

			int height, width;
			common.getGraphics()->getContextSize(&width, &height);
			menuModel.Init(Vec2(width, height));

			Model::ManagerModel *managerModel = DBG_NEW Model::ManagerModel;
			View::ManagerView *managerView = DBG_NEW View::ManagerView(&common, managerModel);
			managerModel->AddView(managerView);

			common.getGraphics()->getContextSize(&width, &height);
			managerModel->Init(Vec2(width, height));

			currentState = GAMESTATE_INMENU;

			while (gRunning) {

				timer.tick();

				// Process OS events.
				common.frame();

				if (timerEsc <= 0) {
					timerEsc = 0;
				} else {
					timerEsc -= timer.getDeltaSeconds();
				}

				InputState input;
				common.getInputState(&input);
				if (input.isDown(Button::BUTTON_ESCAPE)) {
					if (timerEsc <= 0) {
						if (currentState == GAMESTATE_INGAME) {
							currentState = GAMESTATE_INMENU;
						} else {
							currentState = GAMESTATE_INGAME;
						}
						timerEsc = coolDownEsc;
					}
				}


				if (currentState == GAMESTATE_INMENU) {
					ShowCursor(TRUE);

					menuView.OnUpdate(timer.getDeltaSeconds());
					menuModel.OnUpdate(timer.getDeltaSeconds(), isGameStarted);
					if (menuModel.IsPaused() && isGameStarted) {
						currentState = GAMESTATE_INGAME;
					} else if (menuModel.IsNewGame()) {
						delete managerModel;
						delete managerView;

						managerModel = NULL;
						managerView = NULL;

						managerModel = DBG_NEW Model::ManagerModel;
						managerView = DBG_NEW View::ManagerView(&common, managerModel);
						managerModel->AddView(managerView);

						common.getGraphics()->getContextSize(&width, &height);
						managerModel->Init(Vec2(width, height));

						currentState = GAMESTATE_INGAME;
					}

					g->clear(Color::Black, true);

					menuView.OnRender();

					g->present();

				} else if (currentState == GAMESTATE_INGAME) {
					isGameStarted = true;
					ShowCursor(FALSE);

					managerView->OnUpdate(timer.getDeltaSeconds());
					managerModel->OnUpdate(timer.getDeltaSeconds());

					g->clear(Color::Black, true);

					managerView->OnRender();

					g->present();
				}
			}
		}
	}
}