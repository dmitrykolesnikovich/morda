/**
 * @author Ivan Gagis <igagis@gmail.com>
 */


#pragma once

#include "core/container/Frame.hpp"
#include "label/TextLabel.hpp"
#include "label/ColorLabel.hpp"
#include "core/proxy/MouseProxy.hpp"
#include "core/container/Table.hpp"

namespace morda{



class Window :
		virtual public Widget,
		private Table
{
	morda::Vec2r emptyMinDim;//minimal dimension of empty window
	
	std::shared_ptr<ColorLabel> titleBg;
	std::uint32_t titleBgColorTopmost;
	std::uint32_t titleBgColorNonTopmost;
	
	std::shared_ptr<TextLabel> title;
	
	std::shared_ptr<Frame> contentArea;
	
	bool captionCaptured = false;
	bool leftTopResizeCaptured = false;
	bool leftBottomResizeCaptured = false;
	bool rightTopResizeCaptured = false;
	bool rightBottomResizeCaptured = false;
	bool leftResizeCaptured = false;
	bool rightResizeCaptured = false;
	bool topResizeCaptured = false;
	bool bottomResizeCaptured = false;
	
	morda::Vec2r capturePoint;
	
	void setupWidgets();
	
public:
	Window(const stob::Node* chain = nullptr);
	
	
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	
	void setTitle(const std::string& str);
	
	Frame& content(){
		return *this->contentArea;
	}
	

	bool onMouseButton(bool isDown, const morda::Vec2r& pos, EMouseButton button, unsigned pointerId)override;
	
	bool onMouseMove(const morda::Vec2r& pos, unsigned pointerId)override;

	void onTopmostChanged()override;
};

}
