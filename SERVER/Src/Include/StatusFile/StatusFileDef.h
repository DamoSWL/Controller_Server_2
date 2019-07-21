#ifndef STATUSFILEDEF_H
#define STATUSFILEDEF_H

#include <QtGlobal>


namespace RadarDef {

    typedef struct _RadarStatusCF3
    {
        // siteinfo
        char Country[16];
        char Province[16];
        char StationNumber[16];
        char Station[16];
        char RadarType[16];
        char Longitude[16];
        char Latitude[16];
        char Altitude[16];
        char Temp0[40];

        //   systemStatus

           quint16 Year;
           quint8 Month;
           quint8 Day;
           quint8 Hour;
           quint8 Minute;
           quint8 Second;

           quint8 RadarStatus;
           quint8 SubsysNum;
           quint8 Subsys0;
           quint8 Subsys1;
           quint8 Subsys2;
           quint8 Subsys3;
           quint8 Subsys4;
           quint8 Subsys5;
           quint8 Subsys6;
           quint8 Subsys7;
           quint8 Subsys8;
           quint8 Temp1[40];

           //SubSystemStatus0

           quint8 SysCode0;
           quint8 Partnum0;

           quint16 subsystem0_PartCode0;
           quint8 subsystem0_StatusFlag0;
           quint16 subsystem0_PartCode1;
           quint8 subsystem0_StatusFlag1;
           quint16 subsystem0_PartCode2;
           quint8 subsystem0_StatusFlag2;
           quint16 subsystem0_PartCode3;
           quint8 subsystem0_StatusFlag3;
           quint16 subsystem0_PartCode4;
           quint8 subsystem0_StatusFlag4;
           quint16 subsystem0_PartCode5;
           quint8 subsystem0_StatusFlag5;
           quint16 subsystem0_PartCode6;
           quint8 subsystem0_StatusFlag6;
           quint16 subsystem0_PartCode7;
           quint8 subsystem0_StatusFlag7;
           quint16 subsystem0_PartCode8;
           quint8 subsystem0_StatusFlag8;
           quint16 subsystem0_PartCode9;
           quint8 subsystem0_StatusFlag9;
           quint16 subsystem0_PartCode10;
           quint8 subsystem0_StatusFlag10;
           quint16 subsystem0_PartCode11;
           quint8 subsystem0_StatusFlag11;
           quint16 subsystem0_PartCode12;
           quint8 subsystem0_StatusFlag12;
           quint16 subsystem0_PartCode13;
           quint8 subsystem0_StatusFlag13;
           quint16 subsystem0_PartCode14;
           quint8 subsystem0_StatusFlag14;
           quint16 subsystem0_PartCode15;
           quint8 subsystem0_StatusFlag15;
           quint16 subsystem0_PartCode16;
           quint8 subsystem0_StatusFlag16;
           quint16 subsystem0_PartCode17;
           quint8 subsystem0_StatusFlag17;
           quint16 subsystem0_PartCode18;
           quint8 subsystem0_StatusFlag18;
           quint16 subsystem0_PartCode19;
           quint8 subsystem0_StatusFlag19;
           quint16 subsystem0_PartCode20;
           quint8 subsystem0_StatusFlag20;
           quint16 subsystem0_PartCode21;
           quint8 subsystem0_StatusFlag21;
           quint16 subsystem0_PartCode22;
           quint8 subsystem0_StatusFlag22;
           quint16 subsystem0_PartCode23;
           quint8 subsystem0_StatusFlag23;
           quint16 subsystem0_PartCode24;
           quint8 subsystem0_StatusFlag24;
           quint16 subsystem0_PartCode25;
           quint8 subsystem0_StatusFlag25;
           quint16 subsystem0_PartCode26;
           quint8 subsystem0_StatusFlag26;
           quint16 subsystem0_PartCode27;
           quint8 subsystem0_StatusFlag27;
           quint16 subsystem0_PartCode28;
           quint8 subsystem0_StatusFlag28;

           //SubSystemStatus1

           quint8 SysCode1;
           quint8 Partnum1;

           quint16 subsystem1_PartCode0;
           quint8 subsystem1_StatusFlag0;
           quint16 subsystem1_PartCode1;
           quint8 subsystem1_StatusFlag1;
           quint16 subsystem1_PartCode2;
           quint8 subsystem1_StatusFlag2;
           quint16 subsystem1_PartCode3;
           quint8 subsystem1_StatusFlag3;
           quint16 subsystem1_PartCode4;
           quint8 subsystem1_StatusFlag4;
           quint16 subsystem1_PartCode5;
           quint8 subsystem1_StatusFlag5;


           //SubSystemStatus2

           quint8 SysCode2;
           quint8 Partnum2;

           quint16 subsystem2_PartCode0;
           quint8 subsystem2_StatusFlag0;
           quint16 subsystem2_PartCode1;
           quint8 subsystem2_StatusFlag1;
           quint16 subsystem2_PartCode2;
           quint8 subsystem2_StatusFlag2;
           quint16 subsystem2_PartCode3;
           quint8 subsystem2_StatusFlag3;
           quint16 subsystem2_PartCode4;
           quint8 subsystem2_StatusFlag4;
           quint16 subsystem2_PartCode5;
           quint8 subsystem2_StatusFlag5;

           //SubSystemStatus3
           quint8 SysCode3;
           quint8 Partnum3;

           quint16 subsystem3_PartCode0;
           quint8 subsystem3_StatusFlag0;
           quint16 subsystem3_PartCode1;
           quint8 subsystem3_StatusFlag1;

           //SubSystemStatus4
          quint8 subsystem4_SysCode4;
          quint8 subsystem4_Partnum4;
          quint16 subsystem4_PartCode0;
          quint8 subsystem4_StatusFlag0;

           //SubSystemStatus5

          quint8 subsystem5_SysCode5;
          quint8 subsystem5_Partnum5;
          quint16 subsystem5_PartCode0;
          quint8 subsystem5_StatusFlag0;


        //SubSystemStatus6
          quint8 subsystem6_SysCode6;
          quint8 subsystem6_Partnum6;
          quint16 subsystem6_PartCode0;
          quint8 subsystem6_StatusFlag0;

      //SubSystemStatus7
          quint8 subsystem7_SysCode7;
          quint8 subsystem7_Partnum7;
          quint16 subsystem7_PartCode0;
          quint8 subsystem7_StatusFlag0;

          quint8 MOBS_SysCode0;
          quint8 MOBS_Obsdatanum0;
          float MOBS_Obsdata0;
          quint8 MOBS_SysCode1;
          quint8 MOBS_Obsdatanum1;
          float MOBS_Obsdata1;

    }__attribute__((packed)) RadarStatusCF3;


