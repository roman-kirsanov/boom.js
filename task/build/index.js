const { execSync } = require('child_process')

const clean = (process.argv.includes('--clean') ? '--clean' : '');
const release = (process.argv.includes('--release') ? '--release' : '');

execSync(`node ${__dirname + '/../../pkg/boom-lib/task/build'} ${release} ${clean}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/boom-cli/task/build'} ${release} ${clean}`, { stdio: 'inherit' });