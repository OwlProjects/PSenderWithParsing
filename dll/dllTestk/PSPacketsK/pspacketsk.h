#ifndef PSPACKETSK_H
#define PSPACKETSK_H

#include "PSPacketsK_global.h"
#include "packet.h"

#include <QStandardItem>

#define HEX_DIGITS_IN_CHAR 2

enum DataID {

  ID_ReadARPList                = 0x01,
  ID_ReadUART                   = 0x02,
  ID_ReadMAC                    = 0x03,
  ID_AlarmSMK                   = 0x07,
  ID_SMKReg                     = 0x08,
  ID_WriteMaskWord              = 0x09,
  ID_Command                    = 0x0A,
  ID_ReadMem                    = 0x0B,
  ID_ChangeTrState              = 0x0C,

  ID_KKB_ModulesData            = 0x0D,
  ID_KKB_ModulesNotRespond1     = 0x0E,     // нет ответа от модуля, в буфере свободно более 3/4 объема
  ID_KKB_ModulesNotRespond2     = 0x04,     // нет ответа от модуля, в буфере свободно менее 3/4 объема
  ID_KKB_ReadVV3T               = 0x0F,

  ID_MMData                     = 0x10,
  ID_MMDataCal                  = 0x11,
  ID_MMDataSMK                  = 0x12,

  ID_MKIOData                   = 0x18,

  ID_KON1Data                   = 0x20,
  ID_KON1Cond                   = 0x21,

  ID_KON2Data                   = 0x28,
  ID_KON2Cond                   = 0x29,

  ID_FRKData                    = 0x30,
  ID_FRKCond                    = 0x31,

  ID_MKSData                    = 0x38,
  ID_MKSDataCal                 = 0x39,

  ID_DPKData                    = 0x40,

  ID_PVIData                    = 0x48,

  ID_PKNTIogr                   = 0x50,
  ID_PKNTDAC                    = 0x51,
  ID_PKNTstab                   = 0x52,

  ID_UNKSDataOne                = 0x58,
  ID_UNKSDataCycle              = 0x59,
  ID_UNKSDataCal                = 0x5A,
  ID_UNKSDataCalKey             = 0x5B,
  ID_UNKSAlarmData              = 0x5C,
  ID_UNKSAlarmDataReq           = 0x5D,
  ID_UNKSDataInfoBank           = 0x5E,

  ID_AVKData                    = 0x60,
  ID_AVKDataCal                 = 0x61,
  ID_AVKDataSMK                 = 0x62,

  ID_ADCData                    = 0x68,
  ID_ADCDataCmd                 = 0x69,
  ID_ADCDataCal                 = 0x6A,
  ID_ADCDataSMK                 = 0x6B,

  ID_CANData                    = 0x70,
};

enum UDP_CMD_Type
{
  /* Команды общего назначения */
  /* Исходное */
  BASELINE_Set = 0x01,
  /* Чтение и сброс РгСМК */
  SELF_CHECK_REG_GetReset,
  /* Смена IP-адреса */
  NET_IPAddrSet,
  /* Чтение данных */
  BUF_DataRead,
  /* Чтение данных с произвольного адреса */
  MEM_DataRead,
  /* Запись данных по произвольному адресу */
  MEM_DataWrite,
  /* Запись 32 бит по маске */
  MEM_MaskDataWrite,
  /* Остановить */
  MODULE_Stop,
  /* Сброс регистра состояния */
  STATUS_REG_Reset,
  /* Программный запуск */
  MODULE_Start,
  /* Настройка ЭМ */
  MODULE_Init,
//  /* Настройка таймера */
//  TIMER_Init,
  /* Самоконтроль */
  SELF_CHECK_Start,
  /* Чтение MAC-адреса */
  MAC_Read,
};

typedef enum {
  CMD_COMPLETED = 1,
  CMD_STARTED,
  CMD_STOPED_WITH_ERROR,
  CMD_UNKNOWN,
  CMD_UNUSED,
  CMD_IMPOSSIBLE,
} CommandStatus_TypeDef;

// Типы
typedef struct {
  uint16_t Nom;
  uint16_t StatusReg;
  uint32_t Head;
  uint32_t Tail;
} UDPPacketHeader_TypeDef;

typedef struct {
  uint16_t length;
  uint8_t  ID;
  uint8_t  h_time;
  uint32_t l_time;
} SaveDataHeader_TypeDef;

