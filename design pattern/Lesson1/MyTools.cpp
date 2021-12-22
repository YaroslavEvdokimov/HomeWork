
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;

namespace MyTools {

    ofstream logOut;

    //=============================================================================================

    void ClrScr()
    {
        system("cls");
    }

    void __fastcall GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }

    uint16_t GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    //=============================================================================================

    void __fastcall  LogSingleton::OpenLogFile(const string& FN)
    {
        logOut.open(FN, ios_base::out);
    }

    void  LogSingleton::CloseLogFile()
    {
        if (logOut.is_open())
        {
            logOut.close();
        }
    }

    string GetCurDateTime()
    {
        auto cur = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return string(buf);
    }

    void __fastcall  LogSingleton::WriteToLog(const string& str)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void __fastcall  LogSingleton::WriteToLog(const string& str, int n)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void __fastcall  LogSingleton::WriteToLog(const string& str, double d)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }

    //=============================================================================================


} // namespace MyTools


class ILog {
    public:
        virtual void __fastcall OpenLogFile(const std::string& FN) = 0;
        virtual void CloseLogFile();
        virtual void __fastcall WriteToLog(const std::string& str) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, int n) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, double d) = 0;
    };

class Log: public ILog {
    public:
        static Log& getInstance(){}
        void __fastcall OpenLogFile(const std::string& FN);
        void CloseLogFile();
        void __fastcall WriteToLog(const std::string& str);
        void __fastcall WriteToLog(const std::string& str, int n);
        void __fastcall WriteToLog(const std::string& str, double d)
    };
    
    class LogSingletonProxy: public ILog {
    public:

        static LogSingletonProxy& getInstance()
        {
            static LogSingletonProxy theInstance;
            return theInstance;
        }
        void __fastcall OpenLogFile(const std::string& FN);
        void CloseLogFile();
        void __fastcall WriteToLog(const std::string& str);
        void __fastcall WriteToLog(const std::string& str, int n);
        void __fastcall WriteToLog(const std::string& str, double d);

    private:
        LogSingletonProxy() { }
        LogSingletonProxy(const LogSingleton& root) = delete;
        LogSingletonProxy& operator=(const LogSingleton&) = delete;
	    ~LogSingletonProxy() { }
    };












#include <iostream>

class ILog {
    public:
        virtual void  OpenLogFile(const std::string& FN) = 0;
        virtual void CloseLogFile();
        virtual void  WriteToLog(const std::string& str) = 0;
        virtual void  WriteToLog(const std::string& str, int n) = 0;
        virtual void  WriteToLog(const std::string& str, double d) = 0;
    };

class Log: public ILog {
    public:
        static Log& getInstance();
        void  OpenLogFile(const std::string& FN) override;
        void CloseLogFile() override {std::cout << "Test" << std::endl;};
        void  WriteToLog(const std::string& str) override;
        void  WriteToLog(const std::string& str, int n) override;
        void  WriteToLog(const std::string& str, double d) override;
    };
    
    class LogSingletonProxy: public ILog {
    public:
        static Log* getInstance()
        {
            static Log *theInstance;
            return theInstance;
        }
        void OpenLogFile(const std::string& FN);
        void CloseLogFile() override {std::cout << "Test" << std::endl;};
        void WriteToLog(const std::string& str);
        void WriteToLog(const std::string& str, int n);
        void WriteToLog(const std::string& str, double d);

    private:
        Log *theInstance;
        LogSingletonProxy() { }
        LogSingletonProxy(const Log& root) = delete;
        LogSingletonProxy& operator=(const Log&) = delete;
	    ~LogSingletonProxy() {}
    };


int main(){ 
    LogSingletonProxy::getInstance()->CloseLogFile();
    
    std::cout<<"Hello World";

    return 0;
}

