#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <algorithm>
#undef min
#undef max


class SpriteTransforms : public olc::PixelGameEngine
{
public:
	SpriteTransforms()
	{
		sAppName = "Sprite Transforms";
	}

private:
	olc::Sprite *sprCar;

	struct matrix3x3
	{
		float m[3][3];
	};

	void Identity(matrix3x3 &mat)
	{
		mat.m[0][0] = 1.0f; mat.m[1][0] = 0.0f; mat.m[2][0] = 0.0f;
		mat.m[0][1] = 0.0f; mat.m[1][1] = 1.0f; mat.m[2][1] = 0.0f;
		mat.m[0][2] = 0.0f; mat.m[1][2] = 0.0f; mat.m[2][2] = 1.0f;
	}

	void Translate(matrix3x3 &mat, float ox, float oy)
	{
		mat.m[0][0] = 1.0f; mat.m[1][0] = 0.0f; mat.m[2][0] = ox;
		mat.m[0][1] = 0.0f; mat.m[1][1] = 1.0f; mat.m[2][1] = oy;
		mat.m[0][2] = 0.0f;	mat.m[1][2] = 0.0f;	mat.m[2][2] = 1.0f;
	}

	void Rotate(matrix3x3 &mat, float fTheta)
	{
		mat.m[0][0] = cosf(fTheta);  mat.m[1][0] = sinf(fTheta); mat.m[2][0] = 0.0f;
		mat.m[0][1] = -sinf(fTheta); mat.m[1][1] = cosf(fTheta); mat.m[2][1] = 0.0f;
		mat.m[0][2] = 0.0f;			 mat.m[1][2] = 0.0f;		 mat.m[2][2] = 1.0f;
	}

	void Scale(matrix3x3 &mat, float sx, float sy)
	{
		mat.m[0][0] = sx;   mat.m[1][0] = 0.0f; mat.m[2][0] = 0.0f;
		mat.m[0][1] = 0.0f; mat.m[1][1] = sy;   mat.m[2][1] = 0.0f;
		mat.m[0][2] = 0.0f;	mat.m[1][2] = 0.0f;	mat.m[2][2] = 1.0f;
	}

	void Shear(matrix3x3 &mat, float sx, float sy)
	{	
		mat.m[0][0] = 1.0f; mat.m[1][0] = sx;   mat.m[2][0] = 0.0f;
		mat.m[0][1] = sy;   mat.m[1][1] = 1.0f; mat.m[2][1] = 0.0f;
		mat.m[0][2] = 0.0f;	mat.m[1][2] = 0.0f;	mat.m[2][2] = 1.0f;
	}

	void MatrixMultiply(matrix3x3 &matResult, matrix3x3 &matA, matrix3x3 &matB)
	{
		for (int c = 0; c < 3; c++)
		{
			for (int r = 0; r < 3; r++)
			{
				matResult.m[c][r] = matA.m[0][r] * matB.m[c][0] +
					                matA.m[1][r] * matB.m[c][1] +
					                matA.m[2][r] * matB.m[c][2];
			}
		}
	}

	void Forward(matrix3x3 &mat, float in_x, float in_y, float &out_x, float &out_y)
	{
		out_x = in_x * mat.m[0][0] + in_y * mat.m[1][0] + mat.m[2][0];
		out_y = in_x * mat.m[0][1] + in_y * mat.m[1][1] + mat.m[2][1];
	}

