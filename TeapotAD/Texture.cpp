#include "Texture.h"
#include <stdexcept>

static GLenum TextureFormatForBitmapFormat(Bitmap::Format format)
{
	switch (format) {
	case Bitmap::Format_RGB: return gl::RGB;
	case Bitmap::Format_RGBA: return gl::RGBA;
	default: throw std::runtime_error("Unrecognised Bitmap::Format");
	}
}

Texture::Texture(const Bitmap& bitmap, GLint minMagFiler, GLint wrapMode) :
	_originalWidth((GLfloat)bitmap.width()),
	_originalHeight((GLfloat)bitmap.height())
{
	gl::GenTextures(1, &_object);
	gl::BindTexture(gl::TEXTURE_2D, _object);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, minMagFiler);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, minMagFiler);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, wrapMode);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, wrapMode);
	gl::TexImage2D(gl::TEXTURE_2D,
		0,
		TextureFormatForBitmapFormat(bitmap.format()),
		(GLsizei)bitmap.width(),
		(GLsizei)bitmap.height(),
		0,
		TextureFormatForBitmapFormat(bitmap.format()),
		gl::UNSIGNED_BYTE,
		bitmap.pixelBuffer());
	gl::BindTexture(gl::TEXTURE_2D, 0);
}

Texture::~Texture()
{
	gl::DeleteTextures(1, &_object);
}

GLuint Texture::object() const
{
	return _object;
}

GLfloat Texture::originalWidth() const
{
	return _originalWidth;
}

GLfloat Texture::originalHeight() const
{
	return _originalHeight;
}