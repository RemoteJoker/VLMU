#include "utils.h"

Utils::Utils()
{

}

bool Utils::InitApp(){
    //初始化应用程序-读取配置文件
    if(1){
        SetRunPath();
        QString g_exe_path = GetRunPath();
        //读取全局配置文件
        QSettings v_app_settings(g_exe_path+"/configure/app.ini", QSettings::IniFormat);
        v_app_settings.setIniCodec("UTF-8");
        GlobalSet::SetMainWindow(v_app_settings.value("mainwindow/m_mainwindow_name").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_version").toString()
                                 ,g_exe_path+v_app_settings.value("mainwindow/m_mainwindow_style").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_width").toUInt()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_height").toUInt()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu0_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu1_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu1_cmdview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu1_setview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_processview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_dumpview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_versionview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_logview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu3_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu4_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu4_aboutview").toString()
                                 );
        GlobalSet::SetSetWindow(v_app_settings.value("setwindow/m_setwindow_name").toString()
                                ,g_exe_path+v_app_settings.value("setwindow/m_setwindow_style").toString()
                                );
        GlobalSet::SetCmdWindow(v_app_settings.value("cmdwindow/m_cmdwindow_name").toString()
                                ,g_exe_path+v_app_settings.value("cmdwindow/m_cmdwindow_style").toString()
                                ,v_app_settings.value("cmdwindow/m_cmdwindow_button_1").toString()
                                ,v_app_settings.value("cmdwindow/m_cmdwindow_button_2").toString()
                                ,v_app_settings.value("cmdwindow/m_cmdwindow_button_3").toString()
                                );
        GlobalSet::SetProcessWindow(v_app_settings.value("processwindow/m_processwindow_name").toString()
                                    ,g_exe_path+v_app_settings.value("processwindow/m_processwindow_style").toString()
                                    ,v_app_settings.value("processwindow/m_processwindow_num").toUInt()
                                    ,v_app_settings.value("processwindow/m_processwindow_list").toString().split('@')
                                    ,v_app_settings.value("processwindow/m_processwindow_flush").toString()
                                    ,v_app_settings.value("processwindow/m_processwindow_hide").toString()
                                    );
        GlobalSet::SetDumpWindow(v_app_settings.value("dumpwindow/m_dumpwindow_name").toString()
                                 ,g_exe_path+v_app_settings.value("dumpwindow/m_dumpwindow_style").toString()
                                 ,v_app_settings.value("dumpwindow/m_dumpwindow_flush").toString()
                                 ,v_app_settings.value("dumpwindow/m_dumpwindow_hide").toString()
                                 );
        GlobalSet::SetVersionWindow(v_app_settings.value("versionwindow/m_versionwindow_name").toString()
                                    ,g_exe_path+v_app_settings.value("versionwindow/m_versionwindow_style").toString()
                                    ,v_app_settings.value("versionwindow/m_versionwindow_flush").toString()
                                    ,v_app_settings.value("versionwindow/m_versionwindow_hide").toString()
                                    );
        GlobalSet::SetLogWindow(v_app_settings.value("logwindow/m_logwindow_name").toString()
                                ,g_exe_path+v_app_settings.value("logwindow/m_logwindow_style").toString()
                                ,v_app_settings.value("logwindow/m_logwindow_flush").toString()
                                ,v_app_settings.value("logwindow/m_logwindow_hide").toString()
                                );
        GlobalSet::SetAboutWindow(v_app_settings.value("aboutwindow/m_aboutwindow_name").toString()
                                  ,g_exe_path+v_app_settings.value("aboutwindow/m_aboutwindow_style").toString()
                                  );
        //读取MQTT通信相关配置文件
        QSettings v_mosqsub_settings(g_exe_path+"/configure/app/mosqsub.ini", QSettings::IniFormat);
        v_app_settings.setIniCodec("UTF-8");
        GlobalData::SetProcessSub(v_mosqsub_settings.value("process/m_process_report").toString()
                                  ,v_mosqsub_settings.value("process/m_process_request").toString()
                                  );
        GlobalData::SetCoreDumpSub(v_mosqsub_settings.value("coredump/m_coredump_report").toString()
                                  ,v_mosqsub_settings.value("coredump/m_coredump_request").toString()
                                  );
        GlobalData::SetVersionSub(v_mosqsub_settings.value("version/m_version_report").toString()
                                  ,v_mosqsub_settings.value("version/m_version_request").toString()
                                  );
        GlobalData::SetLogInfoSub(v_mosqsub_settings.value("loginfo/m_loginfo_report").toString()
                                  ,v_mosqsub_settings.value("loginfo/m_loginfo_request").toString()
                                  );
        GlobalData::SetHeartSub(v_mosqsub_settings.value("heart/m_heartbeat_edge").toString()
                                  ,v_mosqsub_settings.value("heart/m_heartbeat_dashboard").toString()
                                  );

        return true;
    }else{
        return false;
    }
}

