const { execSync } = require('child_process');

execSync('node ' + __dirname + '/../../pkg/boom-lib/task/clean', { stdio: 'inherit' });