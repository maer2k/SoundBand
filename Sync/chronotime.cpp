#include "chronotime.h"
#include <QDateTime>
#include <QDebug>

/*
 * information about chrono
 * https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back
 */
milliseconds ChronoTime::stdTime() {
    auto tim = std::chrono::system_clock::now();
    auto mc = std::chrono::time_point_cast<std::chrono::milliseconds>(tim);
    auto epoh = mc.time_since_epoch();
#ifdef QT_DEBUG
    qDebug() << epoh.count();
#endif
    return epoh.count();
}

milliseconds ChronoTime::qtTime() {
    return  QDateTime::currentMSecsSinceEpoch();
}

ChronoTime::ChronoTime()
{

}

milliseconds ChronoTime::now(milliseconds calibration){
    return  qtTime() + calibration;
}

Clock ChronoTime::from(const milliseconds& mc){
    std::chrono::milliseconds dur(mc);
    return Clock(dur);
}

milliseconds ChronoTime::abs(milliseconds number){
    return (number << 1) >> 1;
}
