const { join } = require('path')

const ROOT_PATH = join(__dirname, '..');
const API_PATH = join(ROOT_PATH, 'pkg', 'api');
const CLI_PATH = join(ROOT_PATH, 'pkg', 'cli');
const JS_PATH = join(ROOT_PATH, 'pkg', 'js');
const LIB_PATH = join(ROOT_PATH, 'pkg', 'lib');
const IS_DEBUG = (process.argv.includes('--release') == false)
const IS_RELEASE = (process.argv.includes('--release') == true)
const BUILD_TYPE = (IS_RELEASE ? 'Release' : 'Debug');

module.exports = {
    ROOT_PATH,
    API_PATH,
    CLI_PATH,
    JS_PATH,
    LIB_PATH,
    IS_DEBUG,
    IS_RELEASE,
    BUILD_TYPE
}