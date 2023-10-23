const { join } = require('path')
const { rmSync } = require('fs')
const {
    API_PATH,
    JS_PATH,
    CLI_PATH,
    LIB_PATH
} = require('../common')

rmSync(join(API_PATH, '.cmake'), { force: true, recursive: true });
rmSync(join(CLI_PATH, '.cmake'), { force: true, recursive: true });
rmSync(join(JS_PATH, '.cmake'), { force: true, recursive: true });
rmSync(join(LIB_PATH, '.cmake'), { force: true, recursive: true });