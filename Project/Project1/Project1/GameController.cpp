#include "GameController.h"
#include "GameState.h"

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
			common.registerTextureResource("background_after_game", "image/space_background_after_game.png");

			common.registerFontResource("sans16", 16, "fonts/ARIAL.ttf");
			common.registerFontResource("sans20", 20, "fonts/OpenSans-Regular.ttf");
			common.registerFontResource("lobsterBold", 30, "fonts/LobsterTWo-Bold.otf");

			EventManager em;
			common.setEventProcessor(&em);

			Graphics *g = common.getGraphics();

			g->setViewport(0, 0, screenWidth, screenHeight);

			HiResTimer timer;
			timer.restart();

			SetAsteroidType(currentLvl);

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
			managerModel->Init(Vec2(width, height), GetAsteroidType().typ1, GetAsteroidType().type2);

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

				if (managerModel->WonRound() || managerModel->LostRound()) {
					if (timerResultScreen <= 0) {
						timerResultScreen = 0;
					} else {
						timerResultScreen -= timer.getDeltaSeconds();
					}

					if (managerModel->LostRound()) {
						menuModel.ShowLostRound();
						currentState = GAMESTATE_AFTER_GAME;
					} else {
						if (currentLvl >= 2) {
							menuModel.ShowWonGame();
							currentState = GAMESTATE_AFTER_GAME;
						} else {
							menuModel.ShowWonRound();
							currentState = GAMESTATE_AFTER_GAME;
						}
					}

					if (timerResultScreen == 0) {
						timerResultScreen = timeElapseResultScreen;

						if (currentLvl >= 2) {
							currentState = GAMESTATE_INMENU;
						} else {
							currentState = GAMESTATE_INGAME; //Start new game.
						}

						++currentLvl;
						SetAsteroidType(currentLvl);

						delete managerModel;
						delete managerView;

						managerModel = NULL;
						managerView = NULL;

						managerModel = DBG_NEW Model::ManagerModel;
						managerView = DBG_NEW View::ManagerView(&common, managerModel);
						managerModel->AddView(managerView);

						common.getGraphics()->getContextSize(&width, &height);
						managerModel->Init(Vec2(width, height), GetAsteroidType().typ1, GetAsteroidType().type2);
					}
				}

				if (currentState == GAMESTATE_INMENU) {
					//ShowCursor(TRUE);

					menuModel.OnUpdate(timer.getDeltaSeconds(), isGameStarted);
					menuView.OnUpdate(timer.getDeltaSeconds());
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
						managerModel->Init(Vec2(width, height), GetAsteroidType().typ1, GetAsteroidType().type2);

						currentState = GAMESTATE_INGAME;
						currentLvl = 0;
					}

					g->clear(Color::Black, true);

					menuView.OnRenderMenu();

				} else if (currentState == GAMESTATE_INGAME) {
					isGameStarted = true;

					//ShowCursor(FALSE);

					managerModel->OnUpdate(timer.getDeltaSeconds());
					managerView->OnUpdate(timer.getDeltaSeconds());

					g->clear(Color::Black, true);

					managerView->OnRender();

				} else if (currentState == GAMESTATE_AFTER_GAME) {
					menuModel.OnUpdate(timer.getDeltaSeconds(), isGameStarted);
					menuView.OnUpdate(timer.getDeltaSeconds());

					g->clear(Color::Black, true);

					menuView.OnRenderAfterGame();
				}

				g->present();
			}
		}
	}

	AsteroidType GameController::GetAsteroidType() {
		return asteroidType;
	}

	void GameController::SetAsteroidType(int lvl) {
		switch (lvl) {
			case 0:
				asteroidType.typ1 = 1;
				asteroidType.type2 = 2;
				break;
			case 1:
				asteroidType.typ1 = 3;
				asteroidType.type2 = 5;
				break;
			case 2:
				asteroidType.typ1 = 4;
				asteroidType.type2 = 6;
				break;
			default:
				asteroidType.typ1 = 1;
				asteroidType.type2 = 2;
				break;
		}
	}
}