typedef struct {
    /* 0 байт */
    uint8_t HSE_Err                 :1;     // ошибка запуска внешнего генератора
    uint8_t HSE_SA_Err              :1;     // ошибка запуска внешнего генератора второго МК
    uint8_t HSE2_Err                :1;     // ошибка запуска генератора Ethernet
    uint8_t CSEEPROM_Err            :1;     // ошибка контрольной суммы EEPROM
    uint8_t CSEEPROM_SA_Err         :1;     // ошибка контрольной суммы EEPROM второго МК
    uint8_t IntRAM_Err              :1;     // ошибка внутреннего СОЗУ
    uint8_t IntRAM_SA_Err           :1;     // ошибка внутреннего СОЗУ второго МК
    uint8_t EthPHY1_Err             :1;     // ошибка блока PHY Ethernet
    /* 1 байт */
    uint8_t EthMAC1_Err             :1;     // ошибка блока MAC Ethernet
    uint8_t Timer_Err               :1;     // ошибка самоконтроля таймера
    uint8_t ExtClkEnable_Err        :1;     // ошибка входной линии внешней синхронизации
    uint8_t ExtRAMBruteForce_Err    :1;     // отказ проверки ОЗУ методом брутфорс
    uint8_t ExtRAMAddrWrite_Err     :1;     // отказ проверки ОЗУ методом записи адреса
    uint8_t ExtRAMInvAddrWrite_Err  :1;     // отказ проверки ОЗУ методом записи инверсии адреса
    uint8_t SAReadMKIO3_Err         :1;     // отказ записи/чтения регистра CONTROL контроллера МКИО3 в режиме StandAlone
    uint8_t SAReadMKIO4_Err        	:1;     // отказ записи/чтения регистра CONTROL контроллера МКИО4 в режиме StandAlone
    /* 2 байт */
    uint8_t MKIO12Main_Err         	:2;     // ошибка связи каналов 1.о - 2.о
    uint8_t MKIO13Main_Err         	:2;     // ошибка связи каналов 1.о - 3.о
    uint8_t MKIO14Main_Err         	:2;     // ошибка связи каналов 1.о - 4.о
    uint8_t MKIO23Main_Err         	:2;     // ошибка связи каналов 2.о - 3.о
    /* 3 байт */
    uint8_t MKIO24Main_Err         	:2;     // ошибка связи каналов 2.о - 4.о
    uint8_t MKIO34Main_Err         	:2;     // ошибка связи каналов 3.о - 4.о
    uint8_t MKIO12Res_Err         	:2;     // ошибка связи каналов 1.р - 2.р
    uint8_t MKIO13Res_Err         	:2;     // ошибка связи каналов 1.р - 3.р
    /* 4 байт */
    uint8_t MKIO14Res_Err         	:2;     // ошибка связи каналов 1.р -> 4.р
    uint8_t MKIO23Res_Err         	:2;     // ошибка связи каналов 2.р -> 3.р
    uint8_t MKIO24Res_Err         	:2;     // ошибка связи каналов 2.р -> 4.р
    uint8_t MKIO34Res_Err         	:2;     // ошибка связи каналов 3.р -> 4.р
    /* 5 байт */
    uint8_t Man12Main_Err         	:2;     // ошибка связи каналов 1.о - 2.о
    uint8_t Man13Main_Err         	:2;     // ошибка связи каналов 1.о - 3.о
    uint8_t Man14Main_Err         	:2;     // ошибка связи каналов 1.о - 4.о
    uint8_t Man23Main_Err         	:2;     // ошибка связи каналов 2.о - 3.о
    /* 6 байт */
    uint8_t Man24Main_Err         	:2;     // ошибка связи каналов 2.о - 4.о
    uint8_t Man34Main_Err         	:2;     // ошибка связи каналов 3.о - 4.о
    uint8_t Man12Res_Err         	:2;     // ошибка связи каналов 1.р - 2.р
    uint8_t Man13Res_Err         	:2;     // ошибка связи каналов 1.р - 3.р
    /* 7 байт */
    uint8_t Man14Res_Err         	:2;     // ошибка связи каналов 1.р - 4.р
    uint8_t Man23Res_Err         	:2;     // ошибка связи каналов 2.р - 3.р
    uint8_t Man24Res_Err         	:2;     // ошибка связи каналов 2.р - 4.р
    uint8_t Man34Res_Err         	:2;     // ошибка связи каналов 3.р - 4.р
    /* 8 байт */
    uint8_t UnusedInterruption		:1;     // Сработало неиспользуемое прерывание
    uint8_t TimeOverflow_Err        :1;     // переполнение метки времени
    uint8_t 						:6;
    /* */
    uint8_t Reservedbytes[19];
    /* */
    uint8_t AddrMemSel_Err[4];
} SMKRegErrFlag_TypeDef;

typedef struct {
    uint8_t commandID;
    uint8_t CommandState;
} RespFrame_ReceiveConfirmation_t;

/*
 *
 */
/*
class ParseHelper {
public:
    QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, QString value );

    QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, uint32_t value, int bytesCount );

    QStandardItem * CreateFieldView( QStandardItem * item, QString name, QString value );

    QStandardItem * CreateFieldView( QStandardItem * item, QString name, uint32_t value, int bytesCount );

    QStandardItem * CreateCommandHeaderView( QStandardItem * item, uint8_t id, uint32_t length, uint8_t timeHi, uint32_t timeLo );
};
*/


/*
 * Private DLL functions
 */
QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, QString value );

QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, uint32_t value, int bytesCount );

QStandardItem * CreateFieldView( QStandardItem * item, QString name, QString value );

QStandardItem * CreateFieldView( QStandardItem * item, QString name, uint32_t value, int bytesCount );

QStandardItem * CreateCommandHeaderView( QStandardItem * item, uint8_t id, uint32_t length, uint8_t timeHi, uint32_t timeLo );



/*
 * Published DLL functions
 */
extern "C" PSPACKETSK_EXPORT QStandardItemModel * GetPacketModel(QByteArray messArray);


/*
class PSPACKETSK_EXPORT PSPacketsK
{
public:
    PSPacketsK();
};
*/

#endif // PSPACKETSK_H
