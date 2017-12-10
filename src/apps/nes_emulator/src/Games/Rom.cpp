
#include <stdint.h>

#define SUPER_MARIO

uint8_t GameFile[] =
{
#ifdef BALLON_FIGHT
#include "BalloonFight.h"
#endif

#ifdef BATTLE_CITY
#include "BattleCity.h"
#endif

#ifdef SUPER_MARIO
#include "SuperMario.h"
#endif

#ifdef CONTRA
#include "Contra.h"
#endif
};
