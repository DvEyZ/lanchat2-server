project('lanchat2-server', 'cpp',
    version: '0.1',
    default_options: ['warning_level=3', 'cpp_std=c++20']
)

asio = dependency('asio')
json = dependency('nlohmann_json')

exe = executable(
    'lanchat2-server', 
    'src/lanchat2_server.cxx',
    'src/Connection.cpp',
    'src/Parser.cpp',
    'src/Config.cpp',
    'src/loggers/ConsoleLogger.cpp',
    install: true,
    dependencies: [
        asio,
        json,
    ]
)