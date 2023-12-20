"use strict";
if (process.argv[2] === 'init') {
    ;
}
else if (process.argv[2] === 'start') {
    const release = process.argv.includes('--release');
    ;
}
else if (process.argv[2] === 'build') {
    const release = process.argv.includes('--release');
    ;
}
else {
    console.log(`ERROR: Command "${process.argv[2]}" not supported`);
}
