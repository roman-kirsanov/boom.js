const { execSync } = require('child_process')

execSync(`node ${__dirname + '/../../pkg/lib/task/clean'}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/js/task/clean'}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/api/task/clean'}`, { stdio: 'inherit' });
execSync(`node ${__dirname + '/../../pkg/cli/task/clean'}`, { stdio: 'inherit' });