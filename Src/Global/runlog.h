#ifndef RUNLOG_H
#define RUNLOG_H

#include <spdlog/spdlog.h>

#ifdef _WIN32
#include <spdlog/sinks/basic_file_sink.h>
#elif __linux__
#include <spdlog/sinks/basic_file_sink.h>
#endif

#define Log(v_log_flag,v_log_text) RunLog::SaveLog(v_log_flag,v_log_text);

enum LogType{
    L_INFO,
    L_WARN,
    L_ERROR,
    L_UNDEFINE,
};

//全局日志类
class RunLog
{
private:
    RunLog();

public:
    static void SaveLog(LogType v_log_type,const std::string& v_message);

private:
    RunLog(const RunLog&) = delete;
    RunLog& operator=(const RunLog&) = delete;
    ~RunLog();

private:
};

#endif // RUNLOG_H
