

#ifndef __INTERFACE_OUTPUT_H__
#define __INTERFACE_OUTPUT_H__


class IOutput {

    public:

        virtual int AppendText( const TCHAR * pszText, size_t StringSize, bool bOnANewLine ) = 0;

};


#endif /* __INTERFACE_OUTPUT_H__ */