    typedef struct _RadarStatusCF6
    {
    // siteinfo
        char Country[16];
        char Province[16];
        char StationNumber[16];
        char Station[16];
        char RadarType[16];
        char Longitude[16];
        char Latitude[16];
        char Altitude[16];
        char Temp0[40];
 //   systemStatus

        quint16 Year;
        quint8 Month;
        quint8 Day;
        quint8 Hour;
        quint8 Minute;
        quint8 Second;

        quint8 RadarStatus;
        quint8 SubsysNum;
        quint8 Subsys0;
        quint8 Subsys1;
        quint8 Subsys2;
        quint8 Subsys3;
        quint8 Subsys4;
        quint8 Subsys5;
        quint8 Subsys6;
        quint8 Subsys7;
        quint8 Subsys8;
        quint8 Temp1[40];

    //SubSystemStatus0

        quint8 SysCode0;
        quint8 Partnum0;

        quint16 subsystem0_PartCode0;
        quint8 subsystem0_StatusFlag0;
        quint16 subsystem0_PartCode1;
        quint8 subsystem0_StatusFlag1;
        quint16 subsystem0_PartCode2;
        quint8 subsystem0_StatusFlag2;
        quint16 subsystem0_PartCode3;
        quint8 subsystem0_StatusFlag3;
        quint16 subsystem0_PartCode4;
        quint8 subsystem0_StatusFlag4;
        quint16 subsystem0_PartCode5;
        quint8 subsystem0_StatusFlag5;
        quint16 subsystem0_PartCode6;
        quint8 subsystem0_StatusFlag6;
        quint16 subsystem0_PartCode7;
        quint8 subsystem0_StatusFlag7;
        quint16 subsystem0_PartCode8;
        quint8 subsystem0_StatusFlag8;
        quint16 subsystem0_PartCode9;
        quint8 subsystem0_StatusFlag9;
        quint16 subsystem0_PartCode10;
        quint8 subsystem0_StatusFlag10;
        quint16 subsystem0_PartCode11;
        quint8 subsystem0_StatusFlag11;
        quint16 subsystem0_PartCode12;
        quint8 subsystem0_StatusFlag12;
        quint16 subsystem0_PartCode13;
        quint8 subsystem0_StatusFlag13;
        quint16 subsystem0_PartCode14;
        quint8 subsystem0_StatusFlag14;
        quint16 subsystem0_PartCode15;
        quint8 subsystem0_StatusFlag15;
        quint16 subsystem0_PartCode16;
        quint8 subsystem0_StatusFlag16;
        quint16 subsystem0_PartCode17;
        quint8 subsystem0_StatusFlag17;
        quint16 subsystem0_PartCode18;
        quint8 subsystem0_StatusFlag18;
        quint16 subsystem0_PartCode19;
        quint8 subsystem0_StatusFlag19;
        quint16 subsystem0_PartCode20;
        quint8 subsystem0_StatusFlag20;
        quint16 subsystem0_PartCode21;
        quint8 subsystem0_StatusFlag21;
        quint16 subsystem0_PartCode22;
        quint8 subsystem0_StatusFlag22;
        quint16 subsystem0_PartCode23;
        quint8 subsystem0_StatusFlag23;
        quint16 subsystem0_PartCode24;
        quint8 subsystem0_StatusFlag24;
        quint16 subsystem0_PartCode25;
        quint8 subsystem0_StatusFlag25;
        quint16 subsystem0_PartCode26;
        quint8 subsystem0_StatusFlag26;
        quint16 subsystem0_PartCode27;
        quint8 subsystem0_StatusFlag27;
        quint16 subsystem0_PartCode28;
        quint8 subsystem0_StatusFlag28;
        quint16 subsystem0_PartCode29;
        quint8 subsystem0_StatusFlag29;
        quint16 subsystem0_PartCode30;
        quint8 subsystem0_StatusFlag30;
        quint16 subsystem0_PartCode31;
        quint8 subsystem0_StatusFlag31;
        quint16 subsystem0_PartCode32;
        quint8 subsystem0_StatusFlag32;
        quint16 subsystem0_PartCode33;
        quint8 subsystem0_StatusFlag33;
        quint16 subsystem0_PartCode34;
        quint8 subsystem0_StatusFlag34;
        quint16 subsystem0_PartCode35;
        quint8 subsystem0_StatusFlag35;
        quint16 subsystem0_PartCode36;
        quint8 subsystem0_StatusFlag36;
        quint16 subsystem0_PartCode37;
        quint8 subsystem0_StatusFlag37;
        quint16 subsystem0_PartCode38;
        quint8 subsystem0_StatusFlag38;
        quint16 subsystem0_PartCode39;
        quint8 subsystem0_StatusFlag39;
        quint16 subsystem0_PartCode40;
        quint8 subsystem0_StatusFlag40;
        quint16 subsystem0_PartCode41;
        quint8 subsystem0_StatusFlag41;
        quint16 subsystem0_PartCode42;
        quint8 subsystem0_StatusFlag42;
        quint16 subsystem0_PartCode43;
        quint8 subsystem0_StatusFlag43;
        quint16 subsystem0_PartCode44;
        quint8 subsystem0_StatusFlag44;
        quint16 subsystem0_PartCode45;
        quint8 subsystem0_StatusFlag45;
        quint16 subsystem0_PartCode46;
        quint8 subsystem0_StatusFlag46;
        quint16 subsystem0_PartCode47;
        quint8 subsystem0_StatusFlag47;


    //SubSystemStatus1

        quint8 SysCode1;
        quint8 Partnum1;

        quint16 subsystem1_PartCode0;
        quint8 subsystem1_StatusFlag0;
        quint16 subsystem1_PartCode1;
        quint8 subsystem1_StatusFlag1;
        quint16 subsystem1_PartCode2;
        quint8 subsystem1_StatusFlag2;
        quint16 subsystem1_PartCode3;
        quint8 subsystem1_StatusFlag3;
        quint16 subsystem1_PartCode4;
        quint8 subsystem1_StatusFlag4;
        quint16 subsystem1_PartCode5;
        quint8 subsystem1_StatusFlag5;
        quint16 subsystem1_PartCode6;
        quint8 subsystem1_StatusFlag6;
        quint16 subsystem1_PartCode7;
        quint8 subsystem1_StatusFlag7;
        quint16 subsystem1_PartCode8;
        quint8 subsystem1_StatusFlag8;
        quint16 subsystem1_PartCode9;
        quint8 subsystem1_StatusFlag9;
        quint16 subsystem1_PartCode10;
        quint8 subsystem1_StatusFlag10;
        quint16 subsystem1_PartCode11;
        quint8 subsystem1_StatusFlag11;
        quint16 subsystem1_PartCode12;
        quint8 subsystem1_StatusFlag12;
        quint16 subsystem1_PartCode13;
        quint8 subsystem1_StatusFlag13;
        quint16 subsystem1_PartCode14;
        quint8 subsystem1_StatusFlag14;
        quint16 subsystem1_PartCode15;
        quint8 subsystem1_StatusFlag15;
        quint16 subsystem1_PartCode16;
        quint8 subsystem1_StatusFlag16;
        quint16 subsystem1_PartCode17;
        quint8 subsystem1_StatusFlag17;
        quint16 subsystem1_PartCode18;
        quint8 subsystem1_StatusFlag18;
        quint16 subsystem1_PartCode19;
        quint8 subsystem1_StatusFlag19;
        quint16 subsystem1_PartCode20;
        quint8 subsystem1_StatusFlag20;
        quint16 subsystem1_PartCode21;
        quint8 subsystem1_StatusFlag21;
        quint16 subsystem1_PartCode22;
        quint8 subsystem1_StatusFlag22;
        quint16 subsystem1_PartCode23;
        quint8 subsystem1_StatusFlag23;
        quint16 subsystem1_PartCode24;
        quint8 subsystem1_StatusFlag24;
        quint16 subsystem1_PartCode25;
        quint8 subsystem1_StatusFlag25;
        quint16 subsystem1_PartCode26;
        quint8 subsystem1_StatusFlag26;
        quint16 subsystem1_PartCode27;
        quint8 subsystem1_StatusFlag27;
        quint16 subsystem1_PartCode28;
        quint8 subsystem1_StatusFlag28;
        quint16 subsystem1_PartCode29;
        quint8 subsystem1_StatusFlag29;
        quint16 subsystem1_PartCode30;
        quint8 subsystem1_StatusFlag30;
        quint16 subsystem1_PartCode31;
        quint8 subsystem1_StatusFlag31;
        quint16 subsystem1_PartCode32;
        quint8 subsystem1_StatusFlag32;
        quint16 subsystem1_PartCode33;
        quint8 subsystem1_StatusFlag33;
        quint16 subsystem1_PartCode34;
        quint8 subsystem1_StatusFlag34;
        quint16 subsystem1_PartCode35;
        quint8 subsystem1_StatusFlag35;
        quint16 subsystem1_PartCode36;
        quint8 subsystem1_StatusFlag36;
        quint16 subsystem1_PartCode37;
        quint8 subsystem1_StatusFlag37;
        quint16 subsystem1_PartCode38;
        quint8 subsystem1_StatusFlag38;
        quint16 subsystem1_PartCode39;
        quint8 subsystem1_StatusFlag39;
        quint16 subsystem1_PartCode40;
        quint8 subsystem1_StatusFlag40;
        quint16 subsystem1_PartCode41;
        quint8 subsystem1_StatusFlag41;
        quint16 subsystem1_PartCode42;
        quint8 subsystem1_StatusFlag42;
        quint16 subsystem1_PartCode43;
        quint8 subsystem1_StatusFlag43;
        quint16 subsystem1_PartCode44;
        quint8 subsystem1_StatusFlag44;
        quint16 subsystem1_PartCode45;
        quint8 subsystem1_StatusFlag45;
        quint16 subsystem1_PartCode46;
        quint8 subsystem1_StatusFlag46;
        quint16 subsystem1_PartCode47;
        quint8 subsystem1_StatusFlag47;
        quint16 subsystem1_PartCode48;
        quint8 subsystem1_StatusFlag48;
        quint16 subsystem1_PartCode49;
        quint8 subsystem1_StatusFlag49;
        quint16 subsystem1_PartCode50;
        quint8 subsystem1_StatusFlag50;
        quint16 subsystem1_PartCode51;
        quint8 subsystem1_StatusFlag51;
        quint16 subsystem1_PartCode52;
        quint8 subsystem1_StatusFlag52;
        quint16 subsystem1_PartCode53;
        quint8 subsystem1_StatusFlag53;
        quint16 subsystem1_PartCode54;
        quint8 subsystem1_StatusFlag54;
        quint16 subsystem1_PartCode55;
        quint8 subsystem1_StatusFlag55;
        quint16 subsystem1_PartCode56;
        quint8 subsystem1_StatusFlag56;
        quint16 subsystem1_PartCode57;
        quint8 subsystem1_StatusFlag57;
        quint16 subsystem1_PartCode58;
        quint8 subsystem1_StatusFlag58;
        quint16 subsystem1_PartCode59;
        quint8 subsystem1_StatusFlag59;
        quint16 subsystem1_PartCode60;
        quint8 subsystem1_StatusFlag60;
        quint16 subsystem1_PartCode61;
        quint8 subsystem1_StatusFlag61;
        quint16 subsystem1_PartCode62;
        quint8 subsystem1_StatusFlag62;
        quint16 subsystem1_PartCode63;
        quint8 subsystem1_StatusFlag63;
        quint16 subsystem1_PartCode64;
        quint8 subsystem1_StatusFlag64;
        quint16 subsystem1_PartCode65;
        quint8 subsystem1_StatusFlag65;
        quint16 subsystem1_PartCode66;
        quint8 subsystem1_StatusFlag66;
        quint16 subsystem1_PartCode67;
        quint8 subsystem1_StatusFlag67;
        quint16 subsystem1_PartCode68;
        quint8 subsystem1_StatusFlag68;
        quint16 subsystem1_PartCode69;
        quint8 subsystem1_StatusFlag69;
        quint16 subsystem1_PartCode70;
        quint8 subsystem1_StatusFlag70;
        quint16 subsystem1_PartCode71;
        quint8 subsystem1_StatusFlag71;
        quint16 subsystem1_PartCode72;
        quint8 subsystem1_StatusFlag72;
        quint16 subsystem1_PartCode73;
        quint8 subsystem1_StatusFlag73;
        quint16 subsystem1_PartCode74;
        quint8 subsystem1_StatusFlag74;
        quint16 subsystem1_PartCode75;
        quint8 subsystem1_StatusFlag75;
        quint16 subsystem1_PartCode76;
        quint8 subsystem1_StatusFlag76;
        quint16 subsystem1_PartCode77;
        quint8 subsystem1_StatusFlag77;
        quint16 subsystem1_PartCode78;
        quint8 subsystem1_StatusFlag78;
        quint16 subsystem1_PartCode79;
        quint8 subsystem1_StatusFlag79;
        quint16 subsystem1_PartCode80;
        quint8 subsystem1_StatusFlag80;
        quint16 subsystem1_PartCode81;
        quint8 subsystem1_StatusFlag81;

    //SubSystemStatus2

        quint8 SysCode2;
        quint8 Partnum2;

        quint16 subsystem2_PartCode0;
        quint8 subsystem2_StatusFlag0;
        quint16 subsystem2_PartCode1;
        quint8 subsystem2_StatusFlag1;
        quint16 subsystem2_PartCode2;
        quint8 subsystem2_StatusFlag2;
        quint16 subsystem2_PartCode3;
        quint8 subsystem2_StatusFlag3;
        quint16 subsystem2_PartCode4;
        quint8 subsystem2_StatusFlag4;
        quint16 subsystem2_PartCode5;
        quint8 subsystem2_StatusFlag5;

    //SubSystemStatus3
        quint8 SysCode3;
        quint8 Partnum3;

        quint16 subsystem3_PartCode0;
        quint8 subsystem3_StatusFlag0;
        quint16 subsystem3_PartCode1;
        quint8 subsystem3_StatusFlag1;

    //SubSystemStatus4
        quint8 subsystem4_SysCode4;
        quint8 subsystem4_Partnum4;
        quint16 subsystem4_PartCode0;
        quint8 subsystem4_StatusFlag0;

     //SubSystemStatus5

        quint8 subsystem5_SysCode5;
        quint8 subsystem5_Partnum5;
        quint16 subsystem5_PartCode0;
        quint8 subsystem5_StatusFlag0;
        quint16 subsystem5_PartCode1;
        quint8 subsystem5_StatusFlag1;

      //SubSystemStatus6
        quint8 subsystem6_SysCode6;
        quint8 subsystem6_Partnum6;
        quint16 subsystem6_PartCode0;
        quint8 subsystem6_StatusFlag0;

    //SubSystemStatus7
        quint8 subsystem7_SysCode7;
        quint8 subsystem7_Partnum7;
        quint16 subsystem7_PartCode0;
        quint8 subsystem7_StatusFlag0;

    //systemmobsdata

        quint8 MOBS_SysCode0;
        quint8 MOBS_Obsdatanum0;
        float MOBS_Obsdata0;
        quint8 MOBS_SysCode1;
        quint8 MOBS_Obsdatanum1;
        float MOBS_Obsdata1;
        float MOBS_Obsdata2;
        float MOBS_Obsdata3;
        float MOBS_Obsdata4;
        float MOBS_Obsdata5;
        float MOBS_Obsdata6;
        float MOBS_Obsdata7;
        float MOBS_Obsdata8;
        float MOBS_Obsdata9;
        float MOBS_Obsdata10;
        float MOBS_Obsdata11;
        float MOBS_Obsdata12;
        float MOBS_Obsdata13;
        float MOBS_Obsdata14;
        float MOBS_Obsdata15;
        float MOBS_Obsdata16;
        float MOBS_Obsdata17;
        float MOBS_Obsdata18;
        float MOBS_Obsdata19;
        float MOBS_Obsdata20;
        float MOBS_Obsdata21;
        float MOBS_Obsdata22;
        float MOBS_Obsdata23;
        float MOBS_Obsdata24;
        float MOBS_Obsdata25;
        float MOBS_Obsdata26;
        float MOBS_Obsdata27;
        float MOBS_Obsdata28;
        float MOBS_Obsdata29;
        float MOBS_Obsdata30;
        float MOBS_Obsdata31;
        float MOBS_Obsdata32;
        float MOBS_Obsdata33;
        float MOBS_Obsdata34;
        float MOBS_Obsdata35;
        float MOBS_Obsdata36;
        float MOBS_Obsdata37;
        float MOBS_Obsdata38;
        float MOBS_Obsdata39;
        float MOBS_Obsdata40;
        float MOBS_Obsdata41;
        float MOBS_Obsdata42;
        float MOBS_Obsdata43;
        float MOBS_Obsdata44;
        float MOBS_Obsdata45;
        float MOBS_Obsdata46;
        float MOBS_Obsdata47;
        float MOBS_Obsdata48;
        float MOBS_Obsdata49;
        float MOBS_Obsdata50;
        float MOBS_Obsdata51;
        float MOBS_Obsdata52;
        float MOBS_Obsdata53;
        float MOBS_Obsdata54;
        float MOBS_Obsdata55;
        float MOBS_Obsdata56;
        float MOBS_Obsdata57;
        float MOBS_Obsdata58;
        float MOBS_Obsdata59;
        float MOBS_Obsdata60;
        float MOBS_Obsdata61;
        float MOBS_Obsdata62;
        float MOBS_Obsdata63;
        float MOBS_Obsdata64;
        float MOBS_Obsdata65;
        float MOBS_Obsdata66;
        float MOBS_Obsdata67;
        float MOBS_Obsdata68;
        float MOBS_Obsdata69;
        float MOBS_Obsdata70;
        float MOBS_Obsdata71;
        float MOBS_Obsdata72;


     }__attribute__((packed)) RadarStatusCF6;



