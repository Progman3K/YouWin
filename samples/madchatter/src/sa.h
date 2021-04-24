#ifndef __SA_H__
#define __SA_H__


typedef struct tagSA : public sockaddr_in {

//    tagSA() {}

    tagSA( sockaddr_in sin ) {

        sin_family = sin.sin_family;
        sin_port   = sin.sin_port;
        sin_addr   = sin.sin_addr;

    }

    tagSA & operator = ( const sockaddr_in & sin ) {

        sin_family = sin.sin_family;
        sin_port   = sin.sin_port;
        sin_addr   = sin.sin_addr;

        return *this;

    }

    bool operator < ( const tagSA & sin ) const {

        if ( sin_family != sin.sin_family ) {

            return sin_family < sin.sin_family;

        }

        if ( sin_addr.s_addr != sin.sin_addr.s_addr ) {

            return sin_addr.s_addr < sin.sin_addr.s_addr;

        }

        return ( sin_port < sin.sin_port );

    }

//    sa_family_t    sin_family;
//    in_port_t      sin_port;
//    struct in_addr sin_addr;

} tSA;


#endif /* __SA_H__ */
