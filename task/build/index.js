const { join } = require('path');
const { platform } = require('os');
const { mkdirSync } = require('fs')
const { execSync } = require('child_process')
const {
    API_PATH,
    JS_PATH,
    CLI_PATH,
    LIB_PATH,
    IS_RELEASE,
    BUILD_TYPE
} = require('../common')

const build = path => {
    const cwd = join(path, '.cmake', (IS_RELEASE ? 'release' : 'debug'));
    mkdirSync(cwd, { recursive: true });
    execSync(`cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${path}`, { cwd, stdio: 'inherit' });
    if (platform() == 'win32') {
        execSync(`msbuild boomapi.sln /p:Configuration=${BUILD_TYPE}`, { cwd, stdio: 'inherit' });
    } else {
        execSync('make', { cwd, stdio: 'inherit' });
    }
}

build(LIB_PATH);
build(JS_PATH);
build(API_PATH);
build(CLI_PATH);