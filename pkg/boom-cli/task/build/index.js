const { platform } = require('os');
const { mkdirSync } = require('fs');
const { execSync } = require('child_process');

if (process.argv.includes('--clean')) {
    execSync(`node ${(__dirname + '/../clean')}`, { stdio: 'inherit' });
}

const release = process.argv.includes('--release');
const build = (release ? 'Release' : 'Debug');
const path = (__dirname + '/../..');
const out = (__dirname + '/../../.build/' + build);

mkdirSync(out, { recursive: true });
execSync(`cmake -DCMAKE_BUILD_TYPE=${build} ${path}`, { cwd: out, stdio: 'inherit' });
if (platform() == 'win32') {
    execSync(`msbuild boom.sln /p:Configuration=${build}`, { cwd: out, stdio: 'inherit' });
} else {
    execSync('make', { cwd: out, stdio: 'inherit' });
}