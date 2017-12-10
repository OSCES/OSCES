#ifndef VIDEOSYSTEM_H
#define VIDEOSYSTEM_H

// TODO: List<T> m_display

class AbstractDisplay;

class VideoSystem
{
public:
    VideoSystem();
    ~VideoSystem();

    AbstractDisplay* display(int display = 0) const;
    int displayCount() const;

    void addDisplay(AbstractDisplay *display);
    void removeDisplay(const AbstractDisplay *display);

private:
    int m_displayCount;
    AbstractDisplay *m_display; // primaryDisplay
};

#endif // VIDEOSYSTEM_H
