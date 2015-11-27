#pragma once

class Scale {
	public:
		Scale();
		~Scale();

		void set(float sizeW, float sizeH);
		float getW();
		float getH();

	private:
		float w;
		float h;
};