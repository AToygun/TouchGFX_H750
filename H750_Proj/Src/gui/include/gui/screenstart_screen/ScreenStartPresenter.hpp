#ifndef SCREENSTARTPRESENTER_HPP
#define SCREENSTARTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenStartView;

class ScreenStartPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenStartPresenter(ScreenStartView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenStartPresenter() {};

private:
    ScreenStartPresenter();

    ScreenStartView& view;
};

#endif // SCREENSTARTPRESENTER_HPP
