const { execSync } = require('child_process')
const { writeFileSync, mkdirSync } = require('fs')

const release = (process.argv.includes('--release') ? '--release' : '');

execSync(`node ${__dirname + '/../../pkg/lib/task/build'} ${release}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/js/task/build'} ${release}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/api/task/build'} ${release}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/cli/task/build'} ${release}`, { stdio: 'inherit' });

const libCompileCommands = require(__dirname + '/../../pkg/lib/.build/debug/compile_commands.json');
const jsCompileCommands = require(__dirname + '/../../pkg/js/.build/debug/compile_commands.json');
const apiCompileCommands = require(__dirname + '/../../pkg/api/.build/debug/compile_commands.json');
const cliCompileCommands = require(__dirname + '/../../pkg/cli/.build/debug/compile_commands.json');
const allCompileCommands = [
    ...libCompileCommands,
    ...jsCompileCommands,
    ...apiCompileCommands,
    ...cliCompileCommands
]

mkdirSync(__dirname + '/../../.clangd', { recursive: true });
writeFileSync(__dirname + '/../../.clangd/compile_commands.json', JSON.stringify(allCompileCommands, null, 4));