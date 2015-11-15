#pragma once

class Camera {
	public:
		Camera();
		~Camera();

		void setScale(float size);
		float getScale();

	private: 
		float scale = 1; //decide size of everything.
};