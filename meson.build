project('lanchat2-server', 'cpp',
    version: '0.0.0',
    default_options: ['warning_level=3', 'cpp_std=c++20']
)

asio = dependency('asio')
json = dependency('nlohmann_json')

exe = executable(
    'lanchat2-server', 
    'src/utils/uuid.cxx',
    'src/lanchat2_server.cxx',
    'src/Connection.cxx',
    'src/Parser.cxx',
    'src/Config.cxx',
    'src/loggers/ConsoleLogger.cxx',
    'src/chat/Chat.cxx',
    'src/chat/ChatHookComposite.cxx',
    'src/chat/request/ChatHandle.cxx',
    'src/chat/request/request_factory.cxx',
    'src/chat/request/visitors/RequestRoutingVisitor.cxx',
    'src/chat/systems/msg/CoreMsgHook.cxx',
    install: true,
    dependencies: [
        asio,
        json,
    ],
    cpp_args: [
        '-Wno-reorder'
    ]
)