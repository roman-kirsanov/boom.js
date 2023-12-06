const { platform } = require('os');
const { execSync } = require('child_process')
const { mkdirSync } = require('fs')

const release = process.argv.includes('--release');
const build = (release ? 'Release' : 'Debug');
const path = (__dirname + '/../..');
const cwd = (path + '/.cmake/' + build);

if (process.argv.includes('--clean')) {
    execSync(`node ${(path + '/task/clean')}`, { stdio: 'inherit' });
}

execSync(`node ../../../../../task/build`, { cwd: __dirname, stdio: 'inherit' });

mkdirSync(cwd, { recursive: true });
execSync(`cmake -DCMAKE_BUILD_TYPE=${build} ${path}`, { cwd, stdio: 'inherit' });
if (platform() == 'win32') {
    execSync(`msbuild TestCppApp.sln /p:Configuration=${build} /p:LinkerSubSystem=Console`, { cwd, stdio: 'inherit' });
} else {
    execSync('make', { cwd, stdio: 'inherit' });
}