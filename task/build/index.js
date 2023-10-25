const { execSync } = require('child_process')

const clean = (process.argv.includes('--clean') ? '--clean' : '');
const release = (process.argv.includes('--release') ? '--release' : '');

execSync(`node ${__dirname + '/../../pkg/lib/task/build'} ${release} ${clean}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/js/task/build'} ${release} ${clean}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/api/task/build'} ${release} ${clean}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/cli/task/build'} ${release} ${clean}`, { stdio: 'inherit' });