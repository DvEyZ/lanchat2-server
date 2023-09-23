project('lanchat2-server', 'cpp',
    version: '0.1',
    default_options: ['warning_level=3', 'cpp_std=c++20']
)

asio = dependency('asio')
json = dependency('nlohmann_json')

exe = executable(
    'lanchat2-server', 
    'src/lanchat2_server.cxx',
    'src/Connection.cxx',
    'src/Parser.cxx',
    'src/Config.cxx',
    'src/loggers/ConsoleLogger.cxx',
    install: true,
    dependencies: [
        asio,
        json,
    ],
    cpp_args: [
        '-Wno-reorder'
    ]
)