#pragma once
#include <iostream>
#include <stdint.h>
#include <string>
#include <chrono>
#include <vector>
#include "Time.h"

namespace MyTools {

    // Палитра цветов от 0 до 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

	//=============================================================================================

    class ILog {
    public:
        virtual void  OpenLogFile(const std::string& FN) = 0;
        virtual void  CloseLogFile() = 0;
        virtual void  WriteToLog(const std::string& str) = 0;
        virtual void  WriteToLog(const std::string& str, int n) = 0;
        virtual void  WriteToLog(const std::string& str, double d) = 0;
    };

    class RealLog : public ILog {
    public:
        void  OpenLogFile(const std::string& FN) override;
        void  CloseLogFile() override;
        void  WriteToLog(const std::string& str)override;
        void  WriteToLog(const std::string& str, int n) override;
        void  WriteToLog(const std::string& str, double d) override;
    };

    class LogSingletonProxy : public ILog {
    public:
        static RealLog* getInstance() {      
            static RealLog* real_log = new RealLog;
            return real_log;
        }

        void OpenLogFile(const std::string& FN);
        void CloseLogFile();
        void WriteToLog(const std::string& str);
        void WriteToLog(const std::string& str, int n);
        void WriteToLog(const std::string& str, double d);

    private:
        std::vector<double> timer;
       
        LogSingletonProxy() {}
        LogSingletonProxy(const RealLog& root) = delete;
        LogSingletonProxy& operator=(const RealLog&) = delete;
        LogSingletonProxy& operator=(RealLog&&) = delete;
        ~LogSingletonProxy() {}
    };


	//=============================================================================================

};