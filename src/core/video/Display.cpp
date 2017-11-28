#include "Display.h"

static const int DisplayWidth = 400;
static const int DisplayHeight = 300;

#ifdef OSCES_BOARD
static const int DisplayDepth = 8;
#else
static const int DisplayDepth = 32;
#endif

Display::Display() :
    AbstractDisplay(),
    m_visibleBufferIndex(0),
    m_data(0),
    m_statusFlags(0),
    m_context(0),
    m_presentListener(0)
{
}

Display::~Display()
{
    delete[] m_data;
}

bool Display::initialize()
{
    // for OSCEC board initialize FSMC

    m_width = DisplayWidth;
    m_height = DisplayHeight;
    m_depth = DisplayDepth;
    m_bytesPerLine = m_width * m_depth / 8; // + some aligned bytes ?
    m_frameBufferSize = m_height * m_bytesPerLine;

    int infoBytesCount = 10;
    int videoRamSize = m_frameBufferSize * 2 + infoBytesCount;
    m_data = new uint8_t[videoRamSize];
    m_statusFlags = m_data + videoRamSize - 1;
    // clear flags
    *m_statusFlags = 0x0000;

    blankDisplay(false);

    return true;
}

uint8_t *Display::displayBuffer(AbstractDisplay::DisplayBufferType bufferType)
{
    if (bufferType == BackBuffer)
        return m_data + m_frameBufferSize * (m_visibleBufferIndex ^ 1);
    return m_data + m_frameBufferSize * m_visibleBufferIndex;
}

void Display::present()
{
    waitForVSync();

    m_visibleBufferIndex ^= 1;
    if (m_visibleBufferIndex == 1)
        *m_statusFlags |= 0x0001;
    else
        *m_statusFlags &= ~0x0001;

    if (m_presentListener)
        m_presentListener(m_context);
}

void Display::setPresentListener(PresentListener listener, void *context)
{
    m_presentListener = listener;
    m_context = context;
}

void Display::waitForVSync() const
{
    if (!m_vsyncEnabled)
        return;

    while (!(*m_statusFlags & 0x0002))
    {
        // TODO: implement timeout
        // wait count sleep?
        // etc.
    }
}
