#include <stddef.h>
#include <string.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <client/crash_report_database.h>
#include <client/settings.h>
#include <client/crashpad_client.h>
#include <client/crashpad_info.h>

#include "private_environment.hpp"

std::unique_ptr<crashpad::CrashReportDatabase> database;
crashpad::CrashpadClient client;

static bool startCrashHandler(std::string const& url, base::FilePath::StringType const& handler_path, base::FilePath::StringType const& db_path)
{
    using namespace crashpad;

    std::map<std::string, std::string> annotations;
    std::vector<std::string> arguments;
    bool rc;

    crashpad::AnnotationList::Register();

    annotations["format"] = "minidump";
    arguments.push_back("--no-rate-limit");
    //arguments.push_back("--verbose");
    //arguments.push_back("--log-to-stderr");

    base::FilePath db(db_path);
    base::FilePath handler(handler_path);

    database = crashpad::CrashReportDatabase::Initialize(db);
    if (nullptr == database)
        return false;

    crashpad::Settings* setting = database->GetSettings();
    if (nullptr == setting)
        return false;

    if (false == setting->SetUploadsEnabled(true))
        return false;

    return client.StartHandler(handler, db, db, url, annotations, arguments, false, false);
}

void Crash()
{
    memset((void*)(intptr_t)4, 123, 1);
}

bool LogMessageHandler(logging::LogSeverity severity, const char* file_poath, int line, size_t message_start, const std::string& string)
{
    std::cout << "Crashpad Log : " << string << std::endl;
    return true;
}

int main(int argc, char** argv)
{
    logging::SetLogMessageHandler(LogMessageHandler);

    std::string url(Environment::CRASH_REPORTING_WEB_URL);

#if __linux__
    base::FilePath::StringType handler_path(Environment::LINUX_CRASHPAD_HANDLER_PATH);
    base::FilePath::StringType db_path(Environment::LINUX_CRASHPAD_DB_PATH);
#else
    base::FilePath::StringType handler_path(Environment::WINDOWS_CRASHPAD_HANDLER_PATH);
    base::FilePath::StringType db_path(Environment::WINDOWS_CRASHPAD_DB_PATH);
#endif //

    std::cout << "Crashpad URL: " << url << '\n';
#if __linux__
    std::cout << "Crashpad handler: " << handler_path << '\n';
    std::cout << "Crashpad database: " << db_path << '\n';
#else
    std::wcout << L"Crashpad handler: " << handler_path << '\n';
    std::wcout << L"Crashpad database: " << db_path << '\n';
#endif //
    std::cout << (startCrashHandler(url, handler_path, db_path) ? "true" : "false") << '\n';

    while (false)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int should_crash = 1;
    if (should_crash)
        Crash();
}