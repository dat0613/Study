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

    base::FilePath db(db_path);
    base::FilePath handler(handler_path);

    database = crashpad::CrashReportDatabase::Initialize(db);

    std::cerr << __LINE__ << '\n';

    if (database == nullptr || database->GetSettings() == NULL)
        return false;

    std::cerr << __LINE__ << '\n';

    //database->GetSettings()->SetUploadsEnabled(true);

    return client.StartHandler(handler, db, db, url, annotations, arguments, false, false);
}

void Crash()
{
    memset((void*)(intptr_t)4, 123, 1);
}

int main(int argc, char** argv)
{
    std::string url("");

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

    int should_crash = 1;
    if (should_crash)
        Crash();
}