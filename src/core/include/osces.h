#ifndef OSCES_H
#define OSCES_H

// TODO: Remove
#define NEEDS_OSCES_MAIN

#if defined(NEEDS_OSCES_MAIN)
int osces_main(int, char **);
#define main osces_main
#endif

#endif // OSCES_H
