/* The MIT License:

Copyright (c) 2012-2015 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

// Home page: http://morda.googlecode.com

/**
 * @author Ivan Gagis <igagis@gmail.com>
 */

#pragma once

#include <ting/config.hpp>
#include <ting/types.hpp>
#include <ting/Singleton.hpp>
#include <ting/Buffer.hpp>

#include "../render/Render.hpp"

#include "../util/Matrix4.hpp"
#include "../util/Vector3.hpp"
#include "../util/Vector2.hpp"



//TODO: remove
#include "../config.hpp"

#if M_MORDA_RENDER == M_MORDA_RENDER_OPENGL
#	include <GL/glew.h>

#	if M_OS == M_OS_LINUX
#		include <GL/glx.h>
#	else
#		include <ting/windows.hpp>
#	endif

#elif M_MORDA_RENDER == M_MORDA_RENDER_OPENGLES
#		include <GLES2/gl2.h>
#		include <EGL/egl.h>
#else
#	error "unknown render API"
#endif






namespace morda{



/**
 * @brief Abstract shader.
 * Each shader has at least matrix uniform.
 * Matrix uniform should be 'mat4' and named 'matrix'.
 */
class Shader{
	friend class Render;
	
	static Shader* boundShader;
	
	
	std::unique_ptr<Render::Program> program;

	const Render::InputID matrixUniform;
	
protected:
	Render::InputID getAttribute(const char* n){
		return Render::getAttribute(*this->program, n);
	}
	
	Render::InputID getUniform(const char* n){
		return Render::getUniform(*this->program, n);
	}

	Shader(const char* vertexShaderCode = nullptr, const char* fragmentShaderCode = nullptr);

	void renderArrays(Render::EMode mode, unsigned numElements){
		ASSERT(this->IsBound())
		Render::renderArrays(mode, numElements);
	}
	
	void renderElements(Render::EMode mode, ting::Buffer<const std::uint16_t> i){
		ASSERT(this->IsBound())
		Render::renderElements(mode, i);
	}
	
	void setUniformMatrix4f(Render::InputID id, const morda::Matr4f& m){
		ASSERT(this->IsBound())
		Render::setUniformMatrix4f(id, m);
	}
	
	void setUniform1i(Render::InputID id, int i){
		ASSERT(this->IsBound())
		Render::setUniform1i(id, i);
	}
	
	void setUniform2f(Render::InputID id, Vec2f v){
		ASSERT(this->IsBound())
		Render::setUniform2f(id, v);
	}
	
	void setUniform4f(Render::InputID id, float x, float y, float z, float a){
		ASSERT(this->IsBound())
		Render::setUniform4f(id, x, y, z, a);
	}
	
	void setUniform4f(Render::InputID id, ting::Buffer<const Vec4f> v){
		ASSERT(this->IsBound())
		Render::setUniform4f(id, v);
	}
	
	void setVertexAttribArray(Render::InputID id, ting::Buffer<const Vec3f> a){
		ASSERT(this->IsBound())
		Render::setVertexAttribArray(id, &*a.begin());
	}
	
	void setVertexAttribArray(Render::InputID id, ting::Buffer<const Vec2f> a){
		ASSERT(this->IsBound())
		Render::setVertexAttribArray(id, &*a.begin());
	}
public:
	
	
	virtual ~Shader()NOEXCEPT{}

	void Bind(){//TODO: make private
		if(this->IsBound()){
			return;
		}
		
		Render::bindShader(*this->program);
		boundShader = this;
	}

	bool IsBound()const NOEXCEPT{//TODO: make private
		return this == boundShader;
	}
	
	void SetMatrix(const morda::Matr4f &m){
		ASSERT(this->IsBound())
		this->setUniformMatrix4f(this->matrixUniform, m);
	}
	
	//TODO: remove
	static void AssertOpenGLNoError(){

	}
};//~class Shader



}//~namespace
