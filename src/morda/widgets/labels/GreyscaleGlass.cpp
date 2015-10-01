#include "GreyscaleGlass.hpp"

#include "../../render/Texture2D.hpp"

#include "../../App.hpp"


using namespace morda;



GreyscaleGlass::GreyscaleGlass(const stob::Node* chain) :
		Widget(chain)
{}



void GreyscaleGlass::render(const morda::Matr4r& matrix) const{
	Texture2D texture(this->rect().d.to<unsigned>(), 3, Render::ETexFilter::NEAREST, Render::ETexFilter::NEAREST);
	//texture is bound right after creation
	
	Recti viewPortRect = this->ComputeViewportRect(matrix);
	
	if(!viewPortRect.d.isPositive()){
		return;
	}
	
	Render::copyColorBufferToTexture(Vec2i(0), viewPortRect);
	
	morda::Matr4r matr(matrix);
	matr.scale(this->rect().d);

	morda::PosTexShader &s = App::inst().Shaders().simpleGrayscalePosTexShader;

	s.SetMatrix(matr);
	
	s.render(utki::wrapBuf(morda::PosShader::quad01Fan), utki::wrapBuf(s.quadFanTexCoords));
}
