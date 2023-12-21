import { execSync } from 'child_process'
import { readdirSync } from 'fs'

execSync('node_modules\\boom\\lib\\windows-x64\\boom.exe src\\main.js', { stdio: 'inherit' });