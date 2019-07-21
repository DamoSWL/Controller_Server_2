#ifndef _CRC_H_
#define _CRC_H_

#include <QtGlobal>


namespace CRC
{
    typedef union
    {
            quint16 crcData;
            quint8 crcByte[2];
    }CRCData;




    inline unsigned int calccrc(unsigned char crcbuf,unsigned int crc)
    {
        unsigned char i;
        unsigned char chk;
        crc=crc ^ crcbuf;
        for(i=0;i<8;i++)
        {
                chk=( unsigned char)(crc&1);
                crc=crc>>1;
                crc=crc&0x7fff;
                if (chk==1)
                        crc=crc^0xa001;
                crc=crc&0xffff;
        }
        return crc;
    }

    inline unsigned int chkcrc(unsigned char *buf,unsigned char len)
    {
        unsigned char hi,lo;
        unsigned int i;
        unsigned int crc;
        crc=0xFFFF;
        for(i=0;i<len;i++)
        {
                crc=calccrc(*buf,crc);
                buf++;
        }
        hi=( unsigned char)(crc%256);
        lo=( unsigned char)(crc/256);
        crc=(((unsigned int)(hi))<<8)|lo;
        return crc;
    }




}






#endif
