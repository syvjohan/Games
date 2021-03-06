#include <framework.h>
#include "Defs.h"
#include "SplitterSystem.h"
#include <cstdlib>
#include <ctime>
//1
float programScaleIndex = .4f;
int screenWidth = 1280;
int screenHeight = 720;

HiResTimer video;
bool gRunning = true;

class EventManager : public IEventProcessor {
	public:
	void onWindowClose() { gRunning = false; }
};

InputState inputState;
WindowParams wParams;
Common common;

void gameLoop() {
	wParams.mFullscreen = false;
	wParams.mHeight = screenHeight * programScaleIndex;
	wParams.mWidth = screenWidth * programScaleIndex;
	wParams.mTitle = "Laboration 2";
	wParams.mPosX = 0;
	wParams.mPosY = 0;

	if (common.init(wParams)) {

		common.registerTextureResource("spark", "image/spark.png");
		
		EventManager em;
		common.setEventProcessor(&em);

		Graphics *g = common.getGraphics();
		g->setViewport(0, 0, screenWidth, screenHeight);

		Renderer2D *renderer = g->createRenderer2D();

		float rot = 0.0f;

		HiResTimer timer;
		timer.restart();
		video.restart();

		//Set program scale.
		SplitterSystem splitterSystem(common, programScaleIndex, screenWidth, screenHeight);
		
		const float TIME_STEP = 1.0 / 50.0f; //0.02
		float accumulator = 0.0f;

		while (gRunning) {

			if (inputState.isDown(Button::BUTTON_ESCAPE)) {
				gRunning = 0;
			}
			
			common.frame();
			timer.tick();
			video.tick();
			g->clear(Color::Black, true);

			accumulator += timer.getDeltaSeconds();

			while (accumulator >= TIME_STEP) {
				accumulator -= TIME_STEP;
				splitterSystem.UpdateEmitter(TIME_STEP);
			}

			renderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);

			splitterSystem.RenderEmitter(renderer);

			rot += timer.getDeltaSeconds() * 0.1f;

			renderer->end();

			g->present();

			if (video.getTotalSeconds() > 2) {
				gameLoop();
			}
		}

		splitterSystem.FreeMem();
	}
}

#undef main
int main(int, char**) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	srand(time(NULL));
	
	gameLoop();
	return 0;
}

