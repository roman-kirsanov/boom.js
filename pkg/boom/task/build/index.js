const { execSync } = require('child_process');

if (process.argv.includes('--clean')) {
    execSync('node ' + (__dirname + '/../clean'), { stdio: 'inherit' });
}

execSync('pnpm i', { stdio: 'inherit', cwd: (__dirname + '/../../') });
execSync('npx tsc -p ./src/lib/tsconfig.json', { stdio: 'inherit', cwd: (__dirname + '/../../') });
execSync('npx tsc -p ./src/cli/tsconfig.json', { stdio: 'inherit', cwd: (__dirname + '/../../') });