qint64 Utils::GetTimeStampS(){
    return QDateTime::currentDateTime().toSecsSinceEpoch();
}

qint64 Utils::GetTimeStampMS(){
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

QString Utils::GetRunPath(){
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\VLMU", QSettings::NativeFormat);
    // 写入各种类型的数据
    return settings.value("RunPath").toString();
}

void Utils::SetRunPath(){
    QString v_str = QCoreApplication::applicationDirPath();
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\VLMU", QSettings::NativeFormat);
    settings.setValue("RunPath", v_str);
    settings.sync();
}

QString Utils::DeCryptData(){
    return QString();
}

QString Utils::EnCryptData(){
    return QString();
}

QString Utils::GetCpuInfo() {
    QString info;

    // 1. 添加CPU型号（从注册表获取）
    info += "CPU型号: " + GetCpuModelFromRegistry() + "\n";

    // 2. 处理器架构和逻辑核心数（原代码保留）
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    info += QString("处理器架构: ");
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: info += "x64 (AMD或Intel)"; break;
        case PROCESSOR_ARCHITECTURE_ARM64: info += "ARM64"; break;
        case PROCESSOR_ARCHITECTURE_INTEL: info += "x86"; break;
        default: info += "未知";
    }
    info += QString("\n逻辑处理器数量: %1").arg(sysInfo.dwNumberOfProcessors);

    // 3. 物理核心数和NUMA节点（原代码保留）
    DWORD bufferSize = 0;
    GetLogicalProcessorInformation(nullptr, &bufferSize);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        info += "\n获取处理器核心信息失败";
    } else {
        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer =
            (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)LocalAlloc(LPTR, bufferSize);
        if (GetLogicalProcessorInformation(buffer, &bufferSize)) {
            DWORD byteOffset = 0;
            int physicalCores = 0;
            int numaNodes = 0;

            while (byteOffset < bufferSize) {
                auto infoPtr = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)(byteOffset + (PBYTE)buffer);
                if (infoPtr->Relationship == RelationProcessorCore) {
                    physicalCores++;
                } else if (infoPtr->Relationship == RelationNumaNode) {
                    numaNodes++;
                }
                byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
            }

            info += QString("\n物理核心数: %1").arg(physicalCores);
            info += QString("\nNUMA节点数: %1").arg(numaNodes);
        }
        LocalFree(buffer);
    }

    // 4. 添加CPU频率信息（通过WMI获取）
    info += "\n" + GetCpuFrequency();

    return info;
}
// 从注册表读取CPU型号（如"Intel(R) Core(TM) i7-10700K CPU @ 3.80GHz"）
QString Utils::GetCpuModelFromRegistry() {
    HKEY hKey;
    // 注册表路径：CPU信息存储位置
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),
        0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        return "获取失败（注册表访问错误）";
    }

    TCHAR cpuModel[256] = {0};
    DWORD bufferSize = sizeof(cpuModel);
    // 读取"ProcessorNameString"字段（存储CPU型号）
    result = RegQueryValueEx(hKey, _T("ProcessorNameString"), nullptr, nullptr,
                            (LPBYTE)cpuModel, &bufferSize);
    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS) {
        return "获取失败（型号字段不存在）";
    }

    return QString::fromWCharArray(cpuModel).trimmed(); // 去除首尾空格
}

