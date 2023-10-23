const { rmSync } = require('fs')
const { join } = require('path')

rmSync(join(__dirname, '..', '..', '.cmake'), { recursive: true, force: true });