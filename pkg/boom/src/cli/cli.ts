import { start } from './start'


if (process.argv[2] === 'init') {
    ;
} else if (process.argv[2] === 'start') {
    const path = process.argv[3];
    const release = process.argv.includes('--release');
    start({ path, release });
} else if (process.argv[2] === 'build') {
    const release = process.argv.includes('--release');
    ;
} else {
    console.log(`ERROR: Command "${process.argv[2]}" not supported`);
}