// 通过WMI获取CPU基础频率和当前频率（简化版，使用单线程模型兼容）
QString Utils::GetCpuFrequency() {
    QString freqInfo;
    HRESULT hres;

    // 初始化COM（使用单线程模型兼容主线程）
    hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hres)) {
        return "频率获取失败（COM初始化错误）";
    }

    IWbemLocator* pLoc = nullptr;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
                           IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        CoUninitialize();
        return "频率获取失败（创建WMI定位器错误）";
    }

    IWbemServices* pSvc = nullptr;
    // 连接WMI服务（ROOT\CIMV2命名空间）
    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"),nullptr,nullptr,0,0,nullptr,0,&pSvc);
    if (FAILED(hres)) {
        pLoc->Release();
        CoUninitialize();
        return "频率获取失败（连接WMI服务错误）";
    }

    // 设置安全权限
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                           RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "频率获取失败（设置安全权限错误）";
    }

    // 查询CPU频率信息（Win32_Processor的MaxClockSpeed和CurrentClockSpeed）
    IEnumWbemClassObject* pEnumerator = nullptr;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT MaxClockSpeed, CurrentClockSpeed FROM Win32_Processor"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr, &pEnumerator);

    if (SUCCEEDED(hres)) {
        IWbemClassObject* pclsObj = nullptr;
        ULONG uReturn = 0;
        while (pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn) == S_OK && uReturn > 0) {
            VARIANT vtProp;

            // 获取最大频率（基础频率，单位：MHz）
            VariantInit(&vtProp);
            if (SUCCEEDED(pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, nullptr, nullptr)) && vtProp.vt == VT_I4) {
                freqInfo += QString("基础频率: %1 MHz").arg(vtProp.lVal);
            } else {
                freqInfo += "基础频率: 获取失败";
            }
            VariantClear(&vtProp);

            // 获取当前频率（实时频率，单位：MHz）
            VariantInit(&vtProp);
            if (SUCCEEDED(pclsObj->Get(L"CurrentClockSpeed", 0, &vtProp, nullptr, nullptr)) && vtProp.vt == VT_I4) {
                freqInfo += QString(" | 当前频率: %1 MHz").arg(vtProp.lVal);
            } else {
                freqInfo += " | 当前频率: 获取失败";
            }
            VariantClear(&vtProp);

            pclsObj->Release();
        }
        pEnumerator->Release();
    } else {
        freqInfo = "频率获取失败（查询WMI错误）";
    }

    // 释放资源
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return freqInfo;
}

QString Utils::GetGpuInfo() {
    QString info;

    // 1. 获取显卡基础信息（型号、厂商）
    auto gpuAdapters = GetGpuBasicInfo();
    if (gpuAdapters.empty()) {
        return "未检测到显卡设备";
    }

    // 2. 逐个输出信息
    for (size_t i = 0; i < gpuAdapters.size(); ++i) {
        const auto& adapter = gpuAdapters[i];
        QString gpuName = QString::fromWCharArray(adapter.Description).trimmed();
        QString vendor = GetVendorName(adapter.VendorId);

        // 基础信息
        info += QString("显卡 %1:\n").arg(i + 1);
        info += QString("  厂商: %1\n").arg(vendor);
        info += QString("  型号: %1\n").arg(gpuName);

        // 显存信息
        //info += QString("  显存: %1").arg(GetGpuMemory(gpuName));
    }

    return info;
}

