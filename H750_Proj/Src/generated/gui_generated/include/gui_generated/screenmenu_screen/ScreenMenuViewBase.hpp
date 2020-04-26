/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREENMENUVIEWBASE_HPP
#define SCREENMENUVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screenmenu_screen/ScreenMenuPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>

class ScreenMenuViewBase : public touchgfx::View<ScreenMenuPresenter>
{
public:
    ScreenMenuViewBase();
    virtual ~ScreenMenuViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image background;
    touchgfx::Button button1;

private:

};

#endif // SCREENMENUVIEWBASE_HPP