#include "syncpackage.h"
#include <QDataStream>
#include <QDebug>

SyncPackage::SyncPackage()
{
    type = TypeSyncPackage::t_voidSync;
    firstByte = sourceBytes = 0;
}

bool SyncPackage::isValid() const{

    switch (type) {
    case TypeSyncPackage::t_voidSync:
        return false;

    case TypeSyncPackage::t_Header:
        return firstByte >= 0;

    default:
        return firstByte >= 0 && sourceBytes != 0;
    }

}

void SyncPackage::clear(){
    type = TypeSyncPackage::t_voidSync;
    firstByte = 0;
    sourceBytes = 0;
}

QByteArray SyncPackage::parseTo(){
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    temp.clear();
    if(isValid()){
        stream <<  static_cast<unsigned char>(type);

        switch (type) {

        case TypeSyncPackage::t_End:
            stream << firstByte;
            stream << sourceBytes;
            stream << nativeTime;

            break;

        default:
            stream << firstByte;
            stream << sourceBytes;

        }
    } else {
        qDebug() << "package synk is not valid!!!";
    }
    return temp;
}

bool SyncPackage::parseFrom(QByteArray &array){
    type = TypeSyncPackage::t_voidSync;
    QDataStream stream(&array, QIODevice::ReadOnly);

    unsigned char temp_type;
    stream >> temp_type;
    type = static_cast<TypeSyncPackage> (temp_type);

    switch (type) {

    case TypeSyncPackage::t_End:
        stream >> firstByte;
        stream >> sourceBytes;
        stream >> nativeTime;

        break;

    default:
        stream >> firstByte;
        stream >> sourceBytes;

    }

    return isValid();
}

TypeSyncPackage SyncPackage::getType()const {
    return type;
}

char SyncPackage::getIndex()const {
    return firstByte;
}

const milliseconds& SyncPackage::getNative()const {
    return nativeTime;
}

const milliseconds& SyncPackage::getTime()const {
    return sourceBytes;
}

const milliseconds& SyncPackage::getPing()const {
    return sourceBytes;
}

char SyncPackage::getPrecision()const {
    return firstByte;
}

bool SyncPackage::isSended()const {
    return type == TypeSyncPackage::t_Responce && firstByte;
}

SyncPackage::~SyncPackage(){}
