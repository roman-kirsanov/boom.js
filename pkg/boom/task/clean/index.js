const { rmSync } = require('fs');

rmSync(__dirname + '/../../dist', { recursive: true, force: true });