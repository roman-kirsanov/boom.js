const { rmSync } = require('fs');

rmSync(__dirname + '/../../.cmake', { recursive: true, force: true });
rmSync(__dirname + '/../../doc/example/TestCppApp/.cmake', { recursive: true, force: true });