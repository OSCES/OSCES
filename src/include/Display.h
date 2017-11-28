#ifndef DISPLAY_H
#define DISPLAY_H

#include "AbstractDisplay.h"

/*
 * Flag byte:
 *                 +---+---+---+---+---+---+---+---+
 *                 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *                 +---+---+---+---+---+---+---+---+
 *                   ^   ^   ^   ^   ^   ^   ^   ^
 *       reserved ---+---+---+---+---+---+   |   |
 *          vsync ---------------------------+   |
 *  buffer index  -------------------------------+
 *
 *  VSync       : 1 - vsync signal is set --> workaround on OSCES HW bug *
 *  Buffer index: 0 or 1 --> we have only two buffers
 *
 */

#ifndef OSCES_BOARD
typedef void (*PresentListener)(void *context);
#endif

class Display : public AbstractDisplay
{
public:
    Display();
    ~Display();

    bool initialize();
    uint8_t* displayBuffer(DisplayBufferType bufferType = BackBuffer);
    void present();

#ifndef OSCES_BOARD
    void setPresentListener(PresentListener listener, void *context);
#endif

private:
    void waitForVSync() const;

private:
    // TODO: hide impl
    int m_visibleBufferIndex;
    uint8_t *m_data;
    uint8_t *m_statusFlags;

#ifndef OSCES_BOARD
    void *m_context;
    PresentListener m_presentListener;
#endif
};

#endif // DISPLAY_H
