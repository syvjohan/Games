#include "GameController.h"

namespace Controller {

	GameController::GameController() {}
	GameController::~GameController() {}

	void GameController::gameLoop() {
		////set program scale.
		//View::Camera camera;
		//camera.scale = Vec2(1.f, 1.f);

		//screenHeight *= camera.scale.y;
		//screenWidth *= camera.scale.x;

		//Vec2 boarder = Vec2((screenWidth / 2) - (boarderMargin * camera.scale.x), (screenHeight / 2) - (boarderMargin * camera.scale.y));
		//Vec2 origin = Vec2(screenWidth / 2, screenHeight / 2);

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

			common.registerTextureResource("plane", "image/plane.png");
			common.registerTextureResource("shoot", "image/spark.png");
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
			model.Init(Vec2(width, height), Vec2(borderW, borderH));

		/*	View::Player player(&common, camera.scale, Vec2(screenWidth - boarderMargin, screenHeight - boarderMargin));
			View::ShootSystem shootSystem(&common, Vec2(screenWidth - boarderMargin, screenHeight - boarderMargin));
			View::AsteroidSystem asteroidSystem(&common, camera.scale, Vec2(screenWidth - boarderMargin, screenHeight - boarderMargin));
			Model::CollisionDetection collisionDetection;
			View::Score score(common, g);
			View::PlayerHealth playerHealth(common, g);*/

			//const float TIME_STEP = 1.0 / 60.0f;
			//float accumulator = 0.0f;

			//float accumulatorKeyPress = 0.0f;
			//float oldAccumulatorKeyPress = 0.0f;

			//float frames = 0, oldFrames = 0;
			//float frameTimer = 0.0f;

			//ShowCursor(FALSE);

			while (gRunning) {

				timer.tick();

				// Process OS events.
				common.frame();

				view.OnUpdate(timer);
				model.OnUpdate(timer);

				g->clear(Color::Black, true);

				view.OnRender();

				g->present();

			//	common.frame();
			//	timer.tick();

			//	g->clear(Color::Black, true);

			//	accumulator += timer.getDeltaSeconds();
			//	accumulatorKeyPress += timer.getDeltaSeconds(); //setting timer for key pressing.

				/*common.getInputState(&inputState);

				if (inputState.isDown(Button::BUTTON_ESCAPE)) {
					gRunning = 0;
				}

				if (inputState.isDown(Button::BUTTON_A)) {
					player.Move(3);
				}

				if (inputState.isDown(Button::BUTTON_W)) {
					player.Move(1);
				}

				if (inputState.isDown(Button::BUTTON_D)) {
					player.Move(4);
				}

				if (inputState.isDown(Button::BUTTON_S)) {
					player.Move(2);
				}

				if (accumulatorKeyPress - oldAccumulatorKeyPress > .5f) {
					if (inputState.isDown(Button::BUTTON_SPACE)) {
						oldAccumulatorKeyPress = accumulatorKeyPress;

						shootSystem.AddBullet(camera.scale, player.GetFirePosition());
					}
				}*/

				//while (accumulator >= TIME_STEP) {
				//	accumulator -= TIME_STEP;

				//	player.Update(TIME_STEP, boarderMargin);
				//	shootSystem.Update(TIME_STEP);
				//	asteroidSystem.Update(TIME_STEP);
				//	score.Update();
				//	playerHealth.Update();

				//	asteroidSystem.ExtendAsteroidBelt(TIME_STEP);
				//}

				//renderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);

				//player.Render(renderer);
				//shootSystem.Render(renderer);
				//asteroidSystem.Render(renderer);
				//score.Render(renderer);
				//playerHealth.Render(renderer);

				////Collision
				//PairCollision pairCollision1;
				//pairCollision1 = collisionDetection.AsteroidAndBullet(shootSystem.GetBulletsPositions(), asteroidSystem.GetAsteroidPositions());		
				//asteroidSystem.AsteroidIsHit(pairCollision1.first);
				//shootSystem.RemoveBullet(pairCollision1.second);

				//score.UpdateScore(asteroidSystem.GetHitScore());
				//asteroidSystem.ResetHitScore();

				////Collision
				//PairCollision pairCollision2;
				//pairCollision2 = collisionDetection.AsteroidAndPlayer(player.GetPosition(), asteroidSystem.GetAsteroidPositions());
				//
				//player.IsHit(pairCollision2.second);
				//
				//asteroidSystem.AsteroidIsHit(pairCollision2.first);

				//playerHealth.UpdateHealth(player.GetHealth());


				////boarder
				//renderer->debugRect(origin, boarder, Color::Green);

				//renderer->end();

				//g->present();

				
			}


		}
	}
}