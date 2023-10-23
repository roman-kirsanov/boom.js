const { rmSync } = require('fs')
const { join } = require('path')

rmSync(join(__dirname, '..', '..', '.build'), { recursive: true, force: true });