#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Riman.h"

struct Mod *Mods = NULL;
struct Mod **LoadOrder = NULL;

int modCount = 0;

static char rimworldModPath[256];

void setRimworldPath(const char *path) {
  for (unsigned char a = 0; a < 255; a++){
    rimworldModPath[a] = path[a];  
    if (path[a] == '\0')
        break;
  }
};

int detectRimworldPath() {
#ifdef _WIN32
  char *userProfile = getenv("USERPROFILE");
  snprintf(rimworldModPath, sizeof(rimworldModPath),
           "%s\\AppData\\LocalLow\\Ludeon Studios\\RimWorld by Ludeon "
           "Studios\\Config\\ModsConfig.xml",
           userProfile);
#elif defined(__linux__)
  char *home = getenv("HOME");
  snprintf(rimworldModPath, sizeof(rimworldModPath),
           "%s/.config/unity3d/Ludeon Studios/RimWorld by Ludeon "
           "Studios/Config/ModsConfig.xml",
           home);
#elif defined(__APPLE__)
  char *home = getenv("HOME");
  snprintf(rimworldModPath, sizeof(rimworldModPath),
           "%s/Library/Application Support/unity.Ludeon Studios.RimWorld by "
           "Ludeon Studios/Config/ModsConfig.xml",
           home);
#endif
};

int parseRimworldXML() {
    xmlDocPtr doc;
    xmlNodePtr root, curNode, activeModsNode;
  
    doc = xmlParseFile(rimworldModPath);
    if (doc == NULL) {
      return -1; // fail parse
    }
  
    root = xmlDocGetRootElement(doc);
    if (root == NULL) {
      xmlFreeDoc(doc);
      return -2; // empty xml doc
    }
    activeModsNode = NULL;
    for (curNode = root->children; curNode; curNode = curNode->next) {
      if (curNode->type == XML_ELEMENT_NODE &&
          strcmp((char *)curNode->name, "activeMods") == 0) {
        activeModsNode = curNode;
        break;
      }
    }
    if (activeModsNode == NULL) {
      xmlFreeDoc(doc);
      return -3; // active mods not found?
    }
    for (curNode = activeModsNode->children; curNode; curNode = curNode->next) {
      if (curNode->type == XML_ELEMENT_NODE && strcmp((char *)curNode->name, "li") == 0) {
        modCount++;
        Mods = realloc(Mods, modCount * sizeof(struct Mod));
        Mods[modCount - 1].Name = strdup((char *)xmlNodeGetContent(curNode));
        Mods[modCount - 1].Description =
            NULL; // Load description somewhere else, idfk where.
      }
    }
  
    LoadOrder = malloc(modCount * sizeof(struct Mod *));
    for (int i = 0; i < modCount; i++) {
      LoadOrder[i] = &Mods[i];
    }
  
    xmlFreeDoc(doc);
    xmlCleanupParser();
  
    return 0;
  }
  
