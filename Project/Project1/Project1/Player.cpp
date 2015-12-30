#include "Player.h"

namespace View {
	Player::Player() {}

	Player::Player(Common &common, Vec2 scale, Vec2 playerArea) {
		Init(common, scale, playerArea);
	}

	Player::~Player() {}

	void Player::Init(Common &common, Vec2 scale, Vec2 playArea) {
		player.mTexture = common.getTextureResource("plane");
		player.mPos.x = playArea.x / 12;
		player.mPos.y = playArea.y / 2;
		player.mPlayArea = playArea;
		player.mVel = Vec2(1, 1);
		player.mAcc = Vec2(1, 1);
		player.mDir = Vec2(0, 0);
		player.mScale = scale;
		player.mOrientation = 1.58f;
		player.mSize = Vec2(116, 140);

		player.animation.mCurrentFrame = 0;
		player.animation.mFrameTime = 0.0f;
	}

	void Player::Update(const float dt, float boarderMargin) {
		Animation(dt);

		//Game physics
		player.mPos.x += player.mDir.x * player.mVel.x * dt;
		player.mPos.y += player.mDir.y * player.mVel.y * dt;

		if (player.mPos.x < boarderMargin) {
			player.mPos.x = boarderMargin;
		}

		if (player.mPos.x + player.mSize.x + (boarderMargin * 2) > player.mPlayArea.x) {
			player.mPos.x = player.mPlayArea.x  - player.mSize.x - (boarderMargin * 2);
		}

		if (player.mPos.y < boarderMargin + player.mSize.x) {
			player.mPos.y = boarderMargin + player.mSize.x; //Sprite is rotated.
		}

		if (player.mPos.y > player.mPlayArea.y) {
			player.mPos.y = player.mPlayArea.y;
		}
	}

	void Player::Render(Renderer2D *renderer) {
		int width = 116;
		int height = 140;
		RectangleF clip = { 0, 0, width, height };

		clip.x = (player.animation.mCurrentFrame % 4) * width;
		clip.y = (player.animation.mCurrentFrame / 4) * height;

		renderer->draw(player.mTexture,
					   (player.mPos),
						clip,
						Vec2(0,0),
						player.mOrientation,
						player.mScale,
						Color::White,
						0.0f
						);
	}

	void Player::Move(int dir) {
		switch (dir) {
			case 1:
				player.mDir.y -= 1; //Upp
				btnUp++;
				btnDown = 0;
				btnForward = 0;
				btnBack = 0;
				break;
			case 2:
				player.mDir.y += 1; //Down
				btnDown++;
				btnUp = 0;
				btnForward = 0;
				btnBack = 0;
				break;
			case 3:
				player.mDir.x -= 1; //Back
				btnBack++;
				btnForward = 0;
				btnUp = 0;
				btnDown = 0;
				break;
			case 4:
				player.mDir.x += 1; //Forward
				btnForward++;
				btnBack = 0;
				btnUp = 0;
				btnDown = 0;
				break;
			default:
				break;
		}
	}

	void Player::Animation(const float dt) {
		player.animation.mFrameTime += dt;
		if (player.animation.mFrameTime >= 0.021) {
			player.animation.mFrameTime = 0.0;

			if (btnBack > 0) {
				switch (btnBack) {
					case 1:
						player.animation.mCurrentFrame = 0;
						break;
					case 2:
						player.animation.mCurrentFrame = 1;
						break;
					case 3:
						player.animation.mCurrentFrame = 2;
						break;
					case 4:
						player.animation.mCurrentFrame = 3;
						break;
				}
			} else if (btnForward > 0) {
				switch (btnForward) {
					case 1:
						player.animation.mCurrentFrame = 0;
						break;
					case 2:
						player.animation.mCurrentFrame = 1;
						break;
					case 3:
						player.animation.mCurrentFrame = 2;
						break;
					case 4:
						player.animation.mCurrentFrame = 3;
						break;
				}
			} else if (btnDown > 0) {
				switch (btnDown) {
					case 1:
						player.animation.mCurrentFrame = 0;
						break;
					case 2:
						player.animation.mCurrentFrame = 1;
						break;
					case 3:
						player.animation.mCurrentFrame = 2;
						break;
					case 4:
						player.animation.mCurrentFrame = 3;
						break;
				}
			} else if (btnUp > 0) {
				switch (btnUp) {
					case 1:
						player.animation.mCurrentFrame = 0;
						break;
					case 2:
						player.animation.mCurrentFrame = 1;
						break;
					case 3:
						player.animation.mCurrentFrame = 2;
						break;
					case 4:
						player.animation.mCurrentFrame = 3;
						break;
				}
			}
		}
	}

	Vec2 Player::GetFirePosition() {
		return Vec2(player.mPos.x + player.mSize.x + 120, player.mPos.y - 2);
	}
}