// DXGI 获取显卡基础信息（型号、厂商ID）
std::vector<DXGI_ADAPTER_DESC> Utils::GetGpuBasicInfo() {
    std::vector<DXGI_ADAPTER_DESC> adapters;
    IDXGIFactory* pFactory = nullptr;

    // 创建 DXGI 工厂（使用兼容 Win7 的 DXGI 1.0 函数）
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
    if (FAILED(hr)) {
        return adapters;
    }

    // 枚举所有显卡
    IDXGIAdapter* pAdapter = nullptr;
    for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC desc;
        if (SUCCEEDED(pAdapter->GetDesc(&desc))) {
            adapters.push_back(desc);
        }
        pAdapter->Release();
    }

    pFactory->Release();
    return adapters;
}

// 根据厂商ID判断厂商名称（常见显卡厂商）
QString Utils::GetVendorName(DWORD vendorId) {
    switch (vendorId) {
        case 0x10DE: return "NVIDIA";       // NVIDIA
        case 0x1002: return "AMD";          // AMD
        case 0x8086: return "Intel";        // Intel
        case 0x13B5: return "ARM";          // ARM
        case 0x5143: return "Qualcomm";     // 高通
        default: return QString("未知（ID: 0x%1）").arg(vendorId, 4, 16, QChar('0')).toUpper();
    }
}

// WMI 获取显存大小（简化版）
QString Utils::GetGpuMemory(const QString& gpuName) {
    // 初始化 COM
    HRESULT hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hres)) {
        return "获取失败";
    }

    IWbemLocator* pLoc = nullptr;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
                           IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        CoUninitialize();
        return "获取失败";
    }

    IWbemServices* pSvc = nullptr;
    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, 0,
                              0, nullptr, 0, &pSvc);
    if (FAILED(hres)) {
        pLoc->Release();
        CoUninitialize();
        return "获取失败";
    }

    // 设置安全权限
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                           RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
                           nullptr, EOAC_NONE);
    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "获取失败";
    }

    // 查询显存大小
    QString wql = QString("SELECT AdapterRAM FROM Win32_VideoController WHERE Name LIKE '%%1%'")
                     .arg(gpuName);
    IEnumWbemClassObject* pEnumerator = nullptr;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t(wql.toStdWString().c_str()),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr, &pEnumerator);

    QString memoryInfo = "获取失败";
    if (SUCCEEDED(hres)) {
        IWbemClassObject* pclsObj = nullptr;
        ULONG uReturn = 0;
        if (pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn) == S_OK && uReturn > 0) {
            VARIANT vtProp;
            VariantInit(&vtProp);
            if (SUCCEEDED(pclsObj->Get(L"AdapterRAM", 0, &vtProp, nullptr, nullptr)) && vtProp.vt == VT_UI8) {
                // 转换为 GB 或 MB
                ULONGLONG ramBytes = vtProp.ullVal;
                if (ramBytes >= 1024 * 1024 * 1024) {
                    memoryInfo = QString("%1 GB").arg(ramBytes / (1024.0 * 1024 * 1024), 0, 'f', 1);
                } else {
                    memoryInfo = QString("%1 MB").arg(ramBytes / (1024.0 * 1024), 0, 'f', 0);
                }
            }
            VariantClear(&vtProp);
            pclsObj->Release();
        }
        pEnumerator->Release();
    }

    // 释放资源
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return memoryInfo;
}

QString Utils::GetMemoryInfo() {
    QString info = "内存信息:\n";

    // 使用 GlobalMemoryStatusEx 获取核心内存信息（简单可靠）
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex)) {
        // 物理内存
        info += QString("  总量: %1\n").arg(FormatSize(statex.ullTotalPhys));
        info += QString("  可用: %1\n").arg(FormatSize(statex.ullAvailPhys));
        info += QString("  已用: %1\n").arg(FormatSize(statex.ullTotalPhys - statex.ullAvailPhys));
        info += QString("  使用率: %1%\n").arg(statex.dwMemoryLoad);

        // 虚拟内存（页面文件）
        info += QString("\n虚拟内存:\n");
        info += QString("  总量: %1\n").arg(FormatSize(statex.ullTotalPageFile));
        info += QString("  可用: %1\n").arg(FormatSize(statex.ullAvailPageFile));
    } else {
        info += "  内存信息获取失败";
    }

    return info;
}

