const { rmSync } = require('fs')

rmSync(__dirname + '/../../.cmake', { recursive: true, force: true });