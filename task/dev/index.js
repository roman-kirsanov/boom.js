const { writeFileSync, mkdirSync, existsSync } = require('fs')

const LIB_COMPILE_COMMANDS_PATH = (__dirname + '/../../pkg/lib/.build/debug/compile_commands.json');
const JS_COMPILE_COMMANDS_PATH = (__dirname + '/../../pkg/js/.build/debug/compile_commands.json');
const API_COMPILE_COMMANDS_PATH = (__dirname + '/../../pkg/api/.build/debug/compile_commands.json');
const CLI_COMPILE_COMMANDS_PATH = (__dirname + '/../../pkg/cli/.build/debug/compile_commands.json');

const allCompileCommands = [
    ...(existsSync(LIB_COMPILE_COMMANDS_PATH) ? require(LIB_COMPILE_COMMANDS_PATH) : []),
    ...(existsSync(JS_COMPILE_COMMANDS_PATH) ? require(JS_COMPILE_COMMANDS_PATH) : []),
    ...(existsSync(API_COMPILE_COMMANDS_PATH) ? require(API_COMPILE_COMMANDS_PATH) : []),
    ...(existsSync(CLI_COMPILE_COMMANDS_PATH) ? require(CLI_COMPILE_COMMANDS_PATH) : [])
]

mkdirSync(__dirname + '/../../.clangd', { recursive: true });
writeFileSync(__dirname + '/../../.clangd/compile_commands.json', JSON.stringify(allCompileCommands, null, 4));