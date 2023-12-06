const { rmSync } = require('fs');

rmSync(__dirname + '/../../.build', { force: true, recursive: true });