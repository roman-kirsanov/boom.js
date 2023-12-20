import { existsSync } from 'fs';
export const start = (options) => {
    if (existsSync(options.path)) {
        ;
    }
    else {
        throw new Error('File not found');
    }
};
