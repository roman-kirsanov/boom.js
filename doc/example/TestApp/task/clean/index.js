const { rmSync } = require('fs')

rmSync(__dirname + '/../../.build', { recursive: true, force: true });