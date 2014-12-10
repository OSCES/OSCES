#include "KeyboardPlatform.h"

void KeyboardPlatform_t::OnEvent(Key_t& key)
{
    if( 0 != m_fpCallBack )
        m_fpCallBack( m_pContext, key );
}
