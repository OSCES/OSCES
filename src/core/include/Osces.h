#ifndef OSCES_H
#define OSCES_H

#if defined(NEEDS_OSCES_MAIN)
int osces_main(int, char **);
#define main osces_main
#endif

#endif // OSCES_H
