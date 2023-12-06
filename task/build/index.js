const { execSync } = require('child_process');

execSync('node ' + __dirname + '/../../pkg/boom-lib/task/build', { stdio: 'inherit' });
execSync('node ' + __dirname + '/../../pkg/boom-cli/task/build', { stdio: 'inherit' });