struct Mod
{
    char* Name;
    char* Description;
};

extern struct Mod *Mods;
extern struct Mod **LoadOrder;

extern int modCount;

extern void setRimworldPath(const char *path);
extern int detectRimworldPath();
extern int parseRimworldXML();