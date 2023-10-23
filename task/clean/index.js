const { join } = require('path')
const { execSync } = require('child_process')

execSync(`node ${join(__dirname, '..', '..', 'pkg', 'lib', 'task', 'clean')}`, { stdio: 'inherit' });
execSync(`node ${join(__dirname, '..', '..', 'pkg', 'js', 'task', 'clean')}`, { stdio: 'inherit' });
execSync(`node ${join(__dirname, '..', '..', 'pkg', 'api', 'task', 'clean')}`, { stdio: 'inherit' });
execSync(`node ${join(__dirname, '..', '..', 'pkg', 'cli', 'task', 'clean')}`, { stdio: 'inherit' });