#pragma once

#include <algorithm>
#include <iostream>
#include <string>

#include <cubicvr2/opengl/opengl_support.h>
#include <cubicvr2/image/lodepng.h>

using namespace std;


namespace CubicVR {

	class Texture {
	public:
		GLuint width;
		GLuint height;
		GLuint texId, texSampler;

		Texture() {
			glGenTextures(1, &texId);
			glGenSamplers(1, &texSampler);

			glSamplerParameteri(texSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glSamplerParameteri(texSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		GLuint textureId() {
			return texId;
		}

		void bind(GLuint texIndex) {
			glActiveTexture(GL_TEXTURE0+texIndex);
			glBindTexture(GL_TEXTURE_2D, texId);
			glBindSampler(texIndex, texSampler);
			
		}

		bool loadPNG(string filename) {
			
			LodePNG::Decoder pngDecoder;
			std::vector<unsigned char> buffer;
			std::vector<unsigned char> image;

			cout << "Loading png file " << filename << endl;

			LodePNG::loadFile(buffer, filename.c_str());

			LodePNG_inspect(&pngDecoder, &buffer[0], buffer.size());

			pngDecoder.getInfoRaw().color.colorType = (pngDecoder.getInfoPng().color.colorType == 6) ? 6 : 2;

			cout << "Calling PNG decoder.." << endl;
			pngDecoder.decode(image, buffer);

			cout << "Checking decoder state.." << endl;
			if (pngDecoder.hasError())
			{
				cout << "[loadTextureFromPng] Error [" << pngDecoder.getError() << "] while trying to load " << filename << endl;
				return false;
			}

			int pngwidth = pngDecoder.getWidth();
			int pngheight = pngDecoder.getHeight();

			cout << "PNG Decoder Info [ width: " << pngwidth << ", height: " << pngheight << " ].." << endl;

			std::vector<unsigned char>::iterator iStart, iEnd, iTarget;

			GLuint format = pngDecoder.isAlphaType() ? GL_RGBA : GL_RGB;

			GLuint bpp = pngDecoder.isAlphaType() ? 32 : 24;

			cout << "Alpha? " << (pngDecoder.isAlphaType() ? "Yes" : "No") << endl;

			cout << "Swapping ranges" << endl;

			unsigned short stride = bpp / 8;

			for (int i = 0; i < pngheight / 2; i++)
			{
				iStart = image.begin() + (i *  (pngwidth * stride));
				iEnd = iStart + (pngwidth * stride);
				iTarget = image.begin() + (((pngheight - 1) - i) *  (pngwidth * stride));
				swap_ranges(iStart, iEnd, iTarget);
			}

			width = pngwidth;
			height = pngheight;

			glBindTexture(GL_TEXTURE_2D, texId);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, &image[0]);

			return true;

		}

	};

}