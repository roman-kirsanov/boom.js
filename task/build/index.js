const { execSync } = require('child_process')
const { writeFileSync, mkdirSync } = require('fs')

const release = (process.argv.includes('--release') ? '--release' : '');

execSync(`node ${__dirname + '/../../pkg/lib/task/build'} ${release}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/js/task/build'} ${release}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/api/task/build'} ${release}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/cli/task/build'} ${release}`, { stdio: 'inherit' });