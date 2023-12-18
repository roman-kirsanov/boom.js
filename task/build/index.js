const { execSync } = require('child_process');

const release = (process.argv.includes('--release') ? ' --release' : '');

execSync('node ' + __dirname + '/../../pkg/boom-lib/task/build' + release, { stdio: 'inherit' });
execSync('node ' + __dirname + '/../../pkg/boom-cli/task/build' + release, { stdio: 'inherit' });