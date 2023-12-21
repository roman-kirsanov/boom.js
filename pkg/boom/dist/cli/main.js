"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const child_process_1 = require("child_process");
(0, child_process_1.execSync)('node_modules\\boom\\lib\\windows-x64\\boom.exe src\\main.js', { stdio: 'inherit' });
