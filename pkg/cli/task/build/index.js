const { platform } = require('os');
const { execSync } = require('child_process')
const { mkdirSync, writeFileSync, readFileSync } = require('fs')

const release = process.argv.includes('--release');
const buildType = (release ? 'Release' : 'Debug');
const path = (__dirname + '/../..');
const cwd = (path + '/.build' + (release ? '/release' : '/debug'));

if (process.argv.includes('--clean')) {
    const clean = (path + '/task/clean');
    execSync(`node ${clean}`, { stdio: 'inherit' });
}

execSync('pnpm i', { cwd: path, stdio: 'inherit' });
execSync(`npx esbuild ${path}/src/main.ts --bundle --platform=neutral --format=iife --outfile=${cwd}/bundle.js`);
writeFileSync(`${cwd}/embed.cpp`,
`static char const __COMPAT[] = {${readFileSync(path + '/src/compat.js').map(i => i.toString()).join(', ')}, 0x00};
static char const __BUNDLE[] = {${readFileSync(cwd + '/bundle.js').map(i => i.toString()).join(', ')}, 0x00};\n
extern \"C\" char const* COMPAT() { return __COMPAT; }
extern \"C\" char const* BUNDLE() { return __BUNDLE; }`);

mkdirSync(cwd, { recursive: true });
execSync(`cmake -DCMAKE_BUILD_TYPE=${buildType} ${path}`, { cwd, stdio: 'inherit' });
if (platform() == 'win32') {
    execSync(`msbuild boom.sln /p:Configuration=${buildType}`, { cwd, stdio: 'inherit' });
} else {
    execSync('make', { cwd, stdio: 'inherit' });
}