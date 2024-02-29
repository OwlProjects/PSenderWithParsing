#ifndef INTERFACEDLL_H
#define INTERFACEDLL_H

#include <QWidget>


#define DLL_FUNCNAME_PACKETPARSER "GetPacketParserWindow"

#define CLASS_WND_PACKETPARSER QDialog

typedef CLASS_WND_PACKETPARSER *(* WindowPacketParser_t)(QWidget * parent, QByteArray messageArray);

#endif // INTERFACEDLL_H
