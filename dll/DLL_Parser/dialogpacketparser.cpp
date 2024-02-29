#include "dialogpacketparser.h"
#include "ui_dialogpacketparser.h"

#include "PacketTypes_Retarget.h"


#define HEX_DIGITS_IN_CHAR 2

static QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, QString value = QString() ) {
    QList<QStandardItem *> brRow;

    QStandardItem * pItemFieldName = new QStandardItem(name);
    brRow.append(pItemFieldName);
    brRow.append(new QStandardItem(value));
    model->appendRow(brRow);
    return pItemFieldName;
}

static QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, uint32_t value, int bytesCount ) {
    int const baseHex = 16;
    QChar const hexFiller = '0';
    QList<QStandardItem *> brRow;
    QString brValue;

    brValue = QString("%1").arg(value, bytesCount * HEX_DIGITS_IN_CHAR, baseHex, hexFiller).toUpper();
    QStandardItem * pItemFieldName = new QStandardItem(name);
    brRow.append(pItemFieldName);
    brRow.append(new QStandardItem("0x" + brValue));
    model->appendRow(brRow);
    return pItemFieldName;
}

static QStandardItem * CreateFieldView( QStandardItem * item, QString name, QString value = QString() ) {
    QList<QStandardItem *> brRow;
    QStandardItem * pItemFieldName = new QStandardItem(name);
    brRow.append(pItemFieldName);
    brRow.append(new QStandardItem(value));
    item->appendRow(brRow);
    return pItemFieldName;
}

static QStandardItem * CreateFieldView( QStandardItem * item, QString name, uint32_t value, int bytesCount ) {
    int const baseHex = 16;
    QChar const hexFiller = '0';
    QList<QStandardItem *> brRow;
    QString brValue;

    brValue = QString("%1").arg(value, bytesCount * HEX_DIGITS_IN_CHAR, baseHex, hexFiller).toUpper();
    QStandardItem * pItemFieldName = new QStandardItem(name);
    brRow.append(pItemFieldName);
    brRow.append(new QStandardItem("0x"+ brValue));
    item->appendRow(brRow);
    return pItemFieldName;
}

static QStandardItem * CreateCommandHeaderView( QStandardItem * item, uint8_t id, uint32_t length, uint8_t timeHi, uint32_t timeLo ) {
    QString brValue;

    int const bytesCountLength = 2;
    switch (id) {
    case ID_Command: {
        brValue.sprintf("0x%02X (Confirmation)", ID_Command);
        break;
    }
    case ID_SMKReg: {
        brValue.sprintf("0x%02X (Read SMK Reg)", ID_SMKReg);
        break;
    }
    default: {
        brValue.sprintf("0x%02X (Unknown)", id);
        break;
    }
    }
    QStandardItem * pItemCommand = CreateFieldView(item, "ID", brValue);
    CreateFieldView(pItemCommand, "Length", length, bytesCountLength);
    brValue.sprintf("0x%02X%08X", timeHi, timeLo);
    CreateFieldView(pItemCommand, "Time stamp", brValue);
    return pItemCommand;
}

