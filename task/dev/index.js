const { writeFileSync, mkdirSync, existsSync } = require('fs')

const LIB_COMPILE_COMMANDS_PATH = (__dirname + '/../../pkg/lib/.build/Debug/compile_commands.json');
const CLI_COMPILE_COMMANDS_PATH = (__dirname + '/../../pkg/cli/.build/Debug/compile_commands.json');

const allCompileCommands = [
    ...(existsSync(LIB_COMPILE_COMMANDS_PATH) ? require(LIB_COMPILE_COMMANDS_PATH) : []),
    ...(existsSync(CLI_COMPILE_COMMANDS_PATH) ? require(CLI_COMPILE_COMMANDS_PATH) : [])
]

mkdirSync(__dirname + '/../../.clangd', { recursive: true });
writeFileSync(__dirname + '/../../.clangd/compile_commands.json', JSON.stringify(allCompileCommands, null, 4));