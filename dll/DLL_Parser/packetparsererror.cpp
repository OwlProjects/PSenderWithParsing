#include "packetparsererror.h"

PacketParserError::PacketParserError(int parErrorCode, int parFrameNumber)
{
    errorCode = parErrorCode;
    frameNumber = parFrameNumber;
}

int PacketParserError::getErrorcode()
{
    return errorCode;
}

int PacketParserError::getFrameNumber()
{
    return frameNumber;
}

QString PacketParserError::toString()
{
    QString errorString;
    switch ( errorCode ) {
    case NO_ERRORS:
        errorString = "Parsing is succeed";
        break;
    case LENGTH_OF_FRAME_IS_ZERO:
        errorString = "Error in frame with index " + QString::number(frameNumber);
        break;
    default:
        errorString = "Unknown error";
        break;
    }
    return errorString;
}