QStandardItemModel * DialogPacketParser::GetPacketModel(QWidget *parent, QByteArray packetArray) {

    int packN = 0;

    //  Get PacketArray data
    char * pFieldPtr = packetArray.data();
    char * const pPackEndPtr = pFieldPtr + packetArray.count();
    UDPPacketHeader_TypeDef * pPacketHeader = reinterpret_cast<UDPPacketHeader_TypeDef *>(pFieldPtr);

    QStandardItemModel * const model = new QStandardItemModel(parent);
    model->setHorizontalHeaderItem(0, new QStandardItem("Field"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Value"));

    CreateFieldView( model, "Packet ID", pPacketHeader->Nom, sizeof (pPacketHeader->Nom) );
    CreateFieldView( model, "Status", pPacketHeader->StatusReg, sizeof (pPacketHeader->StatusReg) );
    CreateFieldView( model, "Head", pPacketHeader->Head, sizeof (pPacketHeader->Head) );
    CreateFieldView( model, "Tail", pPacketHeader->Tail, sizeof (pPacketHeader->Tail) );

    pFieldPtr += sizeof (UDPPacketHeader_TypeDef);
    QStandardItem * responseFrames = CreateFieldView( model, "Response frames" );
    for ( ; pFieldPtr < pPackEndPtr; packN++ ) {
        SaveDataHeader_TypeDef * pFrameHeader = reinterpret_cast<SaveDataHeader_TypeDef *>( pFieldPtr );
        uint frameLength = pFrameHeader->length;
        if (frameLength == 0) {
            error = new PacketParserError(PacketParserError::LENGTH_OF_FRAME_IS_ZERO);
            CreateFieldView(responseFrames, "Length error of frame with index", QString::number(packN));
            return model;
        }
        pFieldPtr += sizeof (SaveDataHeader_TypeDef);
        switch (pFrameHeader->ID) {
        case ID_Command: {
            QStandardItem * rF_RC = CreateCommandHeaderView(responseFrames, ID_Command, frameLength, pFrameHeader->h_time, pFrameHeader->l_time);
            RespFrame_ReceiveConfirmation_t * pData = reinterpret_cast<RespFrame_ReceiveConfirmation_t *>( pFieldPtr );
            CreateFieldView(rF_RC, "Command ID", pData->commandID, sizeof (pData->commandID));
            CreateFieldView(rF_RC, "Command state", pData->CommandState, sizeof (pData->CommandState));
            pFieldPtr += sizeof (RespFrame_ReceiveConfirmation_t);
            break;
        }
        case ID_SMKReg: {
            QStandardItem * rF_SCD = CreateCommandHeaderView(responseFrames, ID_SMKReg, frameLength, pFrameHeader->h_time, pFrameHeader->l_time);
            SMKRegErrFlag_TypeDef * pData = reinterpret_cast<SMKRegErrFlag_TypeDef *>(pFieldPtr);
            if (pFieldPtr[0] != 0) {
                if (pData->CSEEPROM_Err != 0) CreateFieldView(rF_SCD, "CSEEPROM_Err");
                if (pData->CSEEPROM_SA_Err != 0) rF_SCD->appendRow(new QStandardItem("CSEEPROM_SA_Err"));
            }
            if (pFieldPtr[2] != 0) {
                if (pData->MKIO12Main_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO12Main_Err"));
                if (pData->MKIO13Main_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO13Main_Err"));
                if (pData->MKIO14Main_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO14Main_Err"));
                if (pData->MKIO23Main_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO23Main_Err"));
            }
            if (pFieldPtr[3] != 0) {
                if (pData->MKIO24Main_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO24Main_Err"));
                if (pData->MKIO34Main_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO34Main_Err"));
                if (pData->MKIO12Res_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO12Res_Err"));
                if (pData->MKIO13Res_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO13Res_Err"));
            }
            if (pFieldPtr[4] != 0) {
                if (pData->MKIO14Res_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO14Res_Err"));
                if (pData->MKIO23Res_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO23Res_Err"));
                if (pData->MKIO24Res_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO24Res_Err"));
                if (pData->MKIO34Res_Err != 0) rF_SCD->appendRow(new QStandardItem("MKIO34Res_Err"));
            }
            if (pFieldPtr[5] != 0) {
                if (pData->Man12Main_Err != 0) rF_SCD->appendRow(new QStandardItem("Man12Main_Err"));
                if (pData->Man13Main_Err != 0) rF_SCD->appendRow(new QStandardItem("Man13Main_Err"));
                if (pData->Man14Main_Err != 0) rF_SCD->appendRow(new QStandardItem("Man14Main_Err"));
                if (pData->Man23Main_Err != 0) rF_SCD->appendRow(new QStandardItem("Man23Main_Err"));
            }
            if (pFieldPtr[6] != 0) {
                if (pData->Man24Main_Err != 0) rF_SCD->appendRow(new QStandardItem("Man24Main_Err"));
                if (pData->Man34Main_Err != 0) rF_SCD->appendRow(new QStandardItem("Man34Main_Err"));
                if (pData->Man12Res_Err != 0) rF_SCD->appendRow(new QStandardItem("Man12Res_Err"));
                if (pData->Man13Res_Err != 0) rF_SCD->appendRow(new QStandardItem("Man13Res_Err"));
            }
            if (pFieldPtr[7] != 0) {
                if (pData->Man14Res_Err != 0) rF_SCD->appendRow(new QStandardItem("Man14Res_Err"));
                if (pData->Man23Res_Err != 0) rF_SCD->appendRow(new QStandardItem("Man23Res_Err"));
                if (pData->Man24Res_Err != 0) rF_SCD->appendRow(new QStandardItem("Man24Res_Err"));
                if (pData->Man34Res_Err != 0) rF_SCD->appendRow(new QStandardItem("Man34Res_Err"));
            }
            pFieldPtr += sizeof (SMKRegErrFlag_TypeDef);
            break;
        }
        default: {
            QString brValue; // строка ветви
            QStandardItem * rF_Unk = CreateCommandHeaderView(responseFrames, pFrameHeader->ID, frameLength, pFrameHeader->h_time, pFrameHeader->l_time);
            char * pData = pFieldPtr;
            uint pDataIdx;
            QString tempString;
            uint dataLength = frameLength - sizeof (SaveDataHeader_TypeDef);
            pFieldPtr += dataLength;
            dataLength--;
            brValue.sprintf("Data [%d]: ", dataLength + 1);
            for (pDataIdx = 0; pDataIdx < dataLength; pDataIdx++) {
                tempString.sprintf("%02X, ", pData[pDataIdx]);
                brValue += tempString;
            }
            tempString.sprintf("%02X", pData[pDataIdx]);
            brValue += tempString;
            rF_Unk->appendRow(new QStandardItem(brValue));
        }
        }
    }
    error = new PacketParserError(PacketParserError::NO_ERRORS);
    return model;
}

DialogPacketParser::DialogPacketParser(QWidget *parent, QByteArray packetArray) :
    QDialog(parent),
    ui(new Ui::DialogPacketParser)
{
    ui->setupUi(this);

    QStandardItemModel * model = GetPacketModel(parent ,packetArray);
    ui->treeViewPacketFields->setModel( model );
    ui->treeViewPacketFields->expandAll();
    for (int column = 0; column < model->columnCount(); ++column)
        ui->treeViewPacketFields->resizeColumnToContents(column);
    ui->lineEditPacketHexView->setText(packetArray.toHex(' ').toUpper());
    ui->lineEditPacketHexView->setCursorPosition(0);
    ui->lineEditParsingResult->setText(error->toString());
    ui->lineEditParsingResult->setCursorPosition(0);
}


DialogPacketParser::~DialogPacketParser()
{
    delete ui;
}

void DialogPacketParser::on_pushButtonOK_clicked()
{
    close();
}

QDialog *GetPacketParserWindow(QWidget *parent, QByteArray packetArray)
{
   return new DialogPacketParser( parent, packetArray );
}
