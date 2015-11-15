#pragma once

class Ball {
	public:
		Ball();
		Ball(const float positionX, const float positionY, const float sizeW, const float sizeH);
		~Ball();

		void setSizeW(float size);
		void setSizeH(float size);
		void setPositionX(float position);
		void setPositionY(float position);

		float getSizeW();
		float getSizeH();
		float getPositionX();
		float getPositionY();

	private:
		float sizeW;
		float sizeH;

		float positionX;
		float positionY;
};