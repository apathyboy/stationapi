

#define ELPP_DISABLE_DEFAULT_CRASH_HANDLING 1
#define ELPP_DEFAULT_LOG_FILE "logs/swgchat.log"

#include "easylogging++.h"

#include "StationChatApp.hpp"

#include <boost/program_options.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

INITIALIZE_EASYLOGGINGPP

StationChatConfig BuildConfiguration(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    auto config = BuildConfiguration(argc, argv);

    el::Loggers::setDefaultConfigurations(config.loggerConfig, true);
    START_EASYLOGGINGPP(argc, argv);

    StationChatApp app{config};

    while (app.IsRunning()) {
        app.Tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}

StationChatConfig BuildConfiguration(int argc, char* argv[]) {
    namespace po = boost::program_options;
    StationChatConfig config;
    std::string configFile;

    // Declare a group of options that will be 
    // allowed only on command line
    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produces help message")
        ("config,c", po::value<std::string>(&configFile)->default_value("swgchat.cfg"),
            "sets path to the configuration file")
        ("logger_config", po::value<std::string>(&config.loggerConfig)->default_value("logger.cfg"),
            "setspath to the logger configuration file")
        ;

    po::options_description options("Configuration");
    options.add_options()
        ("gateway_address", po::value<std::string>(&config.gatewayAddress)->default_value("127.0.0.1"),
            "address for gateway connections")
        ("gateway_port", po::value<uint16_t>(&config.gatewayPort)->default_value(5001),
            "port for gateway connections")
        ("registrar_address", po::value<std::string>(&config.registrarAddress)->default_value("127.0.0.1"),
            "address for registrar connections")
        ("registrar_port", po::value<uint16_t>(&config.registrarPort)->default_value(5000),
            "port for registrar connections")
        ("database_path", po::value<std::string>(&config.chatDatabasePath)->default_value("chat.db"),
            "path to the sqlite3 database file")
        ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(options);

    po::options_description config_file_options;
    config_file_options.add(options);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(cmdline_options).allow_unregistered().run(), vm);
    po::notify(vm);

    std::ifstream ifs(configFile.c_str());
    if (!ifs) {
        throw std::runtime_error("Cannot open configuration file: " + configFile);
    }

    po::store(po::parse_config_file(ifs, config_file_options), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << cmdline_options << "\n";
        exit(EXIT_SUCCESS);
    }

    return config;
}
