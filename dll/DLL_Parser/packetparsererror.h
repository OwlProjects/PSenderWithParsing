#ifndef PACKETPARSERERROR_H
#define PACKETPARSERERROR_H

#include <QString>

/*
 * Class of Packet Parser's error
 */
class PacketParserError
{

/*
 * Public constant data
 */
public:
    enum ErrorCodes {
        NO_ERRORS,
        LENGTH_OF_FRAME_IS_ZERO
    };
    static const int NO_FRAME_NUMBER = -1;


/*
 * Private fields
 */
private:
    int errorCode;
    int frameNumber;

/*
 * Public c-tors/d-tors
 */
public:
    explicit PacketParserError(int parErrorCode = NO_ERRORS, int parFrameNumber = NO_FRAME_NUMBER);

/*
 * Public methods
 */
public:
    int getErrorcode();
    int getFrameNumber();
    QString toString();
};

#endif // PACKETPARSERERROR_H
