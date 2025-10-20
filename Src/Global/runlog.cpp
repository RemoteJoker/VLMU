#include "runlog.h"

#include <QDebug>

RunLog::RunLog() {
}

RunLog::~RunLog() {
}

void RunLog::SaveLog(LogType v_log_type, const std::string& v_message) {
    static std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt("logger_name", "C:/app.log");
#if m_log_flag == ON //开启日志
#ifdef QT_DEBUG
    switch (v_log_type) {
        case 0: qDebug()<<" INFO:"<<QString::fromStdString(v_message); break;
        case 1: qDebug()<<"WARN:"<<QString::fromStdString(v_message); break;
        case 2: qDebug()<<"ERROR:"<<QString::fromStdString(v_message); break;
        default: qDebug()<<"UNDEFINE:"<<QString::fromStdString(v_message); break;
    }
#else
    if (!logger) return;
    switch (v_log_type) {
        case 0: logger->info(v_message); break;
        case 1: logger->warn(v_message); break;
        case 2: logger->error(v_message); break;
        default: logger->info(v_message); break;
    }
#endif
#else //关闭日志
#endif
}