	void Invert(matrix3x3 &matIn, matrix3x3 &matOut)
	{
		float det = matIn.m[0][0] * (matIn.m[1][1] * matIn.m[2][2] - matIn.m[1][2] * matIn.m[2][1]) -
			matIn.m[1][0] * (matIn.m[0][1] * matIn.m[2][2] - matIn.m[2][1] * matIn.m[0][2]) +
			matIn.m[2][0] * (matIn.m[0][1] * matIn.m[1][2] - matIn.m[1][1] * matIn.m[0][2]);

		float idet = 1.0f / det;
		matOut.m[0][0] = (matIn.m[1][1] * matIn.m[2][2] - matIn.m[1][2] * matIn.m[2][1]) * idet;
		matOut.m[1][0] = (matIn.m[2][0] * matIn.m[1][2] - matIn.m[1][0] * matIn.m[2][2]) * idet;
		matOut.m[2][0] = (matIn.m[1][0] * matIn.m[2][1] - matIn.m[2][0] * matIn.m[1][1]) * idet;
		matOut.m[0][1] = (matIn.m[2][1] * matIn.m[0][2] - matIn.m[0][1] * matIn.m[2][2]) * idet;
		matOut.m[1][1] = (matIn.m[0][0] * matIn.m[2][2] - matIn.m[2][0] * matIn.m[0][2]) * idet;
		matOut.m[2][1] = (matIn.m[0][1] * matIn.m[2][0] - matIn.m[0][0] * matIn.m[2][1]) * idet;
		matOut.m[0][2] = (matIn.m[0][1] * matIn.m[1][2] - matIn.m[0][2] * matIn.m[1][1]) * idet;
		matOut.m[1][2] = (matIn.m[0][2] * matIn.m[1][0] - matIn.m[0][0] * matIn.m[1][2]) * idet;
		matOut.m[2][2] = (matIn.m[0][0] * matIn.m[1][1] - matIn.m[0][1] * matIn.m[1][0]) * idet;
	}


	float fRotate = 0.0f;

public:
	bool OnUserCreate() override
	{
		sprCar = new olc::Sprite("car_top1.png");

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		
		if (GetKey(olc::Key::Z).bHeld) fRotate -= 2.0f * fElapsedTime;
		if (GetKey(olc::Key::X).bHeld) fRotate += 2.0f * fElapsedTime;
		
		
		Clear(olc::DARK_CYAN);

		SetPixelMode(olc::Pixel::ALPHA);
		//DrawSprite(0, 0, sprCar, 3);
		

		matrix3x3 matFinal, matA, matB, matC, matFinalInv;
		Translate(matA, -100, -50);
		Rotate(matB, fRotate);
		MatrixMultiply(matC, matB, matA);

		Translate(matA, (float)ScreenWidth()/2, (float)ScreenHeight()/2);
		MatrixMultiply(matFinal, matA, matC);

		Invert(matFinal, matFinalInv);

		// Draws the dumb way, but leaves gaps
		/*for (int x = 0; x < sprCar->width; x++)
		{
			for (int y = 0; y < sprCar->height; y++)
			{
				olc::Pixel p = sprCar->GetPixel(x, y);

				float nx, ny;
				Forward(matFinal, (float)x, (float)y, nx, ny);
				Draw(nx, ny, p);
			}
		}*/

		// Work out bounding box of sprite post-transformation
		// by passing through sprite corner locations into 
		// transformation matrix
		float ex, ey;
		float sx, sy;
		float px, py;

		Forward(matFinal, 0.0f, 0.0f, px, py);
		sx = px; sy = py;
		ex = px; ey = py;

		Forward(matFinal, (float)sprCar->width, (float)sprCar->height, px, py);
		sx = std::min(sx, px); sy = std::min(sy, py);
		ex = std::max(ex, px); ey = std::max(ey, py);

		Forward(matFinal, 0.0f, (float)sprCar->height, px, py);
		sx = std::min(sx, px); sy = std::min(sy, py);
		ex = std::max(ex, px); ey = std::max(ey, py);

		Forward(matFinal, (float)sprCar->width, 0.0f, px, py);
		sx = std::min(sx, px); sy = std::min(sy, py);
		ex = std::max(ex, px); ey = std::max(ey, py);

		// Use transformed corner locations in screen space to establish
		// region of pixels to fill, using inverse transform to sample
		// sprite at suitable locations.
		for (int x = sx; x < ex; x++)
		{
			for (int y = sy; y < ey; y++)
			{
				float nx, ny;
				Forward(matFinalInv, (float)x, (float)y, nx, ny);
				olc::Pixel p = sprCar->GetPixel((int32_t)(nx + 0.5f), (int32_t)(ny + 0.5f));
				Draw(x, y, p);
			}
		}

		SetPixelMode(olc::Pixel::NORMAL);

		return true;
	}
};

int main()
{
	SpriteTransforms demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}