// 辅助函数：将字节数转换为易读格式（B/KB/MB/GB）
QString Utils::FormatSize(ULONGLONG bytes) {
    if (bytes < 1024) {
        return QString("%1 B").arg(bytes);
    } else if (bytes < 1024 * 1024) {
        return QString("%1 KB").arg(bytes / 1024.0, 0, 'f', 1);
    } else if (bytes < 1024 * 1024 * 1024) {
        return QString("%1 MB").arg(bytes / (1024.0 * 1024), 0, 'f', 1);
    } else {
        return QString("%1 GB").arg(bytes / (1024.0 * 1024 * 1024), 0, 'f', 2);
    }
}

QString Utils::GetDiskInfo(){
    QString v_disk_info;
    DWORD drives = GetLogicalDrives();
    int driveCount = 0;
    ULONGLONG totalSize = 0;
    ULONGLONG totalFree = 0;

    for (char drive = 'A'; drive <= 'Z'; drive++) {
        if (drives & 1) {
            QString rootPath = QString("%1:\\").arg(drive);
            ULARGE_INTEGER freeBytes, totalBytes, totalFreeBytes;

            if (GetDiskFreeSpaceExW(rootPath.toStdWString().c_str(),
                                  &freeBytes, &totalBytes, &totalFreeBytes)) {
                double totalGB = totalBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                double freeGB = freeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                double usedGB = totalGB - freeGB;
                double usagePercent = (usedGB / totalGB) * 100.0;

                if (driveCount > 0) {
                    v_disk_info += " \n ";
                }

                v_disk_info += QString("%1盘: %2/%3 GB (%4%)")
                               .arg(drive)
                               .arg(QString::number(usedGB, 'f', 1))
                               .arg(QString::number(totalGB, 'f', 1))
                               .arg(QString::number(usagePercent, 'f', 1));

                driveCount++;
                totalSize += totalBytes.QuadPart;
                totalFree += freeBytes.QuadPart;
            }
        }
        drives >>= 1;
    }

    if (driveCount > 0) {
        double totalSizeGB = totalSize / (1024.0 * 1024.0 * 1024.0);
        double totalFreeGB = totalFree / (1024.0 * 1024.0 * 1024.0);
        double totalUsedGB = totalSizeGB - totalFreeGB;
        double totalUsagePercent = (totalUsedGB / totalSizeGB) * 100.0;

        QString summary = QString("\n总计: %1/%2 GB (%3%)")
                             .arg(QString::number(totalUsedGB, 'f', 1))
                             .arg(QString::number(totalSizeGB, 'f', 1))
                             .arg(QString::number(totalUsagePercent, 'f', 1));

        v_disk_info = "硬盘信息:\n" + v_disk_info + summary;
    } else {
        v_disk_info = "硬盘信息获取失败";
    }

    return v_disk_info;
}

bool Utils::CheckDirExist(QString str){
    //
    QDir dir(str);
    if (!dir.exists()) {
        return false;
    }
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    return !list.isEmpty();
}

bool Utils::CheckFileExist(QString str){
    QDir dir(str);
    if (!dir.exists()) {
        return false;
    }

    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    return !list.isEmpty();
}

bool Utils::CheckMySqlSrv(){
#ifdef __linux__
    // Linux系统：检查mysqld进程
    QProcess process;
    process.start("pgrep", QStringList() << "mysqld");
    process.waitForFinished();
    return (process.exitCode() == 0);

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    // Windows系统：检查MySQL服务状态
    QProcess process;
    process.start("sc", QStringList() << "query" << "MySQL");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    return output.contains("RUNNING");

#else
    return false;
#endif
}

bool Utils::CheckFileIntegrity(){
    return false;
}