    typedef struct _RadarFFTData
    {

    //站基本参数
        char FileID[8];   //文件标识，这里为WNDFFT
        float VersionNo; //数据格式版本号
        int FileHeaderLength;   //表示文件头的长度

        char Country[16];  //国家名
        char Province[16];  //省名
        char StationNumber[16];   //区站号
        char Station[16];   //台站名
        char RadarType[16];  //雷达型号
        char Longitude[16];   //经度
        char Latitude[16];  //纬度
        char Altitude[16];  //海拔高度
        char Temp1[40];

     // 性能参数
       int Ae;  //天线增益
       float AgcWast;  //馈线损耗
       float AngleE;  //东波束与铅垂线的夹角（度）
       float AngleW;  //西波束与铅垂线的夹角（度）
       float AngleS;  //南波束与铅垂线的夹角（度）
       float AngleN;  //北波束与铅垂线的夹角（度）
       float AngleR;  //中波束与铅垂线的夹角（度）
       float AngleL;  //中波束与铅垂线的夹角（度）
       unsigned int ScanBeamN;  //扫描波束数
       unsigned int SampleP;  //采样频率
       unsigned int WaveLength;  //发射波长
       float Prp;  //脉冲重复频率
       float PusleW;  //脉冲宽度
       unsigned short HbeamW;  //水平波束宽度（度）
       unsigned short VbeamW;  //垂直波束宽度（度）
       float TranPp;  //发射峰值功率（千瓦）
       float TranAp;  //发射平均功率（千瓦）
       unsigned int StartSamplBin;  //起始采样库的距离高度
       unsigned int EndSamplBin;  //终止采样库的距离高度
       short BinLength;  //距离库长，三位整数
       short BinNum;  //距离库数，三位整数
       char Temp2[40];

        //观测参数

       unsigned short	SYear;	//观测记录开始时间（年），四位整数
       unsigned char	SMonth;	//观测记录开始时间（月），两位整数
       unsigned char	SDay;	//观测记录开始时间（日），两位整数
       unsigned char	SHour;	//观测记录开始时间（时），两位整数
       unsigned char	SMinute;	//观测记录开始时间（分），两位整数
       unsigned char	SSecond;		//观测记录开始时间（秒），两位整数

       unsigned char TimeP;  //时间来源，一位整数
       unsigned int Smillisecond;  //秒的小数位（毫秒）
       unsigned char Calibration;  //标校状态，一位
       short BeamfxChange;  //波束方向改变
       char temp4;

       unsigned short	EYear;	//观测记录结束时间（年），四位整数
       unsigned char	EMonth;	//观测记录结束时间（月），两位整数
       unsigned char	EDay;	//观测记录结束时间（日），两位整数
       unsigned char	EHour;	//观测记录结束时间（时），两位整数
       unsigned char	EMinute;	//观测记录结束时间（分），两位整数
       unsigned char	ESecond;		//观测记录结束时间（秒），两位整数
       char temp5;

       short NNtr;  //非相干积累
       short Ntr;  //相干积累
       short Fft;  //Fft点数
       short SpAver;  //谱平均数
       char BeamDir[10];  //波束顺序标志(E\S\W\N\R\L)
       char temp6[2];

       float AzimuthE;  //东波束方位角修正值（度）
       float AzimuthW;  //西波束方位角修正值（度）
       float AzimuthS;  //南波束方位角修正值（度）
       float AzimuthN;  //北波束方位角修正值（度）
       char Temp3[40];

       float DspToDpDat1[30][512];
       float DspToDpDat2[30][512];
       float DspToDpDat3[30][512];
       float DspToDpDat4[30][512];
       float DspToDpDat5[30][512];


    }__attribute__((packed)) RadarFFTData;

}



#endif
