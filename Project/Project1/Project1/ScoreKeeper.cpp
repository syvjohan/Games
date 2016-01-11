#include "ScoreKeeper.h"
#include "ManagerModel.h"

namespace Model {
	ScoreKeeper::ScoreKeeper() {}

	ScoreKeeper::~ScoreKeeper() {}

	void ScoreKeeper::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		sprintf(mText, "Score: %i%s", mScore, "/100");
		mPos = Vec2(60 , 20);
		mColor = Color::Yellow;
		mRotation = 0;
		mScale = Vec2(1, 1);

		mScore = 0;
	}

	void ScoreKeeper::OnUpdate() {
		if (mScore >= GetModel()->maxScore) { GetModel()->maxScore; }
		sprintf(mText, "Score: %i%s", mScore, "/100");

		GetModel()->OnScoreUpdated(this);
	}
}