const { platform } = require('os');
const { execSync } = require('child_process')
const { mkdirSync, writeFileSync, readFileSync } = require('fs')

const release = process.argv.includes('--release');
const build = (release ? 'Release' : 'Debug');
const path = (__dirname + '/../..');
const cwd = (path + '/.build/' + build);

if (process.argv.includes('--clean')) {
    const clean = (path + '/task/clean');
    execSync(`node ${clean}`, { stdio: 'inherit' });
}

mkdirSync(cwd, { recursive: true });
execSync(`cmake -DCMAKE_BUILD_TYPE=${build} ${path}`, { cwd, stdio: 'inherit' });
if (platform() == 'win32') {
    execSync(`msbuild boom.sln /p:Configuration=${build} /p:LinkerSubSystem=Console`, { cwd, stdio: 'inherit' });
} else {
    execSync('make', { cwd, stdio: 'inherit' });
}