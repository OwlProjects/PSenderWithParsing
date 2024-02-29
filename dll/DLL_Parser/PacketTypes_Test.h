#ifndef PACKETTYPES_TEST_H
#define PACKETTYPES_TEST_H

#include <stdint.h>

enum DataID {
  // Base commands
  ID_ReadARPList                = 0x01,
  ID_ReadUART                   = 0x02,
  ID_ReadMAC                    = 0x03,
  ID_AlarmSMK                   = 0x07,
  ID_SMKReg                     = 0x08,
  ID_WriteMaskWord              = 0x09,
  ID_Command                    = 0x0A,
  ID_ReadMem                    = 0x0B,
  ID_ChangeTrState              = 0x0C

  // Device-specific commands
  //   Will be added later...
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

typedef union {
    SMKRegErrFlag_TypeDef   ErrFlag;
    uint8_t                 ErrReg[32];
} SMKReg_TypeDef;

typedef struct {
    uint8_t commandID;
    uint8_t CommandState;
} RespFrame_ReceiveConfirmation_t;

#endif // PACKETTYPES_TEST_H
