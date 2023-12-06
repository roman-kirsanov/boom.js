const { platform } = require('os');
const { mkdirSync, readdirSync, readFileSync, writeFileSync } = require('fs');
const { execSync } = require('child_process');

if (process.argv.includes('--clean')) {
    execSync(`node ${(__dirname + '/../clean')}`, { stdio: 'inherit' });
}

const release = process.argv.includes('--release');
const build = (release ? 'Release' : 'Debug');

// Build lib...
(() => {
    const path = (__dirname + '/../../lib');
    const out = (__dirname + '/../../lib/.build/' + build);
    const dts = [];

    mkdirSync(out, { recursive: true });
    execSync(`cmake -DCMAKE_BUILD_TYPE=${build} ${path}`, { cwd: out, stdio: 'inherit' });
    if (platform() == 'win32') {
        execSync(`msbuild boom.sln /p:Configuration=${build}`, { cwd: out, stdio: 'inherit' });
    } else {
        execSync('make', { cwd: out, stdio: 'inherit' });
    }

    for (const filename of readdirSync(path + '/src/API')) {
        if (filename.endsWith('.d.ts')) {
            dts.push(readFileSync(path + '/src/API/' + filename).toString());
        }
    }

    writeFileSync(out + '/boom.d.ts', dts.join('\n\n'));
})();

// Build CLI...
(() => {
    execSync('pnpm i', { cwd: (__dirname + '/../../'), stdio: 'inherit' });
})();