#ifndef OSCESDEFS_H
#define OSCESDEFS_H

// TODO: Remove
#define NEEDS_OSCES_MAIN

#if defined(NEEDS_OSCES_MAIN)
//int osces_main(int, char **);
//int osces_main(Osces *osces);
int osces_main(int, char **);
#define main osces_main
#endif

#endif // OSCESDEFS_H
