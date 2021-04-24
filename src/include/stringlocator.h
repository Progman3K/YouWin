#ifndef H_STRING_LOCATOR_H
#define H_STRING_LOCATOR_H


typedef struct {

# if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned short blockposition  : 4;
    unsigned short blocknumber    : 12;
#else
    unsigned short blocknumber    : 12;
    unsigned short blockposition  : 4;
#endif

} stringlocator;


typedef union {

    stringlocator   ID;
    unsigned short  us;

} resourcestringlocator;


typedef struct {

    unsigned short wLen;
    unsigned short Text[];

} StringEntry;


#endif /* H_STRING_LOCATOR_H */
