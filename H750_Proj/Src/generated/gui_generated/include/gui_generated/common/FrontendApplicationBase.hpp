/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDAPPLICATIONBASE_HPP
#define FRONTENDAPPLICATIONBASE_HPP

#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

class FrontendApplicationBase : public touchgfx::MVPApplication
{
public:
    FrontendApplicationBase(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplicationBase() { }

    // ScreenStart
    void gotoScreenStartScreenNoTransition();

    // ScreenMenu
    void gotoScreenMenuScreenSlideTransitionSouth();

protected:
    touchgfx::Callback<FrontendApplicationBase> transitionCallback;
    FrontendHeap& frontendHeap;
    Model& model;

    // ScreenStart
    void gotoScreenStartScreenNoTransitionImpl();

    // ScreenMenu
    void gotoScreenMenuScreenSlideTransitionSouthImpl();
};

#endif // FRONTENDAPPLICATIONBASE_HPP
