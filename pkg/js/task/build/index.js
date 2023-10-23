const { join } = require('path');
const { platform } = require('os');
const { mkdirSync } = require('fs')
const { execSync } = require('child_process')

const release = process.argv.includes('--release');
const buildType = (release ? 'Release' : 'Debug');
const path = join(__dirname, '..', '..');
const cwd = join(path, '.cmake', (release ? 'release' : 'debug'));

if (process.argv.includes('--clean')) {
    const clean = join(path, 'task', 'clean');
    execSync(`node ${clean}`, { stdio: 'inherit' });
}

mkdirSync(cwd, { recursive: true });
execSync(`cmake -DCMAKE_BUILD_TYPE=${buildType} ${path}`, { cwd, stdio: 'inherit' });
if (platform() == 'win32') {
    execSync(`msbuild boomjs.sln /p:Configuration=${buildType}`, { cwd, stdio: 'inherit' });
} else {
    execSync('make', { cwd, stdio: 'inherit' });
}