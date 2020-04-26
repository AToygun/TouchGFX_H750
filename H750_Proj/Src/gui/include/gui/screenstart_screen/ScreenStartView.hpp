#ifndef SCREENSTARTVIEW_HPP
#define SCREENSTARTVIEW_HPP

#include <gui_generated/screenstart_screen/ScreenStartViewBase.hpp>
#include <gui/screenstart_screen/ScreenStartPresenter.hpp>

class ScreenStartView : public ScreenStartViewBase
{
public:
    ScreenStartView();
    virtual ~ScreenStartView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENSTARTVIEW_HPP
