import { existsSync } from 'fs'

export type StartOptions = {
    path: string;
    release?: boolean;
}

export const start = (options: StartOptions) => {
    if (existsSync(options.path)) {
        ;
    } else {
        throw new Error('File not found');
    }
}