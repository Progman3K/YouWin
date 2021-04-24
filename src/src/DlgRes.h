#ifndef YW_DLG_RES_H
#define YW_DLG_RES_H


#include <classatoms.h>
#include <UTF16.h>


typedef struct {

    unsigned int    uiDataVersion;  /* Should be 0 */
    unsigned short  usMemoryFlags;
    unsigned short  usLanguageID;
    unsigned int    uiVersion;
    unsigned int    uiCharacteristics;

} DIALOG_ATTRIBUTES;


typedef struct {

    unsigned short  usPointSize;    // Only here if FONT set for dialog 
    UTF_16          FontName[];     // This too 

} DIALOG_FONT_INFO;


#endif /* YW_DLG_RES_H */
