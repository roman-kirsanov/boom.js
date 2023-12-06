const { rmSync } = require('fs');

rmSync(__dirname + '/../../.build', { recursive: true, force: true });
rmSync(__dirname + '/../../doc/example/TestCppApp/.build', { recursive: true, force: true });