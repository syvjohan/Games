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
		wParams.mTitle = "Laboration 3";
		wParams.mPosX = 0;
		wParams.mPosY = 0;

		if (common.init(wParams)) {

			//Load all textures
			common.registerTextureResource("smoke", "image/particlesmoke.tga");
			common.registerTextureResource("spark", "image/spark.png");
			common.registerTextureResource("explosion", "image/explosion.png");
			common.registerTextureResource("ball", "image/ball.png"); 		

			common.registerSoundResource("shoot", "sound/fire.wav");

			EventManager em;
			common.setEventProcessor(&em);

			Graphics *g = common.getGraphics();

			g->setViewport(0, 0, screenWidth, screenHeight);

			Renderer2D *renderer = g->createRenderer2D();

			float rot = 0.0f;

			HiResTimer timer;
			timer.restart();

			Model::BallSimulation ballSimulation(common, camera.scale, Vec2(screenWidth, screenHeight), boarderMargin);
			View::BallView ballView(ballSimulation.getEmitter(), ballSimulation.getParams());

			const float TIME_STEP = 1.0 / 60.0f;
			float accumulator = 0.0f;

			float accumulatorKeyPress = 0.0f;
			float oldAccumulatorKeyPress = 0.0f;

			while (gRunning) {

				common.getInputState(&inputState);
				if (inputState.isDown(Button::BUTTON_ESCAPE)) {
					gRunning = 0;
				}

				common.frame();
				timer.tick();

				g->clear(Color::White, true);

				accumulator += timer.getDeltaSeconds();

				//setting timer for key pressing.
				accumulatorKeyPress += timer.getDeltaSeconds();

				//Identify key press.
				if (accumulatorKeyPress - oldAccumulatorKeyPress > .5f) {
					if (inputState.isDown(Button::BUTTON_MOUSELEFT)) {
						oldAccumulatorKeyPress = accumulatorKeyPress;
						
						Vec4 hitArea = Vec4(inputState.mMouseX, inputState.mMouseY, 0, aimRadie);
						int ballIndex = ballView.Collision(hitArea);
						if (ballIndex != -1) {
							ballView.StopBall(ballIndex);

							//init effect.
							splitter.push_back(new View::SplitterSystem(common, camera.scale, Vec2(screenWidth, screenHeight), Vec2(inputState.mMouseX, inputState.mMouseY)));
							smoke.push_back(new View::SmokeSystem(common, camera.scale, Vec2(screenWidth, screenHeight), Vec2(inputState.mMouseX, inputState.mMouseY)));

							common.getAudio();
						}
					}
				}

				while (accumulator >= TIME_STEP) {
					accumulator -= TIME_STEP;
					ballView.UpdateEmitter(TIME_STEP, boarderMargin);

					for (int i = 0; i != splitter.size(); ++i) {
						splitter[i]->UpdateEmitter(TIME_STEP);
						smoke[i]->UpdateEmitter(TIME_STEP);
					}
				}

				renderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);

				ballView.RenderEmitter(renderer);

				for (int i = 0; i != splitter.size(); ++i) {
					splitter[i]->RenderEmitter(renderer);
					smoke[i]->RenderEmitter(renderer);
				}

				//boarder
				renderer->debugRect(origin, boarder, Color::Black);

				//Aim
				renderer->debugCircle(inputState.mMouseX, inputState.mMouseY, aimRadie * camera.scale.x, Color::Black);

				rot += timer.getDeltaSeconds() * 0.1f;

				renderer->end();

				g->present();
			}

		}
	}


}