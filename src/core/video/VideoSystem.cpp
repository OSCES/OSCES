#include "VideoSystem.h"
#include "AbstractDisplay.h"

VideoSystem::VideoSystem() :
    m_displayCount(0),
    m_display(0)
{
}

VideoSystem::~VideoSystem()
{
}

AbstractDisplay *VideoSystem::display(int display) const
{
    if (display == 0)
        return m_display;
    return 0;
}

int VideoSystem::displayCount() const
{
    return m_displayCount;
}

void VideoSystem::addDisplay(AbstractDisplay *display)
{
    m_display = display;
    ++m_displayCount;
}

void VideoSystem::removeDisplay(const AbstractDisplay *display)
{
    (void)display;
    m_display = 0;
    --m_displayCount;
}
