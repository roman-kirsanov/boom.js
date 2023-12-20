const { execSync } = require('child_process');

const release = (process.argv.includes('--release') ? ' --release' : '');

execSync('node ' + __dirname + '/../../pkg/boom-lib/task/build' + release, { stdio: 'inherit' });
execSync('npm run build', { stdio: 'inherit', cwd: (__dirname + '/../../pkg/boom') });