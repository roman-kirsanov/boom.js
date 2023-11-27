const { platform } = require('os');
const { mkdirSync, readdirSync, readFileSync, writeFileSync } = require('fs')
const { execSync } = require('child_process')

const release = process.argv.includes('--release');
const build = (release ? 'Release' : 'Debug');
const path = (__dirname + '/../..');
const cwd = (path + '/.build/' + build);
const dts = [];

if (process.argv.includes('--clean')) {
    const clean = (path + '/task/clean');
    execSync(`node ${clean}`, { stdio: 'inherit' });
}

mkdirSync(cwd, { recursive: true });
execSync(`cmake -DCMAKE_BUILD_TYPE=${build} ${path}`, { cwd, stdio: 'inherit' });
if (platform() == 'win32') {
    execSync(`msbuild boomapi.sln /p:Configuration=${build}`, { cwd, stdio: 'inherit' });
} else {
    execSync('make', { cwd, stdio: 'inherit' });
}

for (const filename of readdirSync(path + '/src')) {
    if (filename.endsWith('.d.ts')) {
        dts.push(readFileSync(path + '/src/' + filename).toString());
    }
}

writeFileSync(cwd + '/boom.d.ts', dts.join('\